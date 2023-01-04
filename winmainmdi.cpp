#include "stdafx.h"
namespace local {
 UIMainMDI::UIMainMDI(WindowConfig* pConfig) : UIBase(pConfig) {
  Init();
 }

 UIMainMDI::~UIMainMDI() {
  UnInit();
 }
 void UIMainMDI::Release() const {
  delete this;
 }
 void UIMainMDI::Init() {
  if (!m_pConfig->Hinstance())
   m_pConfig->Hinstance(__gpHinstance);
  if (m_pConfig->WindowClassName().empty())
   m_pConfig->WindowClassName(__mapMainWindowClassName.at(EnUIType::Win32SDKMDI));
  if (!m_pConfig->WndProcPtr())
   m_pConfig->WndProcPtr(UIMainMDI::WindowProc);
  void(::RegisterClassExW(&m_pConfig->WndClassExW()));
 }
 void UIMainMDI::UnInit() {
  ::UnregisterClassW(m_pConfig->WindowClassName().c_str(), m_pConfig->Hinstance());
 }
 IUIChild* UIMainMDI::CreateChild(IWindowChildConfig* inpConfig) {
  UIChild* result = nullptr;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  auto pConfig = dynamic_cast<WindowChildConfig*>(inpConfig);
  do {
   if (!pConfig)
    break;
   if (!pConfig->ParentHwnd())
    pConfig->ParentHwnd(m_hWnd);
   if (!pConfig->ParentClientHwnd())
    pConfig->ParentClientHwnd(m_hWndClient);
   switch (pConfig->UIType()) {
   case EnUIChildType::Win32: {
    result = new UIChildWin32(pConfig);
   }break;
   case EnUIChildType::WxWidgets: {
    result = new UIChildWxwidgets(pConfig);
   }break;
   case EnUIChildType::DearImGui: {//!@ !***DearImGui module Only one instance can be created.
    m_ChildQ.iterate(
     [&](const auto&, UIChild* pChildObj, auto& itbreak) {
      if (pChildObj->UIType() == pConfig->UIType()) {
       result = pChildObj;
       itbreak = true;
      }
     });
    if (result)
     return result;
    //result = new UIChildImGuiDX10(pConfig);
    result = new UIChildImGuiDX10(pConfig);
   }break;
   default:
    break;
   }
  } while (0);
  do {
   if (!result)
    break;
   m_ChildQ.push(result->Identify(), result);
  } while (0);
  return dynamic_cast<IUIChild*>(result);
 }
 LRESULT __stdcall UIMainMDI::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  BOOL Handle = FALSE;
  static UIMainMDI* pThis = NULL;
  switch (message) {
  case WM_GETMINMAXINFO: {
   MINMAXINFO* minMax = (MINMAXINFO*)lParam;
   minMax->ptMinTrackSize.x = 640;
   minMax->ptMinTrackSize.y = 480;
   Handle = TRUE;
  }break;
  case WM_SIZE: {
   if (!pThis)
    break;
   RECT rcClient;
   ::GetClientRect(hwnd, &rcClient);
   ::SetWindowPos(pThis->m_hWndClient, NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
   Handle = TRUE;
  }break;
  case WM_DESTROY: {
   ::PostQuitMessage(0);
   Handle = TRUE;
  }break;
  case WM_CREATE: {
   LPCREATESTRUCTW pCreateStructW = reinterpret_cast<LPCREATESTRUCTW>(lParam);
   if (!pCreateStructW)
    break;
   pThis = reinterpret_cast<UIMainMDI*>(pCreateStructW->lpCreateParams);
   if (!pThis)
    break;
   CLIENTCREATESTRUCT client_create_struct = { 0 };
   client_create_struct.idFirstChild = 50000;
   void(::CreateWindowExW(
    0,
    LR"(MDICLIENT)",
    NULL,
    WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    hwnd,
    NULL,
    pCreateStructW->hInstance,
    (LPVOID)&client_create_struct));
   Handle = TRUE;
  }break;
  default:
   break;
  }
  if (Handle)
   return 0;
  return ::DefFrameProcW(hwnd, pThis ? pThis->m_hWndClient : NULL, message, wParam, lParam);
 }
 void UIMainMDI::MainProcess() {
  do {
   m_hWnd = ::CreateWindowExW(
    WS_EX_CLIENTEDGE,
    m_pConfig->WndClassExW().lpszClassName,
    m_pConfig->MainWindowTitleText().c_str(),
    WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
    m_pConfig->DefaultPosition().x,
    m_pConfig->DefaultPosition().y,
    m_pConfig->DefaultSize().cx,
    m_pConfig->DefaultSize().cy,
    m_pConfig->Parent(),
    NULL,
    m_pConfig->Hinstance(),
    this);
   if (!m_hWnd)
    break;
   m_hWndClient = ::GetWindow(m_hWnd, GW_CHILD);
   ::ShowWindow(m_hWnd, SW_SHOWNORMAL);
   ::UpdateWindow(m_hWnd);
   MSG msg = { 0 };
   do {
    bool __quit = false;
    while (::PeekMessageW(&msg, NULL, 0U, 0U, PM_REMOVE)) {
     ::TranslateMessage(&msg);
     ::DispatchMessageW(&msg);
     if (msg.message == WM_QUIT) {
      __quit = true;
     }
    }
    if (__quit)
     break;

    OnRender();

    NotifyMainCreateEvent();
    std::this_thread::sleep_for(std::chrono::microseconds(10));
   } while (1);


  } while (0);
 }

}///namespace local
