#if !defined(INC_H___E1A3D71E_D33E_4425_90D6_D7922343A8DA__HEAD__)
#define INC_H___E1A3D71E_D33E_4425_90D6_D7922343A8DA__HEAD__

namespace local {

 class WxMain final : public IUIMain {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  WxMain(const TypeIdentify&);
  ~WxMain();
 public:
  const TypeIdentify& Identify() const override final;
  void Create() override final;
  void Destory() override final;
  void Release() const override final;
 private:
  const TypeIdentify m_Identify;
  std::atomic_bool m_IsOpen = false;
  std::atomic_bool m_IsVisible = false;
  HANDLE m_hUIMain = nullptr;
  static void OnAppClose();
 };

}///namespace local

/// /*新生®（上海）**/
/// /*2022_10_07T02:51:42.4170199Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___E1A3D71E_D33E_4425_90D6_D7922343A8DA__HEAD__



