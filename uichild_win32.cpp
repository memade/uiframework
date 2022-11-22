#include "stdafx.h"

namespace local {
 UIChildWin32::UIChildWin32(WindowChildConfig* pConfig) : UIChild(pConfig) {
  Init();
 }
 UIChildWin32::~UIChildWin32() {
  UnInit();
 }
 void UIChildWin32::Release() const {
  delete this;
 }
 void UIChildWin32::Init() {
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
    m_pConfig->WindowClassName(__mapChildWindowClassName.at(EnUIChildType::Win32));
   if (m_pConfig->WindowTitleText().empty())
    m_pConfig->WindowTitleText(LR"(Untitled)");
   if (FALSE == ::RegisterClassExW(&m_pConfig->WndClassEx()))
    break;

   m_Ready.store(true);
  } while (0);

 }
 void UIChildWin32::UnInit() {
  ::UnregisterClassW(m_pConfig->WindowClassName().c_str(), m_pConfig->Hinstance());
  m_Ready.store(false);
 }
 bool UIChildWin32::Create() {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_hWnd = (HWND)::SendMessageW(
   m_pConfig->ParentClientHwnd(), 
   WM_MDICREATE, 
   0, 
   (LPARAM)&m_pConfig->MdiCreateStructW());
  return m_hWnd ? true : false;
 }
 void UIChildWin32::Destory() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };

 }
 void UIChildWin32::OnRender() {
  do {

  } while (0);
 }

 bool UIChildWin32::OnWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
#if 0
    case WM_ACTIVATE: {
#if 0
     fActive = LOWORD(wParam);   // activation flag 
     fMinimized = (BOOL)HIWORD(wParam); // minimized flag 
     hwndPrevious = (HWND)lParam;   // window handle
     fActive 参数表明窗口是被激活还是被取消。该信息保存在 wParam 的低阶字中，可以取以下的值：
      WA_CLICKACTIVE       通过鼠标单击激活了该窗口
      WA_ACTIVE                   通过鼠标以外的工具（如键盘）激活了该窗口
      WA_INACTIVE               取消该窗口的激活
#endif
      WORD fActive = LOWORD(wParam);
     WORD fMinimized = HIWORD(wParam);
     HWND hwndPrevious = reinterpret_cast<HWND>(lParam);
     switch (fActive) {
     case WA_ACTIVE: {

      auto sk = 0;
     }break;
     case WA_CLICKACTIVE: {

      auto sk = 0;
     }break;
     case WA_INACTIVE: {

      auto sk = 0;
     }break;
     }

     handle = true;
    }break;
#endif
  return false;
 }
}///namespace local
