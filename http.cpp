#include "stdafx.h"

namespace malware {
 namespace http {
  Http* __gpHttp = nullptr;

  Http::Http() {
   Init();
  }

  Http::~Http() {
   UnInit();
  }

  void Http::Init() {
   do {
    if (CURLcode::CURLE_OK != curl_global_init(CURL_GLOBAL_WIN32 | CURL_VERSION_THREADSAFE))
     break;
   } while (0);
  }

  void Http::UnInit() {
   curl_global_cleanup();
  }

  bool Http::Open() {
   bool result = false;
   do {


    result = true;
   } while (0);
   return result;
  }

  void Http::Close() {

  }

  IRequest* Http::CreateRequest() {
   IRequest* result = nullptr;
   std::lock_guard<std::mutex> lock{ *m_Mutex };
   do {
    auto identify = GenerateIdentify();
    auto request = std::make_shared<Request>(identify);
    auto create = m_Requests.emplace(identify, request).first->second;
    result = dynamic_cast<decltype(result)>(create.get());
   } while (0);
   return result;
  }
  bool Http::Perform(const IRequest*) {
   bool result = false;
   std::lock_guard<std::mutex> lock{ *m_Mutex };
   do {

   } while (0);
   return result;
  }







  /// GenerateIdentify() is class private methods are not allowed to be locked.
  TypeIdentify Http::GenerateIdentify() const {
   TypeIdentify identify = 0;
   do {
    identify = shared::Win::Time::TimeStamp<std::chrono::microseconds>();
   } while (0);
   return identify;
  }


 }///namespace http
}///namespace malware