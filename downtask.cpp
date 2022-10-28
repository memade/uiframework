#include "stdafx.h"

namespace local {
 TaskNode::TaskNode(const TypeID& task_id) :
  ITaskCommonData(task_id),
  m_pTaskResult(new TaskResult()),
  m_pHeadRequest(Global::HttpGet()->CreateRequest()),
  m_pReadyRequest(Global::HttpGet()->CreateRequest()),
  m_pDownRequest(Global::HttpGet()->CreateRequest())
 {

 }
 TaskNode::TaskNode(const TypeID& task_id, const std::string& gbk_json_data) :
  ITaskCommonData(task_id),
  m_pTaskResult(new TaskResult()),
  m_pHeadRequest(Global::HttpGet()->CreateRequest()),
  m_pReadyRequest(Global::HttpGet()->CreateRequest()),
  m_pDownRequest(Global::HttpGet()->CreateRequest())
 {
  do {
   if (gbk_json_data.empty())
    break;
#if 0
   {
    "module":"runGame",
     "vip" : 1,
     "gameId" : 3,
     "gameName" : "战地1942.rar",
     "gameTime" : 120,
     "type" : 0,
     "ico" : "http://test.xitieba.com//admin/images/未标题-1.jpg",
     "url" : "https://ss.bscstorage.com/goodgame-mifang9ku/yxdown.com_BF1942_en.rar",
     "cmd" : ""
   }
#endif
   rapidjson::Document doc;
   if (doc.Parse(gbk_json_data.data(), gbk_json_data.size()).HasParseError())
    break;
   if (!doc.IsObject())
    break;
   if (doc.HasMember("vip") && doc["vip"].IsNumber())
    m_VipLevel = doc["vip"].GetUint();
#if 0
   if (doc.HasMember("gameId") && doc["gameId"].IsNumber())
    m_ID = doc["gameId"].GetUint();
#endif
   if (doc.HasMember("gameName") && doc["gameName"].IsString())
    m_Name = doc["gameName"].GetString();
   if (doc.HasMember("gameTime") && doc["gameTime"].IsNumber())
    m_ResTime = doc["gameTime"].GetInt64();
   if (doc.HasMember("type") && doc["type"].IsNumber())
    m_ResType = doc["type"].GetUint();
   if (doc.HasMember("ico") && doc["ico"].IsString())
    m_LogoUrl = doc["ico"].GetString();
   if (doc.HasMember("url") && doc["url"].IsString())
    m_Url = doc["url"].GetString();
   if (doc.HasMember("cmd") && doc["cmd"].IsString())
    m_Cmd = doc["cmd"].GetString();
   if (doc.HasMember("account") && doc["account"].IsString())
    m_Account = doc["account"].GetString();
  } while (0);
 }
 TaskNode::~TaskNode() {
  Global::HttpGet()->DestoryRequest(m_pHeadRequest);
  Global::HttpGet()->DestoryRequest(m_pReadyRequest);
  Global::HttpGet()->DestoryRequest(m_pDownRequest);
 }
 void TaskNode::Release() const {
  delete this;
 }
 void TaskNode::LocalResDir(const std::string& path) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_LocalResDir = path;
 }
 const std::string& TaskNode::LocalResDir() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_LocalResDir;
 }
 void TaskNode::DownLimitSpeed(const long long& speed_b/*b*/) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_DownLimitSpeed = speed_b;
  m_pDownRequest->MaxRecvSpeedLarge(m_DownLimitSpeed);
 }
 void* TaskNode::RoutePtr() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_RoutePtr;
 }
 void TaskNode::BindUI2(void* bindui2) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_BindUI2 = bindui2;
 }
 void* TaskNode::BindUI2() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_BindUI2;
 }
 void TaskNode::BindPtr(void* ptr) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_BindPtr = ptr;
 }
 void* TaskNode::BindPtr() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_BindPtr;
 }

 void* TaskNode::BindUI() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_BindUI;
 }
 void TaskNode::BindUI(void* bind_ui) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_BindUI = bind_ui;
 }
 void TaskNode::RoutePtr(void* route_ptr) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_RoutePtr = route_ptr;
 }
 void TaskResult::operator<<(const libcurlpp::IProgressInfo* info) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!info)
    break;
   m_down_total = info->total();
   m_down_current = info->current();
   m_down_percentage = info->percentage();
   auto time_s = info->time_s();
   auto speed_s = info->speed_s();

   if (time_s > 0)
    m_down_time_s = time_s;
   if (speed_s > 0)
    m_down_speed_s = speed_s;
  } while (0);
 }
 void TaskResult::operator<<(const libcurlpp::IResponse* res) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!res)
    break;


  } while (0);
 }
 const std::string& TaskResult::FinishPath() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_FinishPath;
 }
 const std::string& TaskResult::FinishPathname() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_FinishPathname;
 }
 const double& TaskResult::down_total() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_down_total;
 }
 const double& TaskResult::down_current() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_down_current;
 }
 const double& TaskResult::down_speed_s() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_down_speed_s;
 }
 const double& TaskResult::down_percentage() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_down_percentage;
 }
 const long long& TaskResult::down_time_s() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_down_time_s;
 }
 const long long& TaskResult::extract_total() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_extract_total;
 }
 void TaskResult::operator<<(const tagTaskmanMsg::tagDetails& details) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_FinishPath = shared::Win::GetPathByPathnameA(details.StartupPEPathname);
  m_FinishPathname = details.StartupPEPathname;
 }
 void TaskResult::operator<<(const EXTRACTPROGRESSINFO& extract_progress_info) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_extract_total = extract_progress_info.extract_total;
  m_extract_current = extract_progress_info.extract_current;
  m_extract_time_s = extract_progress_info.extract_time_s;
  m_extract_percentage = extract_progress_info.extract_percentage;
 }
 const long long& TaskResult::extract_current() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_extract_current;
 }
 const long long& TaskResult::extract_percentage() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_extract_percentage;
 }
 const long long& TaskResult::extract_time_s() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_extract_time_s;
 }
 void TaskNode::TaskType(const EnTaskType& task_type) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_TaskType.store(task_type);
 }
 ITaskResultStatus* TaskNode::Result() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return dynamic_cast<ITaskResultStatus*>(m_pTaskResult);
 }
 const std::string& TaskNode::DownCacheFilePathname() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_DownCacheFilePathname;
 }
 void TaskNode::DownCacheFilePathname(const std::string& pathname) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_DownCacheFilePathname = pathname;
 }
 void TaskNode::OpenCommandLine(const std::string& commandline) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_OpenCommandLine = commandline;
 }
 const std::string& TaskNode::Name() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Name;
 }
 void TaskNode::Name(const std::string& name) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_Name = name;
 }
 void TaskNode::operator<<(const tagTaskmanMsg::tagDetails& details) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  if (m_pTaskResult)
   *m_pTaskResult << details;
 }
 void TaskNode::operator<<(const EXTRACTPROGRESSINFO& progress_info) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  if (m_pTaskResult)
   *m_pTaskResult << progress_info;
 }
 const TypeID& TaskNode::ID() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ID;
 }
 bool TaskNode::Verify() const {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (m_ID <= 0)
    break;
   if (m_Url.empty())
    break;
   /*if (!m_pRequestObj)
    break;*/
   result = true;
  } while (0);
  return result;
 }
 void TaskNode::Url(const std::string& url) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_Url = url;
  if (m_pDownRequest)
   m_pHeadRequest->RequestUrl(url);
  m_pDownRequest->RequestUrl(url);
 }
 const std::string& TaskNode::LogoUrl() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_LogoUrl;
 }
 void TaskNode::LogoUrl(const std::string& url) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_LogoUrl = url;
  if (m_pReadyRequest)
   m_pReadyRequest->RequestUrl(m_LogoUrl);
 }
 const std::string& TaskNode::Url() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Url;
 }
 const unsigned int& TaskNode::VipLevel() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_VipLevel;
 }
 void TaskNode::VipLevel(const unsigned int& level) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_VipLevel = level;
 }
 const std::string& TaskNode::LogoPathname() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_LogoPathname;
 }
 void TaskNode::LogoPathname(const std::string& logo_buffer) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_LogoPathname = logo_buffer;
 }
 EnActionType TaskNode::Action() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ActionType.load();
 }
 EnActionType TaskNode::ActionPrev() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ActionTypePrev.load();
 }
 EnActionType TaskNode::StatusPrev() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ActionTypePrev.load();
 }
 EnActionType TaskNode::Status() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ActionType.load();
 }
 void TaskNode::FinishPathname(const std::string& pathname) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_FinishPathname = pathname;
 }
 const std::string& TaskNode::FinishPathname() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_FinishPathname;
 }
 void TaskNode::FinishPath(const std::string& path) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_FinishPath = path;
 }
 const std::string& TaskNode::FinishPath() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_FinishPath;
 }
 void TaskNode::Action(const EnActionType& set_action) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_ActionTypePrev.store(m_ActionType.load());
  m_ActionType.store(set_action);
 }
 bool TaskNode::IsPost() {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  if (m_ActionType == EnActionType::DownBeworking) {
   result = true;
  }
  else if (m_ActionType == EnActionType::InstallBeworking) {
   result = true;
  }
  else {
   auto found = m_ActionPostedQ.find(m_ActionType);
   if (found == m_ActionPostedQ.end()) {
    m_ActionPostedQ.emplace(m_ActionType);
    result = true;
   }
  }
  return result;
 }
 bool TaskNode::Install() {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   //!@ 创建安装进程
   //! 
   //! 
   std::string process_pathname;
   std::string commandline;
   commandline
    .append(componects_taskman::mapCommandLineIdentify.at(componects_taskman::EnCmdType::Verify))
    .append("=").append(componects_taskman::STARUP_VERIFY)
    .append(" ");

   commandline
    .append(componects_taskman::mapCommandLineIdentify.at(componects_taskman::EnCmdType::TaskId))
    .append("=").append(std::to_string(m_ID))
    .append(" ");

#ifdef _DEBUG
   process_pathname = R"(D:\__Github__\Windows\projects\pchacker\res\Taskman.exe)";
#else
   process_pathname = shared::Win::GetModulePathA(__gpHinstance) + "Taskman.exe";
#endif

   if (!shared::Win::AccessA(process_pathname))
    break;

#if 1 // 发行算法
   if (Global::PCHackerGet()->m_TaskmanPtrQ.search(m_ID))
    break;
   shared::Win::Process::CreateA(
    process_pathname,
    commandline,
    [&](const HANDLE&, const DWORD& create_pid) {
     auto pTaskman = new Taskman(m_ID);
     pTaskman->InPathname(m_DownCacheFilePathname);
     pTaskman->OutPath(shared::Win::GetPathByPathnameA(m_FinishPathname) + std::to_string(m_ID) + "\\");
     Global::PCHackerGet()->m_TaskmanPtrQ.push(m_ID, pTaskman);
     result = true;
    }, true, false, 0);
#else //!@ 调试算法
   auto pTaskman = new Taskman(m_ID);
   pTaskman->InPathname(m_DownCacheFilePathname);
   pTaskman->OutPath(shared::Win::GetPathByPathnameA(m_FinishPathname) + std::to_string(m_ID) + "\\");
   Global::PCHackerGet()->m_TaskmanPtrQ.push(m_ID, pTaskman);
#endif

  } while (0);
  return result;
 }
 bool TaskNode::Perform() {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (m_ActionType.load() == EnActionType::DownBeworking) {
    result = true;
    break;
   }
   m_ActionTypePrev.store(m_ActionType.load());
   m_ActionType.store(EnActionType::DownBeworking);
   if (!m_pDownRequest)
    break;
   m_pDownRequest->Header(false);
   m_pDownRequest->EnableWriteStream(false);
   m_pDownRequest->RequestType(libcurlpp::EnRequestType::REQUEST_TYPE_GET);
   m_pDownRequest->CachePathname(m_DownCacheFilePathname);
   m_pDownRequest->ProgressCb(
    [&](const libcurlpp::IProgressInfo* pDownProgressInfo, const libcurlpp::IProgressInfo*)->libcurlpp::ProgressActionType {
     libcurlpp::ProgressActionType result = libcurlpp::ProgressActionType::Continue;
     if (m_pTaskResult)
      *m_pTaskResult << pDownProgressInfo;
     if (m_ActionType.load() == EnActionType::DownStop) {
      m_ActionTypePrev.store(m_ActionType.load());
      m_ActionType.store(EnActionType::DownStopd);
      result = libcurlpp::ProgressActionType::Break;
     }
     return result;
    });
   m_pDownRequest->FinishCb(
    [&](const libcurlpp::IResponse* resObj) {
     if (m_pTaskResult) {
      *m_pTaskResult << resObj;
     }
     if (resObj->HttpCode() == 200) {
      m_ActionTypePrev.store(m_ActionType.load());
      m_ActionType.store(EnActionType::DownFinished);
     }
     else if (resObj->HttpCode() == 416) {
      m_ActionTypePrev.store(m_ActionType.load());
      m_ActionType.store(EnActionType::DownFinished);
     }
     else {
      m_ActionTypePrev.store(m_ActionType.load());
      m_ActionType.store(EnActionType::DownFailed);
     }
    });
   m_pDownRequest->Action(libcurlpp::EnRequestAction::Start);
   result = true;
  } while (0);
  if (!result) {
   m_ActionTypePrev.store(m_ActionType.load());
   m_ActionType.store(EnActionType::DownFailed);
  }
  return result;
 }
 bool TaskNode::Preparation() {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_ActionTypePrev.store(m_ActionType.load());
  m_ActionType.store(EnActionType::DownInPreparation);
  do {
   if (!m_pDownRequest || !m_pReadyRequest)
    break;
   if (m_ID <= 0)
    break;
   if (m_Url.empty())
    break;
   std::string file_name;
   std::string file_format;
   shared::Win::GetFileNameAndFormat(m_LogoUrl, file_name, file_format);
   file_format += Global::PCHackerGet()->ConfigureGet()->DefaultDownloadCacheFileFormat();
   m_LogoPathname = shared::Win::PathFixedA(Global::PCHackerGet()->ConfigureGet()->DownPreparedResourcePath() + std::to_string(m_ID) + file_format);
   //!@ 初始化最终下载文件名
   shared::Win::GetFileNameAndFormat(m_Url, file_name, file_format);
   file_format += Global::PCHackerGet()->ConfigureGet()->DefaultDownloadCacheFileFormat();
   m_FinishPathname = shared::Win::PathFixedA(Global::PCHackerGet()->ConfigureGet()->FinishInstalledPath() + std::to_string(m_ID) + file_format);
   //!@ 初始化下载缓冲文件路径名
   m_DownCacheFilePathname = shared::Win::PathFixedA(Global::PCHackerGet()->ConfigureGet()->DownResourceCachePath() + std::to_string(m_ID) + file_format);

   shared::Win::CreateDirectoryA(shared::Win::GetPathByPathnameA(m_LogoPathname));
   shared::Win::CreateDirectoryA(shared::Win::GetPathByPathnameA(m_FinishPathname));
   shared::Win::CreateDirectoryA(shared::Win::GetPathByPathnameA(m_DownCacheFilePathname));

   m_pReadyRequest->HeadersAdd(R"(content-type: application/x-www-form-urlencoded)");
   m_pReadyRequest->EnableWriteStream(true);
   m_pReadyRequest->FinishCb(
    [&](const libcurlpp::IResponse* resObj) {
     do {
      if (resObj->HttpCode() != 200)
       break;
      const auto& body = resObj->Body();
      if (body.empty())
       break;
      shared::Win::File::Write(m_LogoPathname, body);
     } while (0);
    });
   m_pHeadRequest->Header(true);
   m_pHeadRequest->EnableWriteStream(true);
   m_pHeadRequest->RequestType(libcurlpp::EnRequestType::REQUEST_TYPE_HEAD);
   m_pHeadRequest->FinishCb(
    [&](const libcurlpp::IResponse* resObj) {
     do {
      if (resObj->HttpCode() != 200) {
       m_ActionTypePrev.store(m_ActionType.load());
       m_ActionType.store(EnActionType::DownFailed);
       break;
      }
      m_ContentLength = resObj->ContentLength();
      result = true;
      m_ActionTypePrev.store(m_ActionType.load());
      m_ActionType.store(EnActionType::DownReady);
     } while (0);
    });

   Global::HttpGet()->Perform(m_pReadyRequest);
   Global::HttpGet()->Perform(m_pHeadRequest);

   //Global::HttpGet()->PerformM({ m_pReadyRequest,m_pHeadRequest });
  } while (0);
  if (!result) {
   m_ActionTypePrev.store(m_ActionType.load());
   m_ActionType.store(EnActionType::DownFailed);
  }
  return result;
 }



