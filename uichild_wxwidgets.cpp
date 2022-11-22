#include "stdafx.h"

namespace local {
 UIChildWxwidgets::UIChildWxwidgets(WindowChildConfig* pConfig) : UIChild(pConfig) {
  Init();
 }
 UIChildWxwidgets::~UIChildWxwidgets() {
  UnInit();
 }
 void UIChildWxwidgets::Release() const {
  delete this;
 }
 void UIChildWxwidgets::Init() {
  m_Ready.store(false);
  do {
   m_pConfig->Host(this);
   if (!m_pConfig->WndProcPtr())
    m_pConfig->WndProcPtr((void*)
     [](HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)->LRESULT {
      static UIChild* pThis = nullptr;
      switch (message) {
      case WM_CREATE: {
       LPCREATESTRUCTW pCreateStructW = reinterpret_cast<LPCREATESTRUCTW>(lParam);
       if (!pCreateStructW)
        break;
       LPMDICREATESTRUCTW pMdiCreateStructW = reinterpret_cast<LPMDICREATESTRUCTW>(pCreateStructW->lpCreateParams);
       if (!pMdiCreateStructW)
        break;
       pThis = reinterpret_cast<UIChild*>(pMdiCreateStructW->lParam);
       if (!pThis)
        break;
      }break;
      default:
       break;
      }
      if (pThis && pThis->OnWindowProc(hwnd, message, wParam, lParam))
       return 0;
      return ::DefMDIChildProcW(hwnd, message, wParam, lParam);
     });
   if (m_pConfig->WindowStyle() == 0)
    m_pConfig->WindowStyle(MDIS_ALLCHILDSTYLES);
   if (m_pConfig->WindowClassName().empty())
    m_pConfig->WindowClassName(__mapChildWindowClassName.at(EnUIChildType::WxWidgets));
   if (m_pConfig->WindowTitleText().empty())
    m_pConfig->WindowTitleText(LR"(Untitled)");
   if (FALSE == ::RegisterClassExW(&m_pConfig->WndClassEx()))
    break;

   m_pwxApp = new shared::wx::IwxApp();
   wxApp::SetInstance(m_pwxApp);
   wxEntryStart(0, nullptr);
   m_pwxApp->CallOnInit();

   m_Ready.store(true);
  } while (0);
 }
 void UIChildWxwidgets::UnInit() {
  m_pwxApp->OnExit();
  m_pwxApp->CleanUp();
  wxApp::SetInstance(NULL);
  SK_DELETE_PTR(m_pwxWindow);
  SK_DELETE_PTR(m_pwxApp);
  wxModule::CleanUpModules();
  ::UnregisterClassW(m_pConfig->WindowClassName().c_str(), m_pConfig->Hinstance());
  m_Ready.store(false);
 }
 bool UIChildWxwidgets::Create() {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_hWnd = (HWND)::SendMessageW(
   m_pConfig->ParentClientHwnd(),
   WM_MDICREATE,
   0,
   (LPARAM)&m_pConfig->MdiCreateStructW());
  return m_hWnd ? true : false;
 }
 void UIChildWxwidgets::Destory() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };

 }
 void UIChildWxwidgets::OnRender() {
  do {

  } while (0);
 }

 class MyPanel : public wxPanel
 {
 public:
  MyPanel(wxWindow* parent, const wxPoint& pos)
   : wxPanel(parent, wxID_ANY, pos)
  {
   wxSizer* const sizer = new wxFlexGridSizer(2, wxSize(5, 5));
   sizer->Add(new wxStaticText(this, wxID_ANY, "Enter your &name:"),
    wxSizerFlags().Center().Right());
   m_textName = new wxTextCtrl(this, wxID_ANY);
   m_textName->SetHint("First Last");
   sizer->Add(m_textName, wxSizerFlags().Expand().CenterVertical());

   sizer->Add(new wxStaticText(this, wxID_ANY, "And your &age:"),
    wxSizerFlags().Center().Right());
   m_spinAge = new wxSpinCtrl(this, wxID_ANY);
   sizer->Add(m_spinAge, wxSizerFlags().Expand().CenterVertical());

   wxStaticBoxSizer* const
    box = new wxStaticBoxSizer(wxVERTICAL, this, "wxWidgets box");
   box->Add(sizer, wxSizerFlags(1).Expand());
   SetSizer(box);

   // We won't be resized automatically, so set our size ourselves.
   SetSize(GetBestSize());
  }

 private:
  wxTextCtrl* m_textName;
  wxSpinCtrl* m_spinAge;
 };

 bool UIChildWxwidgets::OnWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  bool result = false;
  switch (message) {
  case WM_CREATE: {
   m_hWnd = hwnd;
   /*wxEntry(__gpHinstance);
  wxEntryStart(__gpHinstance);*/
   //wxEntry(__gpHinstance);
   ////wxEntryStart(__gpHinstance);
   //wxWindow* win = new wxWindow();
   //win->SetHWND((WXHWND)m_hWnd);
   //win->AdoptAttributesFromHWND();
   //if (!wxTheApp)
   // new shared::wx::IwxApp();
   //win->Reparent(wxTheApp->GetTopWindow());
   ////win->AddChild(new shared::wx::IMDIParentFrame(win));
   //win->Centre();
   // Create a container representing the MFC window in wxWidgets window
    // hierarchy.
   //auto m_containerWX = new wxNativeContainerWindow(m_hWnd);

   // Now we can create children of this container as usual.
   //new MyPanel(m_containerWX, wxPoint(5, 5));

   // An ugly but necessary workaround to prevent the container TLW from
   // resizing the panel to fit its entire client area as it would do if it
   // were its only child.
  // new wxWindow(m_containerWX, wxID_ANY, wxPoint(4, 4), wxSize(1, 1));
   m_pwxWindow = new wxWindow();
   m_pwxWindow->SetHWND((WXHWND)m_hWnd);
   m_pwxWindow->AdoptAttributesFromHWND();
   m_pwxApp->SetTopWindow(m_pwxWindow);

   //wxThreadEvent* event = new wxThreadEvent(wxEVT_THREAD, shared::wx::CMD_APP_FRAME_SHOW);
   //event->SetString("Hello wxWidgets!");
   //wxQueueEvent(wxApp::GetInstance(), event);
   new MyPanel(m_pwxWindow, wxPoint(5, 5));
   //auto m_chartPanel = new wxChartPanel(m_pActiveXWindow, wxID_ANY, NULL, wxPoint(0, 0), wxSize(rectActiveX.right - rectActiveX.left, rectActiveX.bottom - rectActiveX.top));
   /*wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
   m_pwxWindow->SetSizer(boxSizer);
   boxSizer->Add(m_chartPanel, 1, wxALL | wxGROW);*/
   result = true;
  }break;
  case WM_DESTROY: {
   result = true;
  }break;
  default:
   break;
  }
  return result;
 }
}///namespace local
