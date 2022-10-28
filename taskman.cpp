#include "stdafx.h"

namespace local {

 Taskman::Taskman(const TypeID& task_id) :
  m_TaskID(task_id) {

 }
 Taskman::~Taskman() {

 }
 void Taskman::Release() const {
  delete this;
 }
 const TypeID& Taskman::TaskID() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_TaskID;
 }
 void Taskman::ProcessId(const DWORD& pid) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_ProcessId = pid;
 }
 const DWORD& Taskman::ProcessId() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ProcessId;
 }
 void Taskman::InPathname(const std::string& pathname) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_InPathname = pathname;
 }
 void Taskman::OutPath(const std::string& path) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_OutPath = path;
 }
 const std::string& Taskman::InPathname() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_InPathname;
 }
 const std::string& Taskman::OutPath() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_OutPath;
 }
}///namespace lcoal