#if 0
 IDownTaskElement* TaskNode::UIDownTaskElementCreate() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  CDialogBuilder builder;
  m_pUIDownTaskElement = builder.Create<IDownTaskElement>(LR"(nodes\uidwontasknode.xml)");
  if (!m_Name.empty())
   m_pUIDownTaskElement->SetName(shared::IConv::MBytesToWString(m_Name));
  return m_pUIDownTaskElement;
 }
 IDownTaskElement* TaskNode::UIDownTaskElementGet() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_pUIDownTaskElement;
 }
 DownActionType TaskNode::Action() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ActionType.load();
 }
 bool TaskNode::Pause() {
  return Stop();
 }
 bool TaskNode::Start() {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
#if 0
  do {
   if (m_ActionType != EnDownActionType::Start)
    break;

   if (!m_IsOpenThread.load()) {
    m_IsOpenThread.store(true);
    m_Threads.emplace_back([this]() {OnProgressChanged(); });
   }
   //!@ 任务节点开始下载
   auto pReqObj = Global::PCDownGet()->HttpObj()->RouteCreate();
   if (!pReqObj)
    break;
   pReqObj->Push(
    [&](shared::http::RequestObj* reqObj) {
     do {
      auto fixUrl = shared::Win::UrlFixedByDowntool(m_Url);
      reqObj->Url(fixUrl);
      reqObj->Type(shared::http::EnRequestType::EN_REQUEST_TYPE_DOWN);
      reqObj->Header(false);
      if (m_VipLevel <= 0)
       reqObj->MaxRecvSpeedLarge(NormalUserLimitDownSpeedValue);
      reqObj->TimeoutResponseMS(10 * 1000);//!@ 超时
      reqObj->DownCacheFilePathname(m_DownCacheFilePathname);
      reqObj->ResultCb(
       [&](const shared::http::RequestObj* reqObj, const shared::http::ResponseObj* resObj) {

        auto sk = 0;
       });
      //!@ dltotal + ResumeFromLarge, dlnow + ResumeFromLarge, ultotal, ulnow, nullptr
      reqObj->ProgressCb(
       [&](
        const __int64& dltotal/*+ ResumeFromLarge*/,
        const __int64& dlnow/*+ ResumeFromLarge*/,
        const __int64& ultotal,
        const __int64& ulnow,
        void*)->int {
         int result = static_cast<int>(shared::http::EnDownProgressStatus::EN_DOWN_PROGRESS_STATUS_ON);
         do {
          m_ProgressRouteQ.push(ProgressRoute(dltotal, dlnow, ultotal, ulnow));
         } while (0);
         return result;
       });
     } while (0);
     return true;
    });

   if (!Global::PCDownGet()->HttpObj()->Perform(pReqObj))
    break;

   if (!m_pUIDownTaskElement)
    break;
   m_pUIDownTaskElement->StartingSwitch(true);
   m_ActionType = EnDownActionType::Running;
   m_pUIDownTaskElement->StatusTextSet(CommonStringMap.at(CommonStringType::Downing));
   result = true;
  } while (0);
#endif
  return result;
 }
 bool TaskNode::Stop() {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (m_ActionType != EnDownActionType::Stop && m_ActionType != EnDownActionType::Pause)
    break;
   if (!m_pUIDownTaskElement)
    break;
   m_pUIDownTaskElement->StartingSwitch(false);

   m_pUIDownTaskElement->SetDownDownTimeRemain(0, 0);
   m_pUIDownTaskElement->StatusTextSet(CommonStringMap.at(CommonStringType::DownTaskStop));
   m_ActionType = EnDownActionType::Stop;
   result = true;
  } while (0);

  m_IsOpenThread.store(false);
  for (auto& t : m_Threads)
   t.join();
  m_Threads.clear();
  return result;
 }
 bool TaskNode::Preparation() {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (m_ID <= 0)
    break;
   if (m_Url.empty())
    break;
   std::string file_name;
   std::string file_format;
   shared::Win::GetFileNameAndFormat(m_LogoUrl, file_name, file_format);
   m_LogoPathname = shared::Win::PathFixedA(Global::PCHackerGet()->SystemDirectoryA() + "\\logos\\" + std::to_string(m_ID) + file_format);
   //!@ 初始化最终下载文件名
   shared::Win::GetFileNameAndFormat(m_Url, file_name, file_format);
   m_FinishPathname = shared::Win::PathFixedA(Global::PCHackerGet()->SystemDirectoryA() + "\\finishs\\" + std::to_string(m_ID) + file_format);
   //!@ 初始化下载缓冲文件路径名
   m_DownCacheFilePathname = shared::Win::PathFixedA(Global::PCHackerGet()->SystemDirectoryA() + "\\caches\\" + std::to_string(m_ID) + file_format);


#if 0
   auto reqHead = Global::HttpGet()->CreateRequest();
   reqHead->RequestUrl(m_Url);
   reqHead->Header(true);
   reqHead->RequestType(malware::http::EnRequestType::REQUEST_TYPE_HEAD);
   reqHead->FinishCb(
    [&](const malware::http::IResponse* resObj) {


     result = true;
    });
   auto reqLogo = Global::HttpGet()->CreateRequest();
   reqLogo->RequestUrl(m_LogoUrl);
   reqLogo->RequestType(malware::http::EnRequestType::REQUEST_TYPE_GET);
   //reqLogo->HeadersAdd(R"(content-type: application/x-www-form-urlencoded)");
   reqLogo->FinishCb(
    [&](const malware::http::IResponse* resObj) {

     auto sk = 0;
    });
   Global::HttpGet()->PerformM({ reqLogo,reqHead });
   Global::HttpGet()->DestoryRequest({ reqLogo,reqHead });

#endif

#if 0
   auto pReqObj = Global::PCDownGet()->HttpObj()->RouteCreate();
   if (!pReqObj)
    break;
   if (!m_LogoUrl.empty() && !shared::Win::AccessA(m_LogoPathname)) {
    pReqObj->Push(
     [this](shared::http::RequestObj* reqObj) {
      auto fixUrl = shared::Win::UrlFixedByDowntool(shared::IConv::MBytesToUTF8(m_LogoUrl));
      reqObj->Url(fixUrl);
      reqObj->HttpHeaderAppend({ {"content-type", "application/x-www-form-urlencoded"} });
      reqObj->Type(shared::http::EnRequestType::EN_REQUEST_TYPE_GET);
      reqObj->ResultCb(
       [&](const shared::http::RequestObj* reqObj, const shared::http::ResponseObj* resObj) {
        do {
         if (resObj->HttpCode() != 200)
          break;
         shared::Win::File::Write(m_LogoPathname, resObj->ContentBody());
        } while (0);
       });
      return true;
     });
   }

   pReqObj->Push(
    [&](shared::http::RequestObj* reqObj) {
     auto fixUrl = shared::Win::UrlFixedByDowntool(shared::IConv::MBytesToUTF8(m_Url));
     reqObj->Url(fixUrl);
     reqObj->Type(shared::http::EnRequestType::EN_REQUEST_TYPE_HEAD);
     reqObj->ResultCb(
      [this, &result](const shared::http::RequestObj* reqObj, const shared::http::ResponseObj* resObj) {
       do {
        if (!resObj)
         break;
        if (resObj->HttpCode() != 200)
         break;
        m_ResourceTotalSize = resObj->ContentLength();
        result = m_ResourceTotalSize > 0;
       } while (0);
       if (!result) {
        m_Status = EnTaskStatus::Error;
        m_ActionType = EnDownActionType::Pause;
       }
      });
     return true;
    });
   Global::PCDownGet()->HttpObj()->Perform(pReqObj);
  } while (0);

  do {
   if (!m_pUIDownTaskElement)
    break;
   //!@ 设置资源(游戏)Logo
   if (shared::Win::AccessA(m_LogoPathname))
    m_pUIDownTaskElement->SetLogo(shared::IConv::MBytesToWString(m_LogoPathname));

   if (!result)
    break;
   //!@ 设置资源大小
   m_pUIDownTaskElement->ResourceSizeTextSet(static_cast<size_t>(m_ResourceTotalSize), 0);
   //!@ 初始化进度条数值
   m_pUIDownTaskElement->SetProgressValue(0, 0);
   //!@ 初始化实时下载速度
   m_pUIDownTaskElement->SetDownSpeedValue(0);
   //!@ 初始化VIP加速度
   m_pUIDownTaskElement->SetDownSpeedValueVip(0);
   //!@ 初始化[预测下载时间]
   m_pUIDownTaskElement->SetDownDownTimeRemain(static_cast<size_t>(m_ResourceTotalSize), \
    NormalUserLimitDownSpeedValue);
#endif


  } while (0);

  return result;
 }

 void TaskNode::SetStatusText(const std::wstring& text, const DWORD& color /*= CommonColorMap.at(CommonColorType::White)*/) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_pUIDownTaskElement)
    break;
   m_pUIDownTaskElement->StatusTextSet(text, color);
  } while (0);
 }
 void TaskNode::SetResourceSizeText(const size_t& total, const size_t& current, const DWORD& color /*= CommonColorMap.at(CommonColorType::White)*/) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_pUIDownTaskElement)
    break;
   m_pUIDownTaskElement->ResourceSizeTextSet(total, current, color);
  } while (0);
 }

 void TaskNode::OnProgressChanged() {
  const time_t calc_down_speed_interval = 500;
  volatile time_t prev_time_mark = shared::Win::Time::TimeStamp<std::chrono::milliseconds>();
  volatile __int64 prev_down_total = 0;//!@ 前一次下载量
  volatile __int64 prev_down_current = 0;
  do {

   do {
    if (m_ProgressRouteQ.empty())
     break;
    auto routes = m_ProgressRouteQ.pops();
    for (auto it = routes.begin(); it != routes.end(); ++it) {
     const auto current_time_ms = shared::Win::Time::TimeStamp<std::chrono::milliseconds>();
     do {
      if (it->dlnow == prev_down_total)
       break;
      if (!m_pUIDownTaskElement)
       break;
      m_pUIDownTaskElement->SetDownloadCompletionRate(static_cast<size_t>(it->dltotal), static_cast<size_t>(it->dlnow));
      m_pUIDownTaskElement->SetDownDownTimeRemain(static_cast<size_t>(it->dltotal) - static_cast<size_t>(it->dlnow));
      m_pUIDownTaskElement->ResourceSizeTextSet(static_cast<size_t>(it->dltotal), static_cast<size_t>(it->dlnow));
      m_pUIDownTaskElement->SetProgressValue(static_cast<size_t>(it->dltotal), static_cast<size_t>(it->dlnow));


      do {//!@ 计算下载速度
       if (current_time_ms - prev_time_mark < calc_down_speed_interval)
        break;
       if (it->dlnow < prev_down_total)
        break;
       if (m_VipLevel > 0) {
        size_t noVip = static_cast<size_t>((it->dlnow - prev_down_current) / 3 * 1);
        size_t Vip = static_cast<size_t>((it->dlnow - prev_down_current) / 3 * 2);
        m_pUIDownTaskElement->SetDownSpeedValue(noVip);
        m_pUIDownTaskElement->SetDownSpeedValueVip(Vip);
       }
       else
       {
        m_pUIDownTaskElement->SetDownSpeedValue(static_cast<size_t>(it->dlnow - prev_down_current));
       }

       prev_time_mark = current_time_ms;
       prev_down_current = it->dlnow;
      } while (0);

      prev_down_total = it->dlnow;
     } while (0);

    }

   } while (0);



   if (!m_IsOpenThread.load())
    break;
   std::this_thread::sleep_for(std::chrono::milliseconds(100));
   prev_time_mark += 100;
  } while (1);
 }



