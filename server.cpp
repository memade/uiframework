#include "stdafx.h"

namespace local {
#if 0
 Server::Server() : TcpServer(new uv::EventLoop()) {
  Init();
 }
 Server::~Server() {
  UnInit();
 }
 void Server::Init() {

  onMessageCallback_ =
   [this](uv::TcpConnectionPtr tcp_connection, const char* buffer, ssize_t buffer_size) {
   m_SessionQ.search(tcp_connection->Name(), 
    [&](Taskman* pSession) {
     pSession->Read(std::string((char*)buffer, buffer_size));
    });
  };

  onNewConnectCallback_ =
   [this](std::weak_ptr<uv::TcpConnection> tcp_connection) {
   auto pSession = new Taskman(tcp_connection.lock().get());
   const auto& identify = pSession->Identify();
   m_SessionQ.pop(identify, [](const auto&, auto&) {});
   m_SessionQ.push(identify, pSession);
  };

  onConnectCloseCallback_ =
   [this](std::weak_ptr<uv::TcpConnection> tcp_connection) {
   m_SessionQ.pop(tcp_connection.lock().get()->Name(),
    [&](const auto&, auto& pSession) {
     SK_DELETE_PTR(pSession);
    });
  };
 }
 void Server::UnInit() {
  SK_DELETE_PTR(loop_);
 }

 bool Server::Start() {
  do {
   if (m_IsOpen.load())
    break;
   m_Threads.emplace_back(
    [this]() {
     uv::SocketAddr socket_addr("127.0.0.1", 13762, uv::SocketAddr::Ipv4);
     do {
      if (0 != bindAndListen(socket_addr))
       break;
      loop_->run();
      loop_->runInThisLoop([]() {});
     } while (0);
    });
   m_IsOpen.store(true);
   m_Threads.emplace_back([this]() {Process(); });
  } while (0);
  return m_IsOpen.load();
 }
 void Server::Stop() {
  do {
   if (!m_IsOpen.load())
    break;
   __super::close(
    [this]() {
     std::thread(
      [&]() {
       loop_->runInThisLoop([&]() {loop_->stop(); });
      }).join();
    });
  } while (0);

  m_IsOpen.store(false);
  for (auto& t : m_Threads)
   t.join();
  m_Threads.clear();
 }

 void Server::Process() {
  do {
   m_SessionQ.iterate(
    [&](const auto&, Taskman* pSession, bool& itbreak) {
     std::vector<std::string> recv_pak_s;
     pSession->Read(recv_pak_s);
     if (!recv_pak_s.empty()) {



      auto sksksk = 0;
     }

     auto sk = 0;
    });
   if (!m_IsOpen.load())
    break;
   std::this_thread::sleep_for(std::chrono::milliseconds(10));
  } while (1);
 }
#endif
}///namespace lcoal
