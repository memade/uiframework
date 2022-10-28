#include "stdafx.h"

namespace local {
 UIMain::UIMain(const UIType& uitype, const bool& init_show) : UIBase(uitype, init_show) {
  Init();
 }
 UIMain::~UIMain() {
  UnInit();
 }
 void UIMain::Init() {
 }
 void UIMain::UnInit() {
 }
 void UIMain::OnFinalMessage(HWND hWnd) {
  /*delete this;*////Release can cause a crash
 }
 const HWND& UIMain::Hwnd() const {
  return UIBase::m_hWnd;
 }
 bool UIMain::IsOpen() const {
  return m_IsOpen.load();
 }
 void UIMain::Create() {
  do {
   if (m_IsOpen.load())
    break;
   CPaintManagerUI::SetInstance(__gpHinstance);
#if 0
#ifdef _DEBUG
   /*auto sss = CPaintManagerUI::GetInstancePath();*/
   CPaintManagerUI::SetResourcePath(LR"(D:\__SVN__\Memade\projects\pcdown\res\skin\)");
#else
   //std::string res = shared::Win::File::Read(R"(D:\__SVN__\Memade\projects\pcdown\res\skin.zip)");
   ////*Global::SetupGet() << shared::Win::File::Read(R"(E:\__SVN__\Memade\projects\downtool\res\setup.xml)");
   //if (res.empty())
   //	break;
   std::string res = std::string((char*)&skin_zip_res[0], sizeof(skin_zip_res));
   res = shared::Encryption::WemadeDecode(res);
   if (!shared::Zip::IsZipCompress(res))
    break;
   CPaintManagerUI::SetResourceZip(res.data(), static_cast<unsigned int>(res.size()));
#endif
#else

   CPaintManagerUI::SetResourcePath(Global::PCHackerGet()->UISkinDirectory().c_str());
#endif
   DWORD dwCreateStyle = UI_WNDSTYLE_FRAME;
   do {
    if (m_Show.load())
     break;
    if (!(dwCreateStyle & WS_VISIBLE))
     break;
    dwCreateStyle &= ~WS_VISIBLE;
   } while (0);
   UIBase::m_hWnd = UIFrame::Create(NULL, _TEXT("PCDown main®"), dwCreateStyle, 0L);
   if (!UIBase::m_hWnd)
    break;
   m_IsOpen.store(true);
   CenterWindow();
   CPaintManagerUI::MessageLoop();
  } while (0);
 }
 void UIMain::Destory() {
  do {
   if (!m_IsOpen.load())
    break;
   for (auto& it : m_Threads)
    it.join();
   m_Threads.clear();
   UIFrame::Close(IDOK);
   m_IsOpen.store(false);
  } while (0);
 }

 void UIMain::InitWindow() {
  m_pTabLayoutUIMain = GetCtrl<CTabLayoutUI>(L"1E4BC95731E9");

#if ENABLE_MODULE_CEF3
  for(auto& control : m_CustomControls)
   Global::Cef3Get()->Create(dynamic_cast<Cef3BrowserUI*>(control)->GetHWND());
#endif



 }

 LRESULT UIMain::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 LRESULT UIMain::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  LONG styleValue = ::GetWindowLongW(*this, GWL_STYLE);
  styleValue &= ~WS_CAPTION;
  ::SetWindowLongW(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

  LONG ExStyleValue = ::GetWindowLongW(*this, GWL_EXSTYLE);
  ExStyleValue |= WS_EX_TOOLWINDOW;
  ::SetWindowLongW(*this, GWL_EXSTYLE, ExStyleValue);

  m_pm.Init(GetHWND());
  CDialogBuilder builder;
  CControlUI* pRoot = builder.Create(std::wstring(GetWindowClassName()).append(_TEXT(".xml")).c_str(), (LPCTSTR)0, this, &m_pm);
  ASSERT(pRoot && "Failed to parse 'ui.xml'");
  m_pm.AttachDialog(pRoot);
  m_pm.AddNotifier(this);
  bHandled = TRUE;
  return 0;
 }

 LRESULT UIMain::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 LRESULT UIMain::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 LRESULT UIMain::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 LRESULT UIMain::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  ::PostQuitMessage(0L);
  bHandled = TRUE;
  return 0;
 }

 LRESULT UIMain::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 CControlUI* UIMain::CreateControl(LPCTSTR pstrClassName) {
  CControlUI* result = nullptr;
  do {
   if (0 != ::StrCmpW(pstrClassName, L"Cef3Browser"))
    break;
   result = new Cef3BrowserUI();
   HWND hwnd = ::CreateWindowW(_T("STATIC"), 
    _T(""),
    WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS /*| WS_CLIPCHILDREN*/,
    0, 0, 0, 0, m_pm.GetPaintWindow(), (HMENU)0, NULL, NULL);
   if (!hwnd)
    break;
   dynamic_cast<Cef3BrowserUI*>(result)->Attach(hwnd);
   m_CustomControls.emplace_back(result);
  } while (0);
  return result;
 }



 void UIMain::Notify(TNotifyUI& msg) {
  if (msg.sType == DUI_MSGTYPE_HEADERCLICK) {
  }///DUI_MSGTYPE_HEADERCLICK
#if 0
  else if (msg.sType == DUI_MSGTYPE_LINK) {
   CTextUI* pText = (CTextUI*)msg.pSender;
   CDuiString* strUrl = pText->GetLinkContent(0);
   ::ShellExecute(NULL, _T("open"), strUrl->GetData(), NULL, NULL, SW_SHOWNORMAL);
  }
#endif
  else if (msg.sType == DUI_MSGTYPE_CHECKCLICK) {

  }
  else if (msg.sType == DUI_MSGTYPE_CLICK) {
   if (msg.pSender->GetName() == L"C4B5FC399A8D") {
    m_pTabLayoutUIMain->SelectItem(0);
   }
   else if (msg.pSender->GetName() == L"6134D6C0FADC") {
    m_pTabLayoutUIMain->SelectItem(1);
   }

  }
  else {

  }
 }

}///namespace local
