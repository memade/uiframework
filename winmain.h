#if !defined(INC_H___3180A8B3_813D_490E_90C4_CFCBA36877A1__HEAD__)
#define INC_H___3180A8B3_813D_490E_90C4_CFCBA36877A1__HEAD__

namespace local {

 class UIMain final : public IUIMain {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  UIMain(const TypeIdentify&);
 public:
  IWindowConfig* Config() const override final;
  void Create() override final;
  void Destory() override final;
  void Release() const override final;
 private:
  const TypeIdentify m_Identify;
  std::atomic_bool m_IsOpen = false;
  std::atomic_bool m_IsVisible = false;
  HANDLE m_hUIMain = nullptr;
 private:
  ~UIMain();
 };

}///namespace local

/// /*新生®（上海）**/
/// /*2022_11_12T02:35:13.9188802Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___3180A8B3_813D_490E_90C4_CFCBA36877A1__HEAD__




