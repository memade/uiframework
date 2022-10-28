#if !defined(INC_H___2FBE65F0_B3A6_4423_B761_71BBA13EF973__HEAD__)
#define INC_H___2FBE65F0_B3A6_4423_B761_71BBA13EF973__HEAD__

namespace local {
 
#if 0
 class Server final : virtual public uv::TcpServer {
 public:
  Server();
  virtual ~Server();
 private:
  void Init();
  void UnInit();
 public:
  bool Start();
  void Stop();
 private:
  void Process();
  std::atomic_bool m_IsOpen = false;
  std::vector<std::thread> m_Threads;
  shared::container::map<std::string, Taskman*> m_SessionQ;
 };
#endif
}///namespace lcoal

/// /*新生®（上海）**/
/// /*2022_10_14T08:17:37.3178546Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___2FBE65F0_B3A6_4423_B761_71BBA13EF973__HEAD__


