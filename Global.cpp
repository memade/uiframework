﻿#include "stdafx.h"

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

 }

 UIFrameWork* Global::UIFrameWorkGet() {
  UIFrameWork* result = nullptr;
  if (__gpGlobal)
   result = __gpGlobal->m_pUIFrameWork;
  return result;
 }


}///namespace local