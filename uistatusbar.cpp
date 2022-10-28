#include "stdafx.h"

namespace local {
 UIStatusBar::UIStatusBar(const UIType& uitype, const bool& init_show) : UIBase(uitype, init_show) {
  Init();
 }
 UIStatusBar::~UIStatusBar() {
  UnInit();
 }
 void UIStatusBar::Init() {
 }
 void UIStatusBar::UnInit() {
 }
 void UIStatusBar::OnFinalMessage(HWND hWnd) {
  /*delete this;*////Release can cause a crash
 }
 const HWND& UIStatusBar::Hwnd() const {
  return UIBase::m_hWnd;
 }
 bool UIStatusBar::IsOpen() const {
  return m_IsOpen.load();
 }
 void UIStatusBar::Create() {
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
   UIBase::m_hWnd = UIFrame::Create(NULL, _TEXT("PCDown Statusbar®"), dwCreateStyle, 0L);
   if (!UIBase::m_hWnd)
    break;
   m_IsOpen.store(true);
   CenterWindow();
   CPaintManagerUI::MessageLoop();
  } while (0);
 }
 void UIStatusBar::Destory() {
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
 void UIStatusBar::InitWindow() {
  m_pUIButtonActivateDownTable = GetCtrl<CButtonUI>(L"32986A9F93F0");
  m_pUIButtonDownTotalCount = GetCtrl<CButtonUI>(L"FE58908224CC");
  m_pUIProgress = GetCtrl<CProgressUI>(L"D73AF13A8F49");
  m_pUITextGameDownload = GetCtrl<CLabelUI>(L"7C9745D4E9BD");

  if (m_pUIButtonDownTotalCount) {
   m_pUIButtonDownTotalCount->SetVisible(false);
  }
  if (m_pUIProgress) {
   m_pUIProgress->SetValue(0);
   m_pUIProgress->SetVisible(false);
  }
  if (m_pUITextGameDownload)
   m_pUITextGameDownload->SetVisible(false);
 }

 LRESULT UIStatusBar::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 LRESULT UIStatusBar::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  LONG styleValue = ::GetWindowLongW(*this, GWL_STYLE);
  styleValue &= ~WS_CAPTION;
  ::SetWindowLongW(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

  LONG ExStyleValue = ::GetWindowLongW(*this, GWL_EXSTYLE);
  ExStyleValue |= WS_EX_TOOLWINDOW;
  ::SetWindowLongW(*this, GWL_EXSTYLE, ExStyleValue);

  m_pm.Init(GetHWND());
  CDialogBuilder builder;
  CControlUI* pRoot = builder.Create(std::wstring(GetWindowClassName()).append(_TEXT(".xml")).c_str(), (LPCTSTR)0, NULL, &m_pm);
  ASSERT(pRoot && "Failed to parse 'ui.xml'");
  m_pm.AttachDialog(pRoot);
  m_pm.AddNotifier(this);
  bHandled = TRUE;
  return 0;
 }

 LRESULT UIStatusBar::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 LRESULT UIStatusBar::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 LRESULT UIStatusBar::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 LRESULT UIStatusBar::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  ::PostQuitMessage(0L);
  bHandled = TRUE;
  return 0;
 }

 LRESULT UIStatusBar::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 CControlUI* UIStatusBar::CreateControl(LPCTSTR pstrClassName) {
  return nullptr;
 }



 void UIStatusBar::Notify(TNotifyUI& msg) {
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
   if (m_pUIButtonActivateDownTable == msg.pSender) {//!@ 激活下载管理窗口按钮
    do {
     HWND hParent = Global::PCHackerGet()->ParentHwnd(EnUIType::DownManagerUI);
     HWND hPCHacher = \
      reinterpret_cast<HWND>(Global::PCHackerGet()->UIGetHwnd(EnUIType::DownManagerUI));
     if (!hPCHacher) {
      if (!Global::PCHackerGet()->UICreate(EnUIType::DownManagerUI, false))
       break;
      hPCHacher = \
       reinterpret_cast<HWND>(Global::PCHackerGet()->UIGetHwnd(EnUIType::DownManagerUI));
      if (!hPCHacher)
       break;

      if (hParent)
       ::SetParent(hPCHacher, hParent);
     }

     if (Global::PCHackerGet()->UIShowIs(EnUIType::DownManagerUI)) {
      Global::PCHackerGet()->UIShow(EnUIType::DownManagerUI, false);
     }
     else {
      RECT rtStatusbarClient = { 0 };
      RECT rtStatusbarWindow = { 0 };
      ::GetClientRect(UIBase::m_hWnd, &rtStatusbarClient);
      ::GetWindowRect(UIBase::m_hWnd, &rtStatusbarWindow);

      //!@ 如果指定了模块父窗口则启用客户端定位否则启用屏幕窗口定位
      if (hParent) {
       RECT rtPCDownClient = { 0 };
       ::GetClientRect(hPCHacher, &rtPCDownClient);
       RECT rtParentClient = { 0 };
       ::GetClientRect(hParent, &rtParentClient);
       ::SetWindowPos(hPCHacher, NULL,
        rtStatusbarClient.left,
        rtParentClient.bottom - (rtPCDownClient.bottom - rtPCDownClient.top) - (rtStatusbarClient.bottom - rtStatusbarClient.top),
        0, 0, SWP_NOSIZE | SWP_NOZORDER);
      }
      else {
       RECT rtPCDownWindow = { 0 };
       ::GetWindowRect(hPCHacher, &rtPCDownWindow);
       ::SetWindowPos(hPCHacher, NULL,
        rtStatusbarWindow.left,
        rtStatusbarWindow.top - (rtPCDownWindow.bottom - rtPCDownWindow.top),
        0, 0, SWP_NOSIZE | SWP_NOZORDER);
      }
      Global::PCHackerGet()->UIShow(EnUIType::DownManagerUI, true);
     }

    } while (0);
   }



  }
  else {

  }
 }


 void UIStatusBar::DownStatusTotalCount(const size_t& total) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_pUIButtonDownTotalCount)
    break;
   auto text = m_pUIButtonDownTotalCount->GetText();
   size_t current = ::_wtol(text.GetData());
   if (current == total)
    break;
   m_pUIButtonDownTotalCount->SetText(std::to_wstring(total).c_str());
  } while (0);
 }
 size_t UIStatusBar::DownStatusTotoalCount() const {
  size_t result = 0;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_pUIButtonDownTotalCount)
    break;
   auto text = m_pUIButtonDownTotalCount->GetText();
   result = ::_wtol(text.GetData());
  } while (0);
  return result;
 }
 void UIStatusBar::StatusbarProgressCtrl(const bool& show) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  if (m_pUIButtonDownTotalCount)
   m_pUIButtonDownTotalCount->SetVisible(show);
  if (m_pUIProgress)
   m_pUIProgress->SetVisible(show);
  if (m_pUITextGameDownload)
   m_pUITextGameDownload->SetVisible(show);
 }
 void UIStatusBar::Refresh() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   HWND hParent = ::GetParent(UIBase::m_hWnd);
   if (!hParent)
    break;
   if (m_tagSize.cx <= 0 && m_tagSize.cy <= 0)
    break;
   RECT rtParentWindow = { 0 };
   ::GetWindowRect(hParent, &rtParentWindow);
   RECT rtParentClient = { 0 };
   ::GetWindowRect(hParent, &rtParentClient);
   int cx = rtParentClient.right - rtParentClient.left;
   int cy = rtParentClient.bottom - rtParentClient.top;
   int x = m_tagPoint.x;
   int y = cy - m_tagSize.cy + m_tagPoint.y;
   cx = m_tagSize.cx <= 0 ? cx : m_tagSize.cx;
   cy = m_tagSize.cy <= 0 ? cy : m_tagSize.cy;

   ::SetWindowPos(UIBase::m_hWnd, NULL, x, y, cx, cy, SWP_NOACTIVATE);
  } while (0);
 }
}///namespace local
