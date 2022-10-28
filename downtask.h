#if !defined(INC_H___1A6471C5_4138_4ACA_86CE_EA737976F331__HEAD__)
#define INC_H___1A6471C5_4138_4ACA_86CE_EA737976F331__HEAD__

namespace local {

 class ITaskCommonData {
 public:
  ITaskCommonData(const TypeID& id) : m_ID(id) {}
 protected:
  ///!@ 本地资源目录
  void* m_RoutePtr = nullptr;
  void* m_BindUI = nullptr;
  void* m_BindUI2 = nullptr;
  void* m_BindPtr = nullptr;
  std::string m_OpenCommandLine;
  std::string m_LocalResDir;
  std::string m_Name;
  std::string m_LogoUrl;
  std::string m_Cmd;
  std::string m_Account = "test_account_123456789";
  unsigned int m_ResType = 0;
  time_t m_ResTime = 0;
  const TypeID m_ID;
  unsigned int m_VipLevel = 0;
  std::string m_Url;
  std::string m_LogoPathname;
  std::string m_FinishPath;
  std::string m_FinishPathname;
  std::string m_DownCacheFilePathname;
  size_t m_ContentLength = 0;
  std::atomic<EnTaskType> m_TaskType = EnTaskType::Unknow;
  std::atomic<EnActionType> m_ActionType = EnActionType::Normal;
  std::atomic<EnActionType> m_ActionTypePrev = EnActionType::Normal;
  long long m_DownLimitSpeed = 5 * 1024 * 1024;
 };

 class TaskResult final : public ITaskResultStatus {
  friend class TaskNode;
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  TaskResult() {}
 protected:
  const double& down_total() const override final;
  const double& down_current() const override final;
  const double& down_speed_s() const override final;
  const double& down_percentage() const override final;
  const long long& down_time_s() const override final;

  const long long& extract_total() const override final;
  const long long& extract_current() const override final;
  const long long& extract_percentage() const override final;
  const long long& extract_time_s() const override final;

  const std::string& FinishPath() const override final;
  const std::string& FinishPathname() const override final;

  void operator<<(const tagTaskmanMsg::tagDetails&) override final;
  void operator<<(const EXTRACTPROGRESSINFO&) override final;
 private:
  /// IProgressInfo
  double m_down_total = 0;
  double m_down_current = 0;
  double m_down_speed_s = 0;
  long long m_down_time_s = 0;
  double m_down_percentage = 0;
  /// IResponse
  long long m_extract_total = 0;
  long long m_extract_current = 0;
  long long m_extract_time_s = 0;
  long long m_extract_percentage = 0;

  std::string m_FinishPath;
  std::string m_FinishPathname;
 private:
  void operator<<(const libcurlpp::IProgressInfo*);
  void operator<<(const libcurlpp::IResponse*);
 };
 class TaskNode final : public ITaskNode, public ITaskCommonData {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  TaskNode(const TypeID&);
  TaskNode(const TypeID&, const std::string& json_data);
  virtual ~TaskNode();
 public:
  const TypeID& ID() const override final;
  void Url(const std::string&) override final;
  const std::string& Url() const override final;
  void LogoUrl(const std::string&) override final;
  const std::string& LogoUrl() const override final;
  void LogoPathname(const std::string&) override final;
  const std::string& LogoPathname() const override final;
  EnActionType Status() const override final;
  void Action(const EnActionType&) override final;
  bool Verify() const override final;
  const unsigned int& VipLevel() const override final;
  void VipLevel(const unsigned int&) override final;
  void LocalResDir(const std::string&) override final;
  const std::string& LocalResDir() const override final;
  void Name(const std::string&) override final;
  const std::string& Name() const override final;
  void DownCacheFilePathname(const std::string&) override final;
  const std::string& DownCacheFilePathname() const override final;
  void FinishPath(const std::string&) override final;
  const std::string& FinishPath() const override final;
  void FinishPathname(const std::string&) override final;
  const std::string& FinishPathname() const override final;
  void OpenCommandLine(const std::string&) override final;
  void operator<<(const EXTRACTPROGRESSINFO&) override final;
  void operator<<(const tagTaskmanMsg::tagDetails&) override final;
  void RoutePtr(void*) override final;
  void BindUI(void*) override final;
  void* RoutePtr() const override final;
  void* BindUI() const override final;
  void BindUI2(void*) override final;
  void* BindUI2() const override final;
  void BindPtr(void*) override final;
  void* BindPtr() const override final;
  void DownLimitSpeed(const long long&/*b*/) override final;
  ITaskResultStatus* Result() const  override final;
  void Release() const override final;
  bool Preparation() override final;
  bool Perform() override final;
  bool Install() override final;
 public:
  EnActionType Action() const;
  EnActionType ActionPrev() const;
  EnActionType StatusPrev() const;
  void TaskType(const EnTaskType&);
  bool IsPost();
 protected:
  libcurlpp::IRequest* m_pHeadRequest = nullptr;
  libcurlpp::IRequest* m_pDownRequest = nullptr;
  libcurlpp::IRequest* m_pReadyRequest = nullptr;
  TaskResult* m_pTaskResult = nullptr;
 private:
  std::set<EnActionType> m_ActionPostedQ;

#if 0
 public:
  IDownTaskElement* UIDownTaskElementCreate();
  IDownTaskElement* UIDownTaskElementGet() const;
  DownActionType Action() const;
  /// @Preparation()
  /// 1.请求资源头部信息 获取资源数据情况
  /// 2.请求Logo相关资源
  /// 3.本类初始化工作
  bool Preparation();
  bool Start();
  bool Stop();
  bool Pause();
  void SetStatusText(const std::wstring&, const DWORD& color = CommonColorMap.at(CommonColorType::White));
  void SetResourceSizeText(const size_t& total, const size_t& current, const DWORD& color = CommonColorMap.at(CommonColorType::White));
 private:
  IDownTaskElement* m_pUIDownTaskElement = nullptr;
 private:
  std::atomic_bool m_IsOpenThread = false;
  __int64 m_ResourceTotalSize = 0;
  shared::container::queue<ProgressRoute> m_ProgressRouteQ;
  void OnProgressChanged();
  std::vector<std::thread> m_Threads;
#endif
 };


#if 0
 class IDownTaskElement : public CListContainerElementUI {
 public:
  static IDownTaskElement* Create();
 public:
  void StatusTextSet(const std::wstring&, const DWORD& color = 0);
  void ResourceSizeTextSet(const size_t& total, const size_t& current, const DWORD& color = 0);
  void DownTotalTimeTextSet(const std::wstring&, const DWORD& color = 0);
  void SetName(const std::wstring&, const DWORD& color = 0);
  void SetLogo(const std::wstring& logo_pathname);
  void SetProgressValue(const size_t& total, const size_t& current);
  void SetDownSpeedValue(const size_t&);
  void SetDownloadCompletionRate(const size_t& size_totoal, const size_t& size_current);
  void SetDownSpeedValueVip(const size_t& real_speed/*-200kb*/);
  void SetDownDownTimeRemain(const size_t& size_remain, const size_t& current_down_speed_value = NormalUserLimitDownSpeedValue, const DWORD& color = 0);
  void StartingSwitch(const bool&);
 };
#endif
}///namespace local 

/// /*新生®（上海）**/
/// /*2022_09_12T01:54:44.1160141Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___1A6471C5_4138_4ACA_86CE_EA737976F331__HEAD__
