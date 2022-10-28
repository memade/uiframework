#if !defined(INC_H___D185A4AC_40F5_4798_8E7D_F285AD5F40A9__HEAD__)
#define INC_H___D185A4AC_40F5_4798_8E7D_F285AD5F40A9__HEAD__

namespace local {

 class UIBase {
 protected:
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  UIBase();
  ~UIBase();
 public:
  virtual void Create() = 0;
  virtual void Destory() = 0;
 protected:
  std::atomic_bool m_IsOpen = false;
  std::atomic_bool m_IsVisible = false;
  HANDLE m_hUIMain = nullptr;
 };


}///namespace local

/// /*新生®（上海）**/
/// /*2022_09_09T23:53:43.1131556Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___D185A4AC_40F5_4798_8E7D_F285AD5F40A9__HEAD__
