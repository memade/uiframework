#if !defined(INC_H___AC508D78_14E1_43F5_A7DD_DE0CB12A7F6D__HEAD__)
#define INC_H___AC508D78_14E1_43F5_A7DD_DE0CB12A7F6D__HEAD__

namespace local {

 enum class EnConfigurePageType {
  General = 0,
  Down = 1,
 };

 class UIConfigure final : public shared::ui::UIFrame , public UIBase {
 public:
  UIConfigure(const UIType&, const bool&);
  ~UIConfigure();
 protected:
  void Init();
  void UnInit();
  void Create() override final;
  void Destory() override final;
  const HWND& Hwnd() const;
  bool IsOpen() const;
 protected:
  void InitWindow() override final;
  void Notify(TNotifyUI& msg) override final;
  void OnFinalMessage(HWND hWnd) override final;
  CControlUI* CreateControl(LPCTSTR pstrClassName) override final;
  LPCTSTR GetWindowClassName() const override final { return _TEXT("uiconfigure"); }
  LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
 private:
  COptionUI* m_pOptionDown = nullptr;
  COptionUI* m_pOptionGeneral = nullptr;
  CTabLayoutUI* m_pTabLayoutMain = nullptr;
  /// 开机自动启动
  COptionUI* m_pOptionStartsAutomaticallyWhenStarts = nullptr;
  /// 启动时自动下载上次未完成的下载
  COptionUI* m_pOptionLastIncompleteDownloadIsDownloadedAutomaticallyAtStartup = nullptr;
  /// 下载完成后自动安装游戏
  COptionUI* m_pOptionAutomaticallyInstalledAfterDownloading = nullptr;
  /// 打开后不显示推广广告
  COptionUI* m_pOptionNoPromotionalAdsAreDisplayedWhenOpened = nullptr;
  /// 每次关闭时不再提醒我
  COptionUI* m_pOptionNoMoreRemindersEverytimeItClosesInClickCloseBtn = nullptr;
  /// 最小化到系统托盘区
  COptionUI* m_pOptionMinimizeToSystemTrayInClickCloseBtn = nullptr;
  /// 立即退出
  COptionUI* m_pOptionExitImmediatelyInClickCloseBtn = nullptr;
  /// 安装包存储路径
  CEditUI* m_pEditPathForStoringTheInstallationPackage = nullptr;
  /// 浏览安装包路径
  CButtonUI* m_pButtonViewTheInstallationPackagePath = nullptr;
  /// 安装路径
  CEditUI* m_pEditProgramInstallationPath = nullptr;
  /// 浏览安装路径
  CButtonUI* m_pButtonViewingTheInstallationPath = nullptr;
  /// 不限制下载速度
  COptionUI* m_pOptionNolimitOnDownloadSpeed = nullptr;
  /// 下载速度阀值
  CEditUI* m_pEditDownloadSpeedThreshold = nullptr;
  /// 自动下载安装包至默认路径
  COptionUI* m_pOptionInstallationPackageAutomaticallyDownloadedToDefaultPath = nullptr;
  /// 安装包保留天数
  COptionUI* m_pOptionTheInstallationPackageIsReservedFor7Days = nullptr;
  COptionUI* m_pOptionTheInstallationPackageIsReservedFor15Days = nullptr;
  /// 安装包永久保留
  COptionUI* m_pOptionTheInstallationPackageIsRetainedPermanently = nullptr;
  /// 下载完成后关机
  COptionUI* m_pOptionShutDownAfterDownloading = nullptr;
  /// 关闭延迟分钟数
  CEditUI* m_pEditDisableDelayInMinutes = nullptr;
 };

}///namespace local

/// /*新生®（上海）**/
/// /*2022_09_10T22:42:48.8706907Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___AC508D78_14E1_43F5_A7DD_DE0CB12A7F6D__HEAD__

