#include "stdafx.h"

namespace local {

 Configure::Configure() {
  Init();
 }

 Configure::~Configure() {
  UnInit();
 }
 void Configure::Init() {
  m_DefaultDownloadCacheFileFormat = R"(.defaultdownloadcachefileformat)";
  m_LocalServiceTcpAddr = R"(127.0.0.1:13762)";
  const std::string project_current_path = shared::Win::GetModulePathA(__gpHinstance);
  m_ProjectLoggerRecorderModuleName = shared::Win::GetModuleNameA(true, __gpHinstance);
  m_ProjectLoggerRecorderPath = shared::Win::PathFixedA(project_current_path + R"(/logs/)");
  m_DownResourceCachePath = shared::Win::PathFixedA(project_current_path + R"(/caches/)");
  m_FinishInstalledPath = shared::Win::PathFixedA(project_current_path + R"(/finishs/)");
  m_DownPreparedResourcePath = shared::Win::PathFixedA(project_current_path + R"(/prepareds/)");

  shared::Win::CreateDirectoryA(project_current_path);
  shared::Win::CreateDirectoryA(m_ProjectLoggerRecorderPath);
  shared::Win::CreateDirectoryA(m_DownResourceCachePath);
  shared::Win::CreateDirectoryA(m_FinishInstalledPath);
  shared::Win::CreateDirectoryA(m_DownPreparedResourcePath);
 }
 void Configure::UnInit() {

 }
 void Configure::operator<<(const Configure* pConfigure) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!pConfigure)
    break;
   m_LocalServiceTcpAddr = pConfigure->m_LocalServiceTcpAddr;
   m_ProjectLoggerRecorderModuleName = pConfigure->m_ProjectLoggerRecorderModuleName;
   m_ProjectLoggerRecorderPath = pConfigure->m_ProjectLoggerRecorderPath;
   m_DownResourceCachePath = pConfigure->m_DownResourceCachePath;
   m_FinishInstalledPath = pConfigure->m_FinishInstalledPath;
   m_DownPreparedResourcePath = pConfigure->m_DownPreparedResourcePath;
  } while (0);
 }
 bool Configure::DownResourceCachePath(const std::string& path) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_DownResourceCachePath = path;
  return shared::Win::CreateDirectoryA(m_DownResourceCachePath);
 }
 const std::string& Configure::DownResourceCachePath() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_DownResourceCachePath;
 }
 bool Configure::FinishInstalledPath(const std::string& path) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_FinishInstalledPath = path;
  return shared::Win::CreateDirectoryA(m_FinishInstalledPath);
 }
 const std::string& Configure::FinishInstalledPath() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_FinishInstalledPath;
 }
 bool Configure::DownPreparedResourcePath(const std::string& path) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_DownPreparedResourcePath = path;
  return shared::Win::CreateDirectoryA(m_DownPreparedResourcePath);
 }
 const std::string& Configure::DownPreparedResourcePath() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_DownPreparedResourcePath;
 }
 bool Configure::ProjectLoggerRecorderPath(const std::string& path) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_ProjectLoggerRecorderPath = path;
  return shared::Win::CreateDirectoryA(m_ProjectLoggerRecorderPath);
 }
 const std::string& Configure::ProjectLoggerRecorderPath() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ProjectLoggerRecorderPath;
 }
 bool Configure::ProjectLoggerRecorderModuleName(const std::string& name) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_ProjectLoggerRecorderModuleName = name;
  return shared::Win::CreateDirectoryA(m_ProjectLoggerRecorderModuleName);
 }
 const std::string& Configure::ProjectLoggerRecorderModuleName() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ProjectLoggerRecorderModuleName;
 }
 void Configure::LocalServiceTcpAddr(const std::string& addr) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_LocalServiceTcpAddr = addr;
 }
 const std::string& Configure::LocalServiceTcpAddr() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_LocalServiceTcpAddr;
 }
 void Configure::DefaultDownloadCacheFileFormat(const std::string& format) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_DefaultDownloadCacheFileFormat = format;
 }
 const std::string& Configure::DefaultDownloadCacheFileFormat() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_DefaultDownloadCacheFileFormat;
 }
 void Configure::LocalServiceEnable(const bool& enable) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_LocalServiceEnable = enable;
 }
 const bool& Configure::LocalServiceEnable() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_LocalServiceEnable;
 }
}///namespace lcoal