#endif






#if 0
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////
 void IDownTaskElement::SetDownDownTimeRemain(const size_t& size_remain,
  const size_t& current_down_speed_value /*= NormalUserLimitDownSpeedValue*/, const DWORD& color /*= 0*/) {
  do {
   auto ui = GetSubCtrl<CLabelUI>(L"D1C4FD362124");
   if (!ui)
    break;
   std::wstring time_text = L"--:--:--";
   if (size_remain > 0 && current_down_speed_value > 0) {
    time_t total_s = size_remain / current_down_speed_value;
    time_text = shared::IConv::MBytesToWString(shared::Win::Time::TimePeriodUnMade(static_cast<UINT>(total_s)));
   }
   ui->SetText(time_text.c_str());
   if (color)
    ui->SetTextColor(color);
  } while (0);
 }
 void IDownTaskElement::SetDownloadCompletionRate(const size_t& total, const size_t& current) {
  std::wstring text = L"0.0%";
  CLabelUI* ui_label = nullptr;
  CProgressUI* ui_progress = nullptr;
  do {
   ui_progress = GetSubCtrl<CProgressUI>(L"90352B27A442");
   ui_label = GetSubCtrl<CLabelUI>(L"56E157AE72A8");
   if (!ui_progress || !ui_label)
    break;
   if (total <= 0 || current <= 0)
    break;
   const auto max = ui_progress->GetMaxValue();
   double current_progress = (current * 1.0) / (total * 1.0);
   int value = static_cast<int>(current_progress * max);
   double RatioProgress = current_progress * max / 100.0;
   text = std::format(L"{:.2f}%", RatioProgress);
  } while (0);
  if (ui_label)
   ui_label->SetText(text.c_str());
 }
 void IDownTaskElement::StartingSwitch(const bool& status) {
  do {
   auto ui = GetSubCtrl<COptionUI>(L"06A057E7350B");
   if (!ui)
    break;
   auto current_status = ui->IsSelected();
   if (current_status == status)
    break;
   ui->Selected(status);
  } while (0);
 }
 void IDownTaskElement::SetLogo(const std::wstring& logo_pathname) {
  do {
   if (!shared::Win::AccessW(logo_pathname))
    break;
   auto ui = GetSubCtrl<CLabelUI>(L"CCB822F77204");
   if (!ui)
    break;
   ui->SetBkImage(logo_pathname.c_str());
  } while (0);
 }
 void IDownTaskElement::SetDownSpeedValueVip(const size_t& real_speed/*-NormalUserLimitDownSpeedValue*/) {
  do {
   auto ui = GetSubCtrl<CLabelUI>(L"F5E1F8FAD133");
   if (!ui)
    break;
   auto speed = shared::Win::RealtimeSpeed(real_speed);
   ui->SetText(shared::IConv::MBytesToWString(speed).c_str());
  } while (0);
 }
 void IDownTaskElement::SetDownSpeedValue(const size_t& value) {
  do {
   auto ui = GetSubCtrl<CLabelUI>(L"76E1ED97A767");
   if (!ui)
    break;
   auto speed = shared::Win::RealtimeSpeed(value);
   ui->SetText(shared::IConv::MBytesToWString(speed).c_str());
  } while (0);
 }
 void IDownTaskElement::SetProgressValue(const size_t& total, const size_t& current) {
  do {
   if (total <= 0 || current <= 0)
    break;
   auto ui = GetSubCtrl<CProgressUI>(L"90352B27A442");
   if (!ui)
    break;
   const auto max = ui->GetMaxValue();
   double current_progress = (current * 1.0) / (total * 1.0);
   int value = static_cast<int>(current_progress * max);
   ui->SetValue(static_cast<int>(value));
  } while (0);
 }
 void IDownTaskElement::SetName(const std::wstring& name, const DWORD& color) {
  do {
   auto ui = GetSubCtrl<CLabelUI>(L"DD0FB204BE1D");
   if (!ui)
    break;
   ui->SetText(name.c_str());
   if (color)
    ui->SetTextColor(color);
  } while (0);
 }
 void IDownTaskElement::StatusTextSet(const std::wstring& text, const DWORD& color) {
  do {
   auto ui = GetSubCtrl<CLabelUI>(L"E509EB1128BD");
   if (!ui)
    break;
   ui->SetText(text.c_str());
   if (color)
    ui->SetTextColor(color);
  } while (0);
 }
 void IDownTaskElement::ResourceSizeTextSet(const size_t& total, const size_t& current, const DWORD& color) {
  do {
   auto ui = GetSubCtrl<CLabelUI>(L"E4BD5BC33011");
   if (!ui)
    break;
   if (total <= 0 && current <= 0) {
    ui->SetText(L"--/--");
    break;
   }
   auto realTotal = shared::Win::RealtimeSpeed(total);
   auto realCurrent = shared::Win::RealtimeSpeed(current);
   ui->SetText(std::format(L"{}/{}", shared::IConv::MBytesToWString(realCurrent), shared::IConv::MBytesToWString(realTotal)).c_str());
   if (color)
    ui->SetTextColor(color);
  } while (0);
 }
 void IDownTaskElement::DownTotalTimeTextSet(const std::wstring& text, const DWORD& color) {
  do {
   auto ui = GetSubCtrl<CLabelUI>(L"D1C4FD362124");
   if (!ui)
    break;
   ui->SetText(text.c_str());
   if (color)
    ui->SetTextColor(color);
  } while (0);
 }
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif


}///namespace lcoal
