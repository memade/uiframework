#include "stdafx.h"

namespace local {

 class UIFrameWork final : public IUIFrameWork {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  UIFrameWork();
  virtual ~UIFrameWork();
 private:
  void Init();
  void UnInit();
 public:
  bool Open();
  void Close();
 protected:
  IWxMain* CreateWxMain() override final;
  void DestoryWxMain(uiframework::IWxMain*&) override final;
  void DestoryWxMain(const TypeIdentify&) override final;
 private:
  std::atomic_bool m_IsOpen = false;
  shared::container::map<TypeIdentify, WxMain*> m_WxMainQ;
 };



 extern UIFrameWork* __gpUIFrameWork;
}///namespace malware