#if !defined(INC_H___DE900CDD_AFE5_4FB6_BE64_FA1E0D31E988__HEAD__)
#define INC_H___DE900CDD_AFE5_4FB6_BE64_FA1E0D31E988__HEAD__

namespace malware {
 namespace http {

  class Request final : public IRequest {
   std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
  public:
   Request(const TypeIdentify&);
   virtual ~Request();
  protected:
   TypeIdentify Identify() const override final;
   void ResponseCb(const tf_response_cb&) override final;
  protected:
   const TypeIdentify m_Identify;
   tf_response_cb m_response_cb = nullptr;
  };

 }///namespace http
}///namespace malware

/// /*新生®（上海）**/
/// /*2022_09_08T11:13:10.7275602Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___DE900CDD_AFE5_4FB6_BE64_FA1E0D31E988__HEAD__

