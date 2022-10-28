#if !defined(INC_H___A18B6A9B_FF85_41C8_98A5_267B32FB8AAC__HEAD__)
#define INC_H___A18B6A9B_FF85_41C8_98A5_267B32FB8AAC__HEAD__

namespace local {

 class PCHacker final : public IPCHacker {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  PCHacker();
  virtual ~PCHacker();
 private:
  void Init();
  void UnInit();
 public:
  bool Start(const IConfigure*) override final;
  void Stop() override final;
  IDownTaskNode* TaskCreate(const TypeID&) override final;
  bool TaskAction(const TypeID&, const EnActionType&) override final;
  bool TaskDestory(IDownTaskNode*) override final;
  bool TaskPerform(IDownTaskNode*) override final;
  ICom* ComGet() const override final;
  IConfigure* ConfigureGet() const override final;
  IEncryption* EncryptionGet() const override final;
  bool OnDockingFormHost(const std::wstring& json_data, const tfDockingMessageCb&) override final;
 protected:
  void RegisterTaskResultStatusCallback(const tfTaskResultStatusCb&) override final;
 public:
  shared::container::map<TypeID, Taskman*> m_TaskmanPtrQ;
  shared::container::map<TypeID/*res(game) id*/, TaskNode*> m_TaskPool;
  shared::container::queue<std::shared_ptr<ITaskResultStatus>> m_ResultQ;
  shared::container::queue<ITaskNode*> m_ResponseResultQ;
 private:
  void Process();
 private:
  Com* m_pCom = nullptr;
  Configure* m_pConfigure = nullptr;
  Encryption* m_pEncryption = nullptr;
  std::vector<std::thread> m_Threads;
  std::atomic_bool m_IsOpen = false;
  tfTaskResultStatusCb m_TaskResultStatusCb = nullptr;
 };

}///namespace local 

/// /*新生®（上海）**/
/// /*2022_09_10T10:25:26.4661499Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___A18B6A9B_FF85_41C8_98A5_267B32FB8AAC__HEAD__