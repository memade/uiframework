#include "stdafx.h"

namespace local {
 // Notice use of wxIMPLEMENT_APP_NO_MAIN() instead of the usual wxIMPLEMENT_APP!
 wxIMPLEMENT_APP_NO_MAIN(shared::wx::IwxApp);
#if 0
 extern shared::wx::IwxApp& wxGetApp() { 
  return *static_cast<shared::wx::IwxApp*>(wxApp::GetInstance());
 }
 wxAppConsole* wxCreateApp() {
  wxAppConsole::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE,"my program");
  return new shared::wx::IwxApp();
 }
 wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction)wxCreateApp);
#endif
 WxMain::WxMain(const TypeIdentify& identify) : m_Identify(identify) {

 }

 WxMain::~WxMain() {

 }
 void WxMain::Release() const {
  delete this;
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
    //if (!wxEntryStart(__gpHinstance))
    // break;
    //if (!wxTheApp || !wxTheApp->CallOnInit())
    // break;
    result = 1;
   } while (0);
   return result;
    }, &hEvent, 0, NULL));
   if (!m_hUIMain)
    break;
   ::WaitForSingleObject(hEvent, INFINITE);
   SK_CLOSE_HANDLE(hEvent);
   
   wxGetApp().RegisterAppCloseEventNotifyCb(OnAppClose);
   // Send a message to wx thread to show a new frame:
   wxThreadEvent* event = new wxThreadEvent(wxEVT_THREAD, shared::wx::CMD_APP_FRAME_SHOW);
   event->SetString("Hello wxWidgets!");
   wxQueueEvent(wxApp::GetInstance(), event);

   m_IsOpen.store(true);
  } while (0);
 }
 void WxMain::OnAppClose() {
#if !defined(_DEBUG)
  ::_exit(0);
#endif

  auto xx = 0;
 }
 void WxMain::Destory() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_IsOpen.load())
    break;
   if (!m_hUIMain)
    break;
   auto handle = wxApp::GetInstance();
   if (handle) {
    wxQueueEvent(wxApp::GetInstance(), \
     new wxThreadEvent(wxEVT_THREAD, shared::wx::CMD_APP_TERMINATE));
   }
   ::WaitForSingleObject(m_hUIMain, INFINITE);
   SK_CLOSE_HANDLE(m_hUIMain);
   m_IsOpen.store(false);
  } while (0);
 }

 IWindowConfig* WxMain::Config() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return nullptr;
 }

}///namespace local
