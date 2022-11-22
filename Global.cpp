#include "stdafx.h"

namespace local {
 Global* __gpGlobal = nullptr;
 Global* GlobalGet() { return __gpGlobal; }
 HINSTANCE __gpHinstance = nullptr;

 Global::Global() {

 }

 Global::~Global() {
  UnInit();
 }

 bool Global::Init() {
  do {
   if (m_Ready.load())
    break;

   m_pUIFrameWork = new UIFrameWork();

   m_Ready.store(true);
  } while (0);
  return m_Ready.load();
 }

 void Global::UnInit() {
  SK_DELETE_PTR(m_pUIFrameWork);
 }

 UIFrameWork* Global::UIFrameWorkGet() {
  UIFrameWork* result = nullptr;
  if (__gpGlobal)
   result = __gpGlobal->m_pUIFrameWork;
  return result;
 }

 const std::map<EnUIType, std::wstring> __mapMainWindowClassName = {
  {EnUIType::Chromium,LR"(UIFrameWork Main Type - Chromium)"},
  {EnUIType::DuiLib,LR"(UIFrameWork Main Type - DuiLib)"},
  {EnUIType::DearImGui,LR"(UIFrameWork Main Type - DearImGui)"},
  {EnUIType::Win32SDKMDI,LR"(UIFrameWork Main Type - Win32SDKMDI)"},
  {EnUIType::Win32SDKSDI,LR"(UIFrameWork Main Type - Win32SDKSDI)"},
  {EnUIType::WxWidgets,LR"(UIFrameWork Main Type - WxWidgets)"},
 };
 const std::map<EnUIChildType, std::wstring> __mapChildWindowClassName = {
  {EnUIChildType::Chromium,LR"(UIFrameWork Child Type - Chromium)"},
  {EnUIChildType::DearImGui,LR"(UIFrameWork Child Type - DearImGui)"},
  {EnUIChildType::DuiLib,LR"(UIFrameWork Child Type - DuiLib)"},
  {EnUIChildType::Win32,LR"(UIFrameWork Child Type - Win32)"},
  {EnUIChildType::WxWidgets,LR"(UIFrameWork Child Type - WxWidgets)"},
 };
}///namespace local