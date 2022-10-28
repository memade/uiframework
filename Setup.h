#if !defined(INC_H___61EC514D_4F9D_4224_966E_16BD85D4D0E7__HEAD__)
#define INC_H___61EC514D_4F9D_4224_966E_16BD85D4D0E7__HEAD__

namespace local {

 class Setup final {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  class Server final {
  public:
   std::string IPAddr;
   std::uint16_t Port = 0;
  };
 public:
  Setup(const std::string& setup_xml_pathname);
  ~Setup();
 private:
  void Init();
  void UnInit();
 public:
  const Server& ServerGet() const;
 private:
  std::atomic_bool m_Ready = false;
  Server m_Server;
  const std::string m_SetupXmlPathname;
 };

}///namespace local

/// /*新生®（上海）**/
/// /*2022_09_10T00:00:06.3224855Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___61EC514D_4F9D_4224_966E_16BD85D4D0E7__HEAD__


