#include "stdafx.h"

namespace malware {
 namespace http {

  Request::Request(const TypeIdentify& identify) :
   m_Identify(identify) {

  }

  Request::~Request() {

  }

  TypeIdentify Request::Identify() const {
   std::lock_guard<std::mutex> lock{ *m_Mutex };
   return m_Identify;
  }
  void Request::ResponseCb(const tf_response_cb& response_cb) {
   std::lock_guard<std::mutex> lock{ *m_Mutex };
   m_response_cb = response_cb;
  }



 }///namespace http
}///namespace malware