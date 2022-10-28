#if !defined(INC_H___E7118B19_EA8E_4445_B79C_159F33ABDC29__HEAD__)
#define INC_H___E7118B19_EA8E_4445_B79C_159F33ABDC29__HEAD__

namespace local {

 class Taskman final {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  Taskman(const TypeID&);
  virtual ~Taskman();
 public:
  void ProcessId(const DWORD&);
  const DWORD& ProcessId() const;
  void Release() const;
  const TypeID& TaskID() const;
  void InPathname(const std::string&);
  void OutPath(const std::string&);
  const std::string& InPathname() const;
  const std::string& OutPath() const;
 private:
  const TypeID m_TaskID;
  DWORD m_ProcessId = 0;
  std::string m_InPathname;
  std::string m_OutPath;
 };

}///namespace lcoal

/// /*新生®（上海）**/
/// /*2022_10_14T13:01:14.6817275Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___E7118B19_EA8E_4445_B79C_159F33ABDC29__HEAD__



