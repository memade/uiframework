#include "stdafx.h"

namespace local {

 UIMain::UIMain(const TypeIdentify& identify) : m_Identify(identify) {

 }

 UIMain::~UIMain() {

 }
 void UIMain::Release() const {
  delete this;
 }
 static bool __Win32CreateWindow() {
  bool result = shared::Win::Window::Win32CreateWindow(__gpHinstance,
   [](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)->LRESULT {
#if 1
    /*LONG style = ::GetWindowLongW(hWnd, GWL_STYLE);
    ::SetWindowLongW(hWnd, GWL_STYLE, style & ~WS_VISIBLE);*/
    PAINTSTRUCT ps = { 0 };
  HDC hdc = nullptr;
  HICON hIcon = shared::Win::CreateIcon(\
   shared::Encryption::WemadeDecode(\
    std::string((char*)&logo_ico_res[0], sizeof(logo_ico_res))));
  shared::GlobalWindowConfigGet()->hMain = hWnd;
  switch (message) {
  case WM_CREATE: {
   shared::GlobalWindowConfigGet()->gdiplusToken = shared::Win::Window::GdiplusStartup();

   LONG style = ::GetWindowLongW(hWnd, GWL_STYLE);
   style = style & ~WS_SIZEBOX;
   style = style & ~WS_MAXIMIZEBOX;
   ::SetWindowLongW(hWnd, GWL_STYLE, style);

   ::SendMessageW(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
   ::SendMessageW(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

   SIZE sizeWindow = shared::Win::Window::Win32GetSystemMetrics();
   sizeWindow.cx /= 3;
   sizeWindow.cy /= 2;
   shared::Win::Window::Win32SizeWindow(hWnd, sizeWindow);
   shared::Win::Window::Win32CenterWindow(hWnd, true);
#if 0
   __gpHwndLink = shared::Win::Window::Win32CreateHyperlink(hWnd,
    local::__gpHinstance,
    LR"(www.baidu.com)", LR"(百度一下，你就知道)", 30, 30, 200, 60);
#endif
   shared::GlobalWindowConfigGet()->hhKeyHook = ::SetWindowsHookExW(
    WH_KEYBOARD_LL,
    [](int nCode, WPARAM wParam, LPARAM lParam)->LRESULT {
     do {
      KBDLLHOOKSTRUCT* pKHook = (KBDLLHOOKSTRUCT*)lParam;
      if (!pKHook)
       break;
      if (HC_ACTION != nCode)
       break;
      switch (wParam) {
      case WM_KEYDOWN:
       [[fallthrough]];
      case WM_SYSKEYDOWN: {
       /*CTRL+LEFT(ALT)*/
       if (!(((::GetKeyState(VK_LCONTROL) & 0x8000) && (::GetKeyState(VK_LMENU) & 0x8000)) || \
        ((::GetKeyState(VK_RCONTROL) & 0x8000) && (::GetKeyState(VK_RMENU) & 0x8000))))
        break;
       if ('k' == pKHook->vkCode || 'K' == pKHook->vkCode) {
        if (::IsWindowVisible(shared::GlobalWindowConfigGet()->hMain))
         ::ShowWindow(shared::GlobalWindowConfigGet()->hMain, SW_HIDE);
        else {
         ::ShowWindow(shared::GlobalWindowConfigGet()->hMain, SW_SHOWNORMAL);
         //::UpdateWindow(__gpHwnd);
         /*::SetWindowPos(__gpHwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW | SWP_DRAWFRAME);*/
        }
       }
       else if ('q' == pKHook->vkCode || 'Q' == pKHook->vkCode) {
        ::DestroyWindow(shared::GlobalWindowConfigGet()->hMain);
       }
      }break;
      default:
       break;
      }///switch
     } while (0);
     return ::CallNextHookEx(shared::GlobalWindowConfigGet()->hhKeyHook, nCode, wParam, lParam);
    }, NULL, 0);

  }break;
  case WM_PAINT: {
   hdc = ::BeginPaint(hWnd, &ps);
   HGDIOBJ fontPrevObj = nullptr;
   shared::Win::Window::Win32CreateFontIndirect(hdc, fontPrevObj, 30, 600);
   shared::Win::Window::Win32TextOut(hdc, LR"(我的电脑到底是出了啥问题？)", RGB(255, 0, 0));
   ::DeleteObject(fontPrevObj);

   const std::string bitmap_buffer = shared::Encryption::WemadeDecode(std::string((char*)&china_png_res[0], sizeof(china_png_res)));
   RECT rtClient;
   ::GetClientRect(hWnd, &rtClient);
   shared::Win::Window::Win32GdiCreateImage(
    hdc,
    bitmap_buffer,
    [&](const unsigned int& width, const unsigned int& height, int& x, int& y) {
     x = rtClient.right - width;
   y = rtClient.bottom - height;
    });
   ::EndPaint(hWnd, &ps);
  }break;
#if 0
  case WM_CLOSE: {
   //::ShowWindow(hWnd, SW_HIDE);
  }break;
#endif
  case WM_DESTROY: {
   if (shared::GlobalWindowConfigGet()->hhKeyHook)
    if (FALSE == ::UnhookWindowsHookEx(shared::GlobalWindowConfigGet()->hhKeyHook)) {
     auto UnhookWindowsHookEx_error = 1;
    }
   ::PostQuitMessage(0);
   shared::Win::Window::GdiplusShutdown(shared::GlobalWindowConfigGet()->gdiplusToken);
  }break;
  default: {
  }break;
  }
#endif
  //switch (message) {
  //case WM_CREATE: {
  // if (!wxEntryStart(__gpHinstance))
  //  return FALSE;

  // if (!wxTheApp || !wxTheApp->CallOnInit())
  //  return FALSE;
  // //wxWindow* const w = wxTheApp->GetTopWindow();

  // //wxTheApp->SetExitOnFrameDelete(true);
  // return 1;
  //}break;
  //default:
  // break;
  //}
  //switch (message) {
  //case WM_CREATE: {
  // wxWindow* const w = wxTheApp->GetTopWindow();
  // if (!w)
  //  return FALSE;

  // // We need to initialize the main window to let the program continue
  // // running.
  // //BaseApp::m_pMainWnd = new wxMFCWnd(w);

  // // We also need to reset m_pMainWnd when this window will be destroyed
  // // to prevent MFC from using an invalid HWND, which is probably not
  // // fatal but can result in at least asserts failures.
  // //w->Bind(wxEVT_DESTROY, &wxMFCApp::OnMainWindowDestroyed, this);

  // // And we need to let wxWidgets know that it should exit the
  // // application when this window is closed, as OnRun(), which does this
  // // by default, won't be called when using MFC main message loop.
  // wxTheApp->SetExitOnFrameDelete(true);

  // return TRUE;
  //}break;
  //default:
  // break;
  //}



  return ::DefWindowProcW(hWnd, message, wParam, lParam); ;
   }, LR"(UIWindow)", L"", POINT{ 0,0 }, SIZE{ 0,0 }, RGB(105, 105, 105), true, nullptr/*::GetDesktopWindow()*/);




  return result;
 }

 void UIMain::Create() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (m_IsOpen.load())
    break;
   if (!__gpHinstance)
    break;

   HANDLE hCreateFinishEvent = ::CreateEventW(NULL, FALSE, FALSE, NULL);
   if (!hCreateFinishEvent)
    break;

   m_hUIMain = reinterpret_cast<HANDLE>(::_beginthreadex(NULL, 0,
    [](void* param)->UINT {
     HANDLE* hEvent = reinterpret_cast<HANDLE*>(param);
   ::SetEvent(*hEvent);
   __Win32CreateWindow();
   //wxEntryStart(__gpHinstance);
   return 0;
    }, &hCreateFinishEvent, 0, NULL));

   ::WaitForSingleObject(hCreateFinishEvent, INFINITE);
   SK_CLOSE_HANDLE(hCreateFinishEvent);
   m_IsOpen.store(true);

  } while (0);
 }

 void UIMain::Destory() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_IsOpen.load())
    break;
   ::SendMessageW(shared::GlobalWindowConfigGet()->hMain, WM_CLOSE, 0, 0);
   ::WaitForSingleObject(m_hUIMain, INFINITE);
   SK_CLOSE_HANDLE(m_hUIMain);

   m_IsOpen.store(false);
  } while (0);
 }

 const TypeIdentify& UIMain::Identify() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Identify;
 }


}///namespace local
