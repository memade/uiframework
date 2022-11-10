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
 }

 bool UIFrameWork::Open() {
  bool result = false;
  do {


   result = true;
  } while (0);
  return result;
 }

 void UIFrameWork::Close() {

 }
 IWxMain* UIFrameWork::CreateWxMain() {
  IWxMain* result = nullptr;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  auto identify = shared::Win::Time::TimeStamp<std::chrono::microseconds>();
  auto pWxMain = new WxMain(identify);
  m_WxMainQ.push(identify, pWxMain);
  pWxMain->Create();
  return dynamic_cast<IWxMain*>(pWxMain);
 }
 void UIFrameWork::DestoryWxMain(uiframework::IWxMain*& wxmain) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  auto pDestoryObj = dynamic_cast<WxMain*>(wxmain);
  SK_DELETE_PTR(pDestoryObj);
  wxmain = nullptr;
 }
 void UIFrameWork::DestoryWxMain(const TypeIdentify& identify) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_WxMainQ.pop(identify, 
   [&](const auto&,WxMain* pWxMain) {
    pWxMain->Destory();
    SK_DELETE_PTR(pWxMain);
   });
 }
}///namespace lcoal