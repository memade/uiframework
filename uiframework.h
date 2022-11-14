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
 protected:
  IUIMain* CreateUIMain(const UIMainType&) override final;
  void DestoryUIMain(uiframework::IUIMain*&) override final;
  void DestoryUIMain(const TypeIdentify&) override final;
 private:
  std::atomic_bool m_IsOpen = false;
  shared::container::map<TypeIdentify, IUIMain*> m_UIMainQ;
 };



 extern UIFrameWork* __gpUIFrameWork;
}///namespace malware