#include "stdafx.h"

namespace malware {
 namespace http {

  class Http final : public IHttpApi {
   std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
  public:
   Http();
   virtual ~Http();
  private:
   void Init();
   void UnInit();
  public:
   bool Open();
   void Close();
  protected:
   IRequest* CreateRequest() override final;
   bool Perform(const IRequest*) override final;
  private:
   std::atomic_bool m_IsOpen = false;
  private:
   /// Generate request task identify
   TypeIdentify GenerateIdentify() const;
  private:
   std::map<TypeIdentify, std::shared_ptr<Request>> m_Requests;
  };



  extern Http* __gpHttp;
 }///namespace http
}///namespace malware