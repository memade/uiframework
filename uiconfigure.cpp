#include "stdafx.h"

namespace local {
 UIConfigure::UIConfigure(const UIType& uitype, const bool& init_show) : UIBase(uitype, init_show) {
  Init();
 }
 UIConfigure::~UIConfigure() {
  UnInit();
 }
 void UIConfigure::Init() {

 }
 void UIConfigure::UnInit() {

 }
 void UIConfigure::OnFinalMessage(HWND hWnd) {
  /*delete this;*////Release can cause a crash
 }
 const HWND& UIConfigure::Hwnd() const {
  return UIBase::m_hWnd;
 }
 bool UIConfigure::IsOpen() const {
  return m_IsOpen.load();
 }
 void UIConfigure::Create() {
  do {
   if (m_IsOpen.load())
    break;
   CPaintManagerUI::SetInstance(__gpHinstance);
#ifdef _DEBUG
   CPaintManagerUI::SetResourcePath(LR"(D:\__SVN__\Memade\projects\pcdown\res\skin\)");
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
   UIBase::m_hWnd = UIFrame::Create(NULL, _TEXT("PCDown Configure®"), dwCreateStyle, 0L);
   if (!UIBase::m_hWnd)
    break;
   m_IsOpen.store(true);
   CenterWindow();
   CPaintManagerUI::MessageLoop();
  } while (0);
 }
 void UIConfigure::Destory() {
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
 void UIConfigure::InitWindow() {
  m_pOptionDown = GetCtrl<COptionUI>(L"F38DA89C0E8B");
  m_pOptionGeneral = GetCtrl<COptionUI>(L"C4E9B2C7DCB0");
  m_pTabLayoutMain = GetCtrl<CTabLayoutUI>(L"B78751250524");

  /// 开机自动启动
  m_pOptionStartsAutomaticallyWhenStarts = GetCtrl<COptionUI>(L"617CC729EE3A");
  /// 启动时自动下载上次未完成的下载
  m_pOptionLastIncompleteDownloadIsDownloadedAutomaticallyAtStartup = GetCtrl<COptionUI>(L"739D036A420E");
  /// 下载完成后自动安装游戏
  m_pOptionAutomaticallyInstalledAfterDownloading = GetCtrl<COptionUI>(L"ED35F19D6183");
  /// 打开后不显示推广广告
  m_pOptionNoPromotionalAdsAreDisplayedWhenOpened = GetCtrl<COptionUI>(L"94FCF44F7104");
  /// 每次关闭时不再提醒我
  m_pOptionNoMoreRemindersEverytimeItClosesInClickCloseBtn = GetCtrl<COptionUI>(L"5B405FA829F4");
  /// 最小化到系统托盘区
  m_pOptionMinimizeToSystemTrayInClickCloseBtn = GetCtrl<COptionUI>(L"DADB6C99850F");
  /// 立即退出
  m_pOptionExitImmediatelyInClickCloseBtn = GetCtrl<COptionUI>(L"B028F5B3C490");
  /// 安装包存储路径
  m_pEditPathForStoringTheInstallationPackage = GetCtrl<CEditUI>(L"E6EB916CD8D1");
  /// 安装路径
  m_pEditProgramInstallationPath = GetCtrl<CEditUI>(L"F95EA9059591");
  m_pButtonViewTheInstallationPackagePath = GetCtrl<COptionUI>(L"43EDDF54B1B9");
  m_pButtonViewingTheInstallationPath = GetCtrl<COptionUI>(L"0B83DAA3DCAA");
  /// 不限制下载速度
  m_pOptionNolimitOnDownloadSpeed = GetCtrl<COptionUI>(L"6C014D3196C0");
  /// 下载速度阀值
  m_pEditDownloadSpeedThreshold = GetCtrl<CEditUI>(L"5E264C155710");
  /// 自动下载安装包至默认路径
  m_pOptionInstallationPackageAutomaticallyDownloadedToDefaultPath = GetCtrl<COptionUI>(L"65157CA3603C");
  /// 安装包保留天数
  m_pOptionTheInstallationPackageIsReservedFor7Days = GetCtrl<COptionUI>(L"5A32C2448EDE");
  m_pOptionTheInstallationPackageIsReservedFor15Days = GetCtrl<COptionUI>(L"CB47D05B24DA");
  /// 安装包永久保留
  m_pOptionTheInstallationPackageIsRetainedPermanently = GetCtrl<COptionUI>(L"F6FD1E78D000");
  /// 下载完成后关机
  m_pOptionShutDownAfterDownloading = GetCtrl<COptionUI>(L"279F1D194143");
  /// 关闭延迟分钟数
  m_pEditDisableDelayInMinutes = GetCtrl<CEditUI>(L"CFB31D6C9AF1");

  if (m_pOptionGeneral)
   m_pOptionGeneral->Selected(true);
 }


 LRESULT UIConfigure::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 LRESULT UIConfigure::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
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

 LRESULT UIConfigure::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 LRESULT UIConfigure::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 LRESULT UIConfigure::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 LRESULT UIConfigure::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  ::PostQuitMessage(0L);
  bHandled = TRUE;
  return 0;
 }

 LRESULT UIConfigure::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 CControlUI* UIConfigure::CreateControl(LPCTSTR pstrClassName) {
  return nullptr;
 }











 void UIConfigure::Notify(TNotifyUI& msg) {
  if (msg.sType == DUI_MSGTYPE_HEADERCLICK) {
  }///DUI_MSGTYPE_HEADERCLICK
  else if (msg.sType == DUI_MSGTYPE_LINK) {
   CTextUI* pText = (CTextUI*)msg.pSender;
   CDuiString* strUrl = pText->GetLinkContent(0);
   ::ShellExecute(NULL, _T("open"), strUrl->GetData(), NULL, NULL, SW_SHOWNORMAL);
  }
  else if (msg.sType == DUI_MSGTYPE_SELECTCHANGED) {
   if (msg.pSender == m_pOptionGeneral && m_pOptionGeneral->IsSelected()) {
    if (m_pTabLayoutMain) {
     m_pTabLayoutMain->SelectItem(int(EnConfigurePageType::General));
     const auto min_size = m_pm.GetMinInfo();
     ::SetWindowPos(GetHWND(), nullptr, 0, 0, min_size.cx, min_size.cy, SWP_NOACTIVATE | SWP_NOMOVE);
    }
   }
   else if (msg.pSender == m_pOptionDown && m_pOptionDown->IsSelected()) {
    if (m_pTabLayoutMain) {
     m_pTabLayoutMain->SelectItem(int(EnConfigurePageType::Down));
     const auto max_size = m_pm.GetMaxInfo();
     ::SetWindowPos(GetHWND(), nullptr, 0, 0, max_size.cx, max_size.cy, SWP_NOACTIVATE | SWP_NOMOVE);
    }
   }
  }
  else if (msg.sType == DUI_MSGTYPE_CLICK) {
   const auto name = msg.pSender->GetName();
   if (!name.Compare(_T("0D641E9F6F01"))) {
    ShowWindow(false);
    Show(false);
   }



  }
  else {

  }
 }



}///namespace local
