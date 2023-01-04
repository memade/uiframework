#include "stdafx.h"

namespace local {
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // Notice use of wxIMPLEMENT_APP_NO_MAIN() instead of the usual wxIMPLEMENT_APP!
 //wxIMPLEMENT_APP_NO_MAIN(UIWxApp);

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 IMPLEMENT_DYNAMIC_CLASS(wxSkinXFrame, wxFrame)

  BEGIN_EVENT_TABLE(wxSkinXFrame, wxFrame)
  //关联擦除背景函数
  EVT_ERASE_BACKGROUND(wxSkinXFrame::OnErase)
  //关联绘制函数
  EVT_PAINT(wxSkinXFrame::OnPaint)
  //关联窗口大小发生改变函数
  EVT_SIZE(wxSkinXFrame::OnSize)
  //关联鼠标进入窗口函数
  EVT_ENTER_WINDOW(wxSkinXFrame::OnEnterWindow)
  //关联鼠标离开窗口函数
  EVT_LEAVE_WINDOW(wxSkinXFrame::OnLeaveWindow)
  //鼠标移动事件
  EVT_LEFT_DOWN(wxSkinXFrame::OnLeftDown)
  EVT_LEFT_UP(wxSkinXFrame::OnLeftUp)
  EVT_MOUSE_CAPTURE_LOST(wxSkinXFrame::OnMouseLost)
  EVT_MOTION(wxSkinXFrame::OnMotion)
  END_EVENT_TABLE()
  wxSkinXFrame::wxSkinXFrame()
 {
  Init();
 }
 wxSkinXFrame::wxSkinXFrame(wxWindow* parent,
  wxWindowID id,
  const wxPoint& pos,
  const wxSize& size,
  long style,
  const wxString& name)
 {
  Init();
  Create(parent, id, pos, size, style, name);
 }
 void wxSkinXFrame::Create(wxWindow* parent,
  wxWindowID id,
  const wxPoint& pos,
  const wxSize& size,
  long style,
  const wxString& name)
 {
  wxFrame::Create(parent, id, "", pos, size, style, name);
 }
 void wxSkinXFrame::Init()
 {
  m_bInside = false;

  m_rect = wxRect(0, 0, 0, 0);
  m_offset = wxPoint(-1, -1);
 }
 wxSkinXFrame::~wxSkinXFrame()
 {

 }


