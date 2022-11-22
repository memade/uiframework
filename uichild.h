#if !defined(INC_H___E1BB09CD_2C3D_43CC_8D9A_AC1F5A5DB3F8__HEAD__)
#define INC_H___E1BB09CD_2C3D_43CC_8D9A_AC1F5A5DB3F8__HEAD__

namespace local {

 class UIChild : public IUIChild {
 protected:
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  UIChild(WindowChildConfig*);
 protected:
  virtual ~UIChild();
 public:
  bool Show() const override final;
  void Show(const bool&) override final;
  const HWND& GetHwnd() const override final;
  IWindowChildConfig* Config() const override final;
  const TypeIdentify& Identify() const override final;
  const EnUIChildType& UIType() const override final;
 public:
  virtual bool Ready() const;
  virtual void OnRender() { return; }
  virtual bool OnWindowProc(HWND, UINT, WPARAM, LPARAM) = 0;
 protected:
  std::atomic_bool m_Ready = false;
  std::atomic_bool m_ShowFlag = false;
  EnUIChildType m_UIType = EnUIChildType::Win32;
  HWND m_hWnd = nullptr;
  WindowChildConfig* m_pConfig = nullptr;
 };

}///namespace local

/// /*新生®（上海）**/
/// /*2022_11_19T15:09:51.1092424Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___E1BB09CD_2C3D_43CC_8D9A_AC1F5A5DB3F8__HEAD__





