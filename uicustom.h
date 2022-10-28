#if !defined(INC_H___A3643213_0465_45A2_94A2_B598EAC8C107__HEAD__)
#define INC_H___A3643213_0465_45A2_94A2_B598EAC8C107__HEAD__

namespace local {

 class Cef3BrowserUI : virtual public CControlUI {
 public:
  Cef3BrowserUI() {
  }
  virtual ~Cef3BrowserUI() {
  }
 public:
  void SetVisible(bool bVisible = true)	 override final {
   __super::SetVisible(bVisible);
   ::ShowWindow(m_hWnd, bVisible);
  }

  void SetInternVisible(bool bVisible = true)		 override final {
   __super::SetInternVisible(bVisible);
   ::ShowWindow(m_hWnd, bVisible);
  }
  void SetPos(RECT rc) {
   __super::SetPos(rc);
   ::SetWindowPos(m_hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE);
  }
  void Attach(HWND hWndNew) {
   m_hWnd = hWndNew;
  }
  HWND Detach() {
   HWND hWnd = m_hWnd;
   m_hWnd = NULL;
   return hWnd;
  }
  HWND GetHWND() {
   return m_hWnd;
  }
 protected:
  HWND m_hWnd = nullptr;
 };


}///namespace local

/// /*新生®（上海）**/
/// /*2022_09_28T11:27:42.7586134Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___A3643213_0465_45A2_94A2_B598EAC8C107__HEAD__


