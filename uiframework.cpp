#include "stdafx.h"

namespace local {
 extern UIFrameWork* __gpUIFrameWork = nullptr;

 UIFrameWork::UIFrameWork() {
  Init();
 }

 UIFrameWork::~UIFrameWork() {
  UnInit();
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
 }
 IUIMain* UIFrameWork::CreateUIMain(const UIMainType& uitype) {
  IUIMain* result = nullptr;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  auto identify = shared::Win::Time::TimeStamp<std::chrono::microseconds>();
  switch (uitype) {
  case UIMainType::WINMAIN: {
   result = new UIMain(identify);
  }break;
  case UIMainType::WXMAIN: {
   result = new WxMain(identify);
  }break;
  case UIMainType::DUIMAIN: {

  }break;
  default:
   break;
  }
  if (result) {
   m_UIMainQ.push(identify, result);
   result->Create();
  }
  return result;
 }
 void UIFrameWork::DestoryUIMain(uiframework::IUIMain*& wxmain) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  auto pDestoryObj = dynamic_cast<WxMain*>(wxmain);
  SK_DELETE_PTR(pDestoryObj);
  wxmain = nullptr;
 }
 void UIFrameWork::DestoryUIMain(const TypeIdentify& identify) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_UIMainQ.pop(identify,
   [&](const auto&, IUIMain* pWxMain) {
    pWxMain->Destory();
  SK_DELETE_PTR(pWxMain);
   });
 }
}///namespace lcoal