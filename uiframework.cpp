#include "stdafx.h"

namespace local {
 extern UIFrameWork* __gpUIFrameWork = nullptr;
 UIFrameWork* UIFrameWorkGet() { return __gpUIFrameWork; }

 UIFrameWork::UIFrameWork() {
  Init();
 }

 UIFrameWork::~UIFrameWork() {
  UnInit();
 }
 void UIFrameWork::Release() const {
  delete this;
 }
 void UIFrameWork::Init() {
  do {


  } while (0);
 }

 void UIFrameWork::UnInit() {
  m_UIMainQ.iterate_clear(
   [this](const auto&, auto& pUIObj, auto&, auto& itclear) {
    pUIObj->Destory();
  pUIObj->Release();
  itclear = true;
   });
  for (auto it = m_WindowConfigQ.begin(); it != m_WindowConfigQ.end();) {
   (*it)->Release();
   it = m_WindowConfigQ.erase(it);
  }
 }
 IUIMain* UIFrameWork::SearchUIMain(const TypeIdentify& identify) {
  IUIMain* result = nullptr;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  void(m_UIMainQ.search(identify,
   [&](const auto&, auto& pMain) {
    result = dynamic_cast<IUIMain*>(pMain);
   }));
  return result;
 }
 IWindowConfig* UIFrameWork::CreateWindowConfig() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return dynamic_cast<IWindowConfig*>(m_WindowConfigQ.emplace_back(new WindowConfig()));
 }
 IUIMain* UIFrameWork::CreateUIMain(IWindowConfig* pWindowConfig) {
  IUIMain* result = nullptr;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  switch (pWindowConfig->UIType()) {
  case EnUIType::WxWidgets: {
   result = new WxMain(dynamic_cast<WindowConfig*>(pWindowConfig));
  }break;
  default: {
   result = new UIMainMDI(dynamic_cast<WindowConfig*>(pWindowConfig));
  }break;
  }
#if 0
  if (std::uint64_t(EnUIType::Win32SDKMDI) & std::uint64_t(pWindowConfig->UIType())) {
   result = new UIMainMDI(dynamic_cast<WindowConfig*>(pWindowConfig));
  }
  else if (std::uint64_t(EnUIType::WxWidgets) & std::uint64_t(pWindowConfig->UIType())) {
   auto sk = 0;
  }
  if (std::uint64_t(EnUIType::WinMDI) & std::uint64_t(pWindowConfig->UIType())) {
   result = new UIMainMDI(dynamic_cast<WindowConfig*>(pWindowConfig));
  }

  else if (std::uint64_t(EnUIType::DearImGui) & std::uint64_t(pWindowConfig->UIType())) {

  }
  else if (std::uint64_t(EnUIType::DuiLib) & std::uint64_t(pWindowConfig->UIType())) {

  }
  else if (std::uint64_t(EnUIType::Default) & std::uint64_t(pWindowConfig->UIType())) {

  }
  else if (std::uint64_t(EnUIType::Chromium) & std::uint64_t(pWindowConfig->UIType())) {

  }
#endif
  if (result) {
   m_UIMainQ.push(pWindowConfig->Identify(), result);
   result->Create();
  }
  return result;
 }
 void UIFrameWork::DestoryUIMain(uiframework::IUIMain*& wxmain) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  /*auto pDestoryObj = dynamic_cast<WxMain*>(wxmain);*/
  /*SK_DELETE_PTR(pDestoryObj);*/
  wxmain->Release();
  wxmain = nullptr;
 }
 void UIFrameWork::DestoryUIMain(const TypeIdentify& identify) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_UIMainQ.pop(identify,
   [&](const auto&, IUIMain* pWxMain) {
    pWxMain->Destory();
  pWxMain->Release();
  /*SK_DELETE_PTR(pWxMain);*/
   });
 }
}///namespace lcoal