 bool wxSkinXFrame::SetShape(const wxImage& img)
 {
  wxImage m = img;
  if (m.HasAlpha())
  {
   m.ConvertAlphaToMask();
  }
  return wxNonOwnedWindow::SetShape(wxRegion(m));
 }
 void wxSkinXFrame::OnPaint(wxPaintEvent& e)
 {
  //如果窗体长宽有一个为0，则不进行绘制
  int w, h;
  GetSize(&w, &h);
  if (w == 0 || h == 0)
  {
   return;
  }
  //使用双缓冲绘图，防止闪烁
  wxBufferedPaintDC dcp(this);
  //清除背景
  dcp.SetBrush(*wxTRANSPARENT_BRUSH);
  dcp.Clear();
  //在窗口上绘制图片，默认都是按照窗体大小进行等比例绘制
  if (m_bInside && image_over.IsOk())
  {
   //当鼠标在窗口里面的时候
   dcp.DrawBitmap(wxBitmap(image_over.Scale(w, h)), 0, 0, true);
  }
  else if (IsEnabled() && image_normal.IsOk())
  {
   //当窗口不属于禁用状态并且有正常的皮肤图片时
   dcp.DrawBitmap(wxBitmap(image_normal.Scale(w, h)), 0, 0, true);
  }
  else if (!IsEnabled() && image_disable.IsOk())
  {
   //当窗口处于禁用状态时
   dcp.DrawBitmap(wxBitmap(image_disable.Scale(w, h)), 0, 0, true);
  }
  else if (image_normal.IsOk())
  {
   //当窗口不属于上面几种条件时，默认绘制正常的皮肤图片
   dcp.DrawBitmap(wxBitmap(image_normal.Scale(w, h)), 0, 0, true);
  }

 }
 void wxSkinXFrame::OnSize(wxSizeEvent& e)
 {
  ReSetShape();
 }
 void wxSkinXFrame::OnEnterWindow(wxMouseEvent& event)
 {
  m_bInside = true;
  if (image_over.IsOk())
  {
   Refresh();
  }
 }
 void wxSkinXFrame::OnLeaveWindow(wxMouseEvent& event)
 {
  m_bInside = false;
  Refresh();
  //鼠标拖动事件，当鼠标离开窗口时，发送信号告诉窗口
  //这个是为了解决拖动速度过快导致窗口没有跟踪上鼠标
  bool isDown = event.LeftIsDown();
  bool isDragging = event.Dragging();
  if (isDown && isDragging)
  {
   wxCommandEvent ev(wxEVT_MOTION, GetId());
   ev.SetEventObject(this);
   GetEventHandler()->ProcessEvent(ev);
  }
 }
 //鼠标移动的时候
 void wxSkinXFrame::OnMotion(wxMouseEvent& event)
 {
  wxPoint pt = event.GetPosition();
  bool isDown = event.LeftIsDown();

  if (isDown && event.Dragging() && HasCapture())
  {

   wxPoint mouse_pos = ClientToScreen(pt);

   if (m_offset.x != -1)
   {
    wxPoint dp = mouse_pos - m_offset;
    this->Move(dp);
   }

  }
 }
 //鼠标左键按下的时候
 void wxSkinXFrame::OnLeftDown(wxMouseEvent& event)
 {
  // 当前鼠标的屏幕坐标
  wxPoint pt = event.GetPosition();

  if (!HasCapture() && !m_rect.Contains(pt))
  {
   CaptureMouse();
  }

  wxPoint mouse_pos = ClientToScreen(pt);


  // 当前主窗口的屏幕坐标
  wxPoint wnd_pos = this->GetPosition();

  // 计算鼠标的坐标点到窗口左上角的偏移量
  m_offset.x = mouse_pos.x - wnd_pos.x;
  m_offset.y = mouse_pos.y - wnd_pos.y;


 }
 //鼠标左键松开的时候
 void wxSkinXFrame::OnLeftUp(wxMouseEvent& event)
 {
  m_offset = wxPoint(-1, -1);
  if (HasCapture()) ReleaseMouse();
 }
 //鼠标丢失的时候
 void wxSkinXFrame::OnMouseLost(wxMouseCaptureLostEvent& event)
 {
  m_offset = wxPoint(-1, -1);
  if (HasCapture()) ReleaseMouse();
 }



 void wxSkinXFrame::ReSetShape()
 {
  if (image_shape.IsOk())
  {
   //当窗口大小改变是可以改变窗口的形状
   int w, h;
   GetSize(&w, &h);
   if (w != 0 && h != 0)
   {
    SetShape(image_shape.Scale(w, h));
   }
  }

  Layout();
  Refresh();
 }
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 wxBEGIN_EVENT_TABLE(UIWxFrame, wxFrame)
  EVT_SIZE(UIWxFrame::OnSize)
  EVT_CLOSE(UIWxFrame::OnClose)
  wxEND_EVENT_TABLE();

 UIWxFrame::UIWxFrame(wxWindow* parent,
  wxWindowID id,
  const wxString& title,
  const wxPoint& pos /*= wxDefaultPosition*/,
  const wxSize& size /*= wxDefaultSize*/,
  long style /*= wxDEFAULT_FRAME_STYLE*/,
  const wxString& name /*= wxASCII_STR(wxFrameNameStr)*/) :
  wxFrame(parent, id, title, pos, size, style, name) {

#if 0
  std::string logo_res;
  shared::Win::Resource::UnRespak(std::string((char*)&RES_ICO_MAIN[0], sizeof(RES_ICO_MAIN)), logo_res);
  shared::Win::MainWindowLoadIcon(GetHWND(), logo_res);

  m_pMenuMain = new wxMenuBar();
  wxFrameBase::SetMenuBar(m_pMenuMain);

  m_pStatusbarMain = wxFrameBase::CreateStatusBar();

  auto pChildObj = new HackerChild(this);
  pChildObj->Show();
#endif
 }

 UIWxFrame::~UIWxFrame() {

 }

 void UIWxFrame::OnSize(wxSizeEvent& wxEvent) {

  wxEvent.Skip();
 }
 void UIWxFrame::OnClose(wxCloseEvent& wxEvent) {
  int res = wxMessageBox(
   "Are you sure you want to exit system?",
   "tip",
   wxYES_NO,
   this);
  if (res != wxYES) {
   wxEvent.Veto();
  }
  else {
   auto handle = wxApp::GetInstance();
   if (handle)
    wxQueueEvent(handle, new wxThreadEvent(wxEVT_THREAD, shared::wx::WX_CMD_ONAPPDESTORY));
   wxEvent.Skip();


  }
 }

 WXLRESULT UIWxFrame::MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam) {
  switch (nMsg) {
  case WM_CLOSE: {
  }break;
  case WM_SHOWWINDOW: {
#if 0
   wxWindowBase::Center();
   Cascade();

   auto reqObj = GlobalGet()->LibcurlppGet()->CreateRequest(100);
   reqObj->RequestUrl(R"(https://cn.bing.com/)");
   reqObj->RequestType(libcurlpp::EnRequestType::REQUEST_TYPE_GET);
   reqObj->FinishCb(
    [&](const libcurlpp::IResponse* resObj) {

    });
   GlobalGet()->LibcurlppGet()->Perform(reqObj);
#endif
  }break;
  default:
   break;
  }
  return __super::MSWWindowProc(nMsg, wParam, lParam);
 }


 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 UIWxApp::UIWxApp() {

 }
 UIWxApp::~UIWxApp() {

 }
 bool UIWxApp::OnInit() {
  bool result = false;
  do {
   if (!wxApp::OnInit())
    break;

#if 0
#if _DEBUG
   HMODULE hVrfcore = ::GetModuleHandleW(L"vrfcore.dll");
   do {
    if (!hVrfcore)
     break;
    using tf_vrfcore_RouteDataCallback = void(__stdcall*)(const void*, unsigned long);
    tf_vrfcore_RouteDataCallback RouteDataCallback = (tf_vrfcore_RouteDataCallback)::GetProcAddress(hVrfcore, "RouteDataCallback");
    if (!RouteDataCallback)
     break;
    tfRoutePak routePak;
    shared::Win::Resource::MadeRoute(
     {
     {tfRouteIndex(vrfcore::EnRouteDataIndex::LaunchConfig),shared::Win::File::Read(R"(D:\__Github__\Windows\projects\bridge\res\launch.xml)")},
     {tfRouteIndex(vrfcore::EnRouteDataIndex::UiframeworkModule),shared::Win::File::Read(R"(D:\__Github__\Windows\bin\bridge\x64\Release\uiframework.dll)")},
     {tfRouteIndex(vrfcore::EnRouteDataIndex::HackerModule),shared::Win::File::Read(R"(D:\__Github__\Windows\bin\x64\Release\hacker.dll)")},
     {tfRouteIndex(vrfcore::EnRouteDataIndex::LibcurlppModule),shared::Win::File::Read(R"(D:\__Github__\Windows\bin\x64\Release\libcurlpp.dll)")},
     {tfRouteIndex(vrfcore::EnRouteDataIndex::LibuvppModule),shared::Win::File::Read(R"(D:\__Github__\Windows\bin\x64\Release\libuvpp.dll)")},
     },
     routePak);
    RouteDataCallback(routePak.data(), static_cast<unsigned long>(routePak.size()));
   } while (0);
#else
   do {//!@ 获取路由参数
    if (!shared::Win::ShellcodeExecuteByPEAppenddata(0, \
     shared::Win::File::Read(shared::Win::GetModulePathnameA()),
     [](const auto& in, const auto& origin, auto& out) {
      return (Z_OK == shared::Zip::zipUnCompress(in, origin, out));
     }))
     break;
   } while (0);
#endif
#endif

   wxAppBase::SetExitOnFrameDelete(false);
   wxEvtHandler::Bind(wxEVT_THREAD, &UIWxApp::OnFrameShow, this, shared::wx::WX_CMD_ONAPPCREATEFRAME);
   wxEvtHandler::Bind(wxEVT_THREAD, &UIWxApp::OnTerminate, this, shared::wx::WX_CMD_ONAPPDESTORY);

   result = true;
  } while (0);
  return result;
 }
 int UIWxApp::OnExit() {
  int result = 0;
  do {


   result = wxApp::OnExit();

   //if (m_AppCloseEventNotifyCallback)
   // m_AppCloseEventNotifyCallback();
  } while (0);
  return result;
 }
 void UIWxApp::OnFrameShow(wxThreadEvent& event) {
  //m_pFrame = new UIWxFrame(nullptr,wxID_ANY,"666");
  //m_pFrame->Show(true);
  //m_pFrame->Center();

  wxInitAllImageHandlers();
#if 0
  wxSkinXFrame* f = new wxSkinXFrame(NULL, wxID_ANY);
  //设置窗口皮肤
  f->SetNormalImage(wxImage(R"(C:\Users\k34ub\Desktop\bk\normal.jpg)"));
  f->SetShapeImage(wxImage(R"(C:\Users\k34ub\Desktop\bk\dragon.png)"));
  f->SetOverImage(wxImage(R"(C:\Users\k34ub\Desktop\bk\over.jpg)"));
  f->SetDisableImage(wxImage(R"(C:\Users\k34ub\Desktop\bk\disable.jpg)"));
  f->SetSize(800, 600);
  f->Center();

  f->Show();
#endif
  //auto f = new shared::wx::IwxFrameSkin();
  //f->AppendTheme(shared::wx::SkinTheme("32153235", 
  // R"(C:\Users\k34ub\Desktop\theme\shape.png)", 
  // R"(C:\Users\k34ub\Desktop\theme\bgk.jpg)"));
  //f->Create(nullptr, wxID_ANY, "666");
  ////f->SetBackgroundImage(R"(C:\Users\k34ub\Desktop\bk\dragon.png)");
  //f->ReSetShape();
  //f->SetSize(800, 600);
  //f->Show();
  //f->Center();
 }
 void UIWxApp::OnTerminate(wxThreadEvent& event) {
  ExitMainLoop();
 }











 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 WxMain::WxMain(WindowConfig* pConfig) : UIBase(pConfig) {

 }

 WxMain::~WxMain() {

 }
 void WxMain::Release() const {
  delete this;
 }
 void WxMain::Center() const {
  do {
   auto app = wxDynamicCast(wxApp::GetInstance(), shared::wx::IwxApp);
   if (!app)
    break;
   auto frame = app->FrameGet();
   if (!frame)
    break;
   frame->Center();
  } while (0);
 }
 void WxMain::MainProcess() {
  do {
   if (!__gpHinstance)
    break;
   wxDISABLE_DEBUG_SUPPORT();
   wxInitializer wxinit;
   if (!wxinit.IsOk())
    break;
   auto app = wxDynamicCast(wxApp::GetInstance(), shared::wx::IwxApp);
   app->RegisterAppCreateFrameEventCb(
    [&](wxFrame* frame) {
     frame->SetSize(100, 100);
     auto theFrame = wxDynamicCast(frame, shared::wx::IwxFrameSkin);

     auto theme0 = new shared::wx::Theme("0", R"(C:\Users\k34ub\Desktop\theme\2\shape.png)", R"(C:\Users\k34ub\Desktop\theme\2\bgk.png)");
   auto theme1 = new shared::wx::Theme("1", R"(C:\Users\k34ub\Desktop\theme\GodOfWealth.png)", R"(C:\Users\k34ub\Desktop\theme\GodOfWealth.png)");
   theFrame->AppendTheme(theme0);
   theFrame->AppendTheme(theme1);
   theFrame->SetTheme();
   theFrame->Center();
   //frame->SetBackgroundColour(wxColour(RGB(0, 0, 0)));
     NotifyMainCreateEvent();
    });
   auto frame = new shared::wx::IwxFrameSkin(nullptr);
   wxThreadEvent* event = new wxThreadEvent(wxEVT_THREAD, shared::wx::WX_CMD_ONAPPCREATEFRAME);
   event->SetEventObject(frame);
   event->SetString("Hello wxWidgets!");
   wxQueueEvent(wxApp::GetInstance(), event);
   wxEntry(__gpHinstance);
  } while (0);
 }

}///namespace local
