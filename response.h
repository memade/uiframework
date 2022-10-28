#if !defined(INC_H___3D9AAFA7_34E9_4421_A70F_1D8E4230A42B__HEAD__)
#define INC_H___3D9AAFA7_34E9_4421_A70F_1D8E4230A42B__HEAD__

namespace malware {
 namespace http {

  class Response final : public IResponse {
   std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
  public:
   Response();
   virtual ~Response();
  protected:
  };


 }///namespace http
}///namespace malware

/// /*新生®（上海）**/
/// /*2022_09_08T11:12:47.8151364Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___3D9AAFA7_34E9_4421_A70F_1D8E4230A42B__HEAD__

