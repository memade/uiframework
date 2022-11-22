#include "stdafx.h"

namespace local {
 UIBase::UIBase(WindowConfig* pConfig)
  :m_pConfig(pConfig) {
  m_hUIMainCreateEvent = ::CreateEventW(NULL, FALSE, FALSE, NULL);
 }
 UIBase::~UIBase() {
  m_ChildQ.iterate_clear(
   [&](const auto& identify, auto& child, auto&, auto& itclear) {
    child->Release();
  itclear = true;
   });
  SK_CLOSE_HANDLE(m_hUIMainCreateEvent);
  SK_CLOSE_HANDLE(m_hUIMain);

  for (auto it = m_ChildConfigQ.begin(); it != m_ChildConfigQ.end();) {
   (*it)->Release();
   it = m_ChildConfigQ.erase(it);
  }
 }
 IWindowChildConfig* UIBase::CreateChildConfig() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  auto pConfig = new WindowChildConfig();
  pConfig->Hinstance(m_pConfig->Hinstance());
  return dynamic_cast<IWindowChildConfig*>(m_ChildConfigQ.emplace_back(pConfig));
 }
 IWindowConfig* UIBase::Config() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_pConfig;
 }
 void UIBase::Destory() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_IsOpen.load())
    break;
   ::SendMessageW(shared::GlobalWindowConfigGet()->hMain, WM_CLOSE, 0, 0);
   ::WaitForSingleObject(m_hUIMain, INFINITE);
   m_IsOpen.store(false);
  } while (0);
 }
 const HWND& UIBase::MainWnd() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_hWnd;
 }
 void UIBase::Create() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   INITCOMMONCONTROLSEX icc = { 0 };
   icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
   icc.dwICC = ICC_WIN95_CLASSES;
   if (FALSE == ::InitCommonControlsEx(&icc))
    break;
   if (m_IsOpen.load())
    break;
   if (!__gpHinstance)
    break;
   m_hUIMain = reinterpret_cast<HANDLE>(::_beginthreadex(NULL, 0,
    [](void* param)->UINT {
     UIBase* pThis = reinterpret_cast<UIBase*>(param);
   pThis->MainProcess();
   return 0;
    }, this, 0, NULL));
   ::WaitForSingleObject(m_hUIMainCreateEvent, INFINITE);
   m_IsOpen.store(true);
  } while (0);
 }
 void UIBase::OnRender() {
  /*std::lock_guard<std::mutex> lock{ *m_Mutex };*/
  m_ChildQ.iterate_const(
   [](const auto& pChild, auto& itbreak) {
    pChild->OnRender();
   });
 }
 void UIBase::MdiCascade() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_hWndClient)
    break;
   if (!m_pConfig)
    break;
   if (EnUIType::Win32SDKMDI != m_pConfig->UIType())
    break;
   ::SendMessageW(m_hWndClient, WM_MDICASCADE, 0, 0);
  } while (0);
 }
 void UIBase::MdiTile() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_hWndClient)
    break;
   if (!m_pConfig)
    break;
   if (EnUIType::Win32SDKMDI != m_pConfig->UIType())
    break;
   ::SendMessageW(m_hWndClient, WM_MDITILE, 0, 0);
  } while (0);
 }
 void UIBase::MdiConarrange() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_hWndClient)
    break;
   if (!m_pConfig)
    break;
   if (EnUIType::Win32SDKMDI != m_pConfig->UIType())
    break;
   ::SendMessageW(m_hWndClient, WM_MDIICONARRANGE, 0, 0);
  } while (0);
 }
 void UIBase::Show(const bool& show_flag) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_ShowFlag.store(show_flag);
 }
 bool UIBase::Show() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ShowFlag.load();
 }
 void UIBase::ShowControl() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_pConfig)
    break;
   if (!m_pConfig->Visible() && !m_ShowFlag.load())
    break;
   if (m_pConfig->Visible() && m_ShowFlag.load())
    break;
   if (m_pConfig->Visible())
    ::ShowWindow(m_hWnd, SW_SHOW);
   else
    ::ShowWindow(m_hWnd, SW_HIDE);
   m_ShowFlag.store(m_pConfig->Visible());
  } while (0);

 }

}///namespace local
