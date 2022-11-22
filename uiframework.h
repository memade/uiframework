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
  IWindowConfig* CreateWindowConfig() override final;
  IUIMain* CreateUIMain(IWindowConfig*) override final;
  void DestoryUIMain(uiframework::IUIMain*&) override final;
  void DestoryUIMain(const TypeIdentify&) override final;
 public:
  IUIMain* SearchUIMain(const TypeIdentify&) override final;
 private:
  std::atomic_bool m_IsOpen = false;
  shared::container::map<TypeIdentify, IUIMain*> m_UIMainQ;
  std::vector<IWindowConfig*> m_WindowConfigQ;
 };



 extern UIFrameWork* __gpUIFrameWork;
 extern UIFrameWork* UIFrameWorkGet();
}///namespace malware