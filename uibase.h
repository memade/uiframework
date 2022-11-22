#if !defined(INC_H___D185A4AC_40F5_4798_8E7D_F285AD5F40A9__HEAD__)
#define INC_H___D185A4AC_40F5_4798_8E7D_F285AD5F40A9__HEAD__

namespace local {

 class UIBase : public IUIMain {
 protected:
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  UIBase(WindowConfig*);
  ~UIBase();
 public:
  IWindowConfig* Config() const override final;
  IWindowChildConfig* CreateChildConfig() override final;
  void Create() override final;
  void Destory() override final;
  const HWND& MainWnd() const override final;
  void Show(const bool&) override final;
  bool Show() const override final;
  IUIChild* CreateChild(IWindowChildConfig*) override { return nullptr; }
   void MdiCascade() const override final;
   void MdiConarrange() const override final;
   void MdiTile() const override final;
 protected:
  //!@ Logic blocking
  virtual void MainProcess() { return; }
  virtual void ShowControl();
  virtual void OnRender();
 protected:
  std::atomic_bool m_IsOpen = false;
  HANDLE m_hUIMain = nullptr;
  HANDLE m_hUIMainCreateEvent = nullptr;
  WindowConfig* m_pConfig = nullptr;
  HWND m_hWnd = nullptr;
  HWND m_hWndClient = nullptr;
  std::atomic_bool m_ShowFlag = false;
  std::vector<IWindowChildConfig*> m_ChildConfigQ;
  shared::container::map<TypeIdentify, UIChild*> m_ChildQ;
 };
}///namespace local

/// /*新生®（上海）**/
/// /*2022_09_09T23:53:43.1131556Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___D185A4AC_40F5_4798_8E7D_F285AD5F40A9__HEAD__
