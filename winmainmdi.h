#if !defined(INC_H___1DCCDD7D_38A4_4A85_A8EB_E156D7B9457D__HEAD__)
#define INC_H___1DCCDD7D_38A4_4A85_A8EB_E156D7B9457D__HEAD__

namespace local {

 class UIMainMDI final : public UIBase {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  UIMainMDI(WindowConfig*);
 protected:
  void Release() const override final;
 protected:
  void MainProcess() override final;
  IUIChild* CreateChild(IWindowChildConfig*) override final;
 private:
  ~UIMainMDI();
  void Init();
  void UnInit();
  static LRESULT __stdcall WindowProc(HWND, UINT, WPARAM, LPARAM);
 };

}///namespace local

/// /*新生®（上海）**/
/// /*2022_11_18T01:19:10.0869111Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___1DCCDD7D_38A4_4A85_A8EB_E156D7B9457D__HEAD__




