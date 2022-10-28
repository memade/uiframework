#include "stdafx.h"

namespace local {
 class WxFrame : public wxFrame {
 public:
  WxFrame(wxWindow* parent, const wxString& label);
  void OnAbout(wxCommandEvent& event);
  wxDECLARE_EVENT_TABLE();
 };


 static const int CMD_SHOW_WINDOW = wxNewId();
 static const int CMD_TERMINATE = wxNewId();

 class WxApp : public shared::wx::IwxApp {
 public:
  WxApp();
  virtual ~WxApp();
 private:
  void OnShowWindow(wxThreadEvent& event);
  void OnTerminate(wxThreadEvent& event);
 };
 wxBEGIN_EVENT_TABLE(WxFrame, wxFrame)
  EVT_BUTTON(wxID_ABOUT, WxFrame::OnAbout)
  wxEND_EVENT_TABLE()

  WxFrame::WxFrame(wxWindow* parent, const wxString& label)
  : wxFrame(parent, wxID_ANY, label)
 {
  wxPanel* p = new wxPanel(this, wxID_ANY);
  wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

  sizer->Add
  (
   new wxStaticText
   (
    p, wxID_ANY,
    wxString::Format
    (
     "Running using %s\n"
     "wxApp instance is %p, thread ID %ld",
     wxVERSION_STRING,
     wxApp::GetInstance(),
     wxThread::GetCurrentId()
    )
   ),
   wxSizerFlags(1).Expand().Border(wxALL, 10)
  );

  sizer->Add
  (
   new wxButton(p, wxID_ABOUT, "Show info"),
   wxSizerFlags(0).Right().Border(wxALL, 10)
  );

  p->SetSizerAndFit(sizer);

  wxSizer* fsizer = new wxBoxSizer(wxVERTICAL);
  fsizer->Add(p, wxSizerFlags(1).Expand());
  SetSizerAndFit(fsizer);
 }

 void WxFrame::OnAbout(wxCommandEvent& WXUNUSED(event)) {
  wxMessageBox("This window is running in its own thread,\n"
   "using private wxWidgets instance compiled into the DLL.",
   "About",
   wxOK | wxICON_INFORMATION);
 }


 WxApp::WxApp() {
  SetExitOnFrameDelete(false);

  Bind(wxEVT_THREAD, &WxApp::OnShowWindow, this, CMD_SHOW_WINDOW);
  Bind(wxEVT_THREAD, &WxApp::OnTerminate, this, CMD_TERMINATE);
 }
 WxApp::~WxApp() {

 }
 void WxApp::OnShowWindow(wxThreadEvent& event) {
  /*wxFrame* f = new WxFrame(NULL, event.GetString());
  f->Show(true);*/
  auto mdiframe = new shared::wx::IMDIParentFrame(nullptr);
  mdiframe->Show(true);
 }

 void WxApp::OnTerminate(wxThreadEvent& WXUNUSED(event)) {
  ExitMainLoop();
 }
 wxIMPLEMENT_APP_NO_MAIN(WxApp);


 WxMain::WxMain() {

 }

 WxMain::~WxMain() {

 }

 void WxMain::Create() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (m_IsOpen.load())
    break;
   HANDLE hEvent = ::CreateEventW(NULL, FALSE, FALSE, NULL);
   if (!hEvent)
    break;
   m_hUIMain = reinterpret_cast<HANDLE>(::_beginthreadex(NULL, 0,
    [](void* pRouteEvent)->unsigned int {
     unsigned int result = 0;
     do {
      if (!__gpHinstance || !pRouteEvent)
       break;
      HANDLE* phEvent = reinterpret_cast<HANDLE*>(pRouteEvent);
      if (!phEvent)
       break;
      /*const HINSTANCE
       hInstance = wxDynamicLibrary::MSWGetModuleHandle(shared::Win::GetModuleNameA(__gpHinstance), phUIMainThread);
      if (!hInstance)
       break;*/
      wxDISABLE_DEBUG_SUPPORT();
      wxInitializer wxinit;
      if (!wxinit.IsOk())
       break;
      if (!::SetEvent(*phEvent))
       break;
      wxEntry(__gpHinstance);
      result = 1;
     } while (0);
     return result;
    }, &hEvent, 0, NULL));
   if (!m_hUIMain)
    break;
   ::WaitForSingleObject(hEvent, INFINITE);
   SK_CLOSE_HANDLE(hEvent);
   // Send a message to wx thread to show a new frame:
   wxThreadEvent* event = new wxThreadEvent(wxEVT_THREAD, CMD_SHOW_WINDOW);
   event->SetString("Hello wxWidgets!");
   wxQueueEvent(wxApp::GetInstance(), event);
   m_IsOpen.store(true);
  } while (0);
 }

 void WxMain::Destory() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_IsOpen.load())
    break;
   if (!m_hUIMain)
    break;
   wxThreadEvent* event = new wxThreadEvent(wxEVT_THREAD, CMD_TERMINATE);
   wxQueueEvent(wxApp::GetInstance(), event);
   ::WaitForSingleObject(m_hUIMain, INFINITE);
   SK_CLOSE_HANDLE(m_hUIMain);
   m_IsOpen.store(false);
  } while (0);
 }


}///namespace local
