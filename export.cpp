#include "stdafx.h"
#include "export.h"

__shared_api_ void* __stdcall api_object_init(const void*, unsigned long) {
 void* result = nullptr;
 do {
  if (local::__gpGlobal)
   break;
  local::__gpGlobal = new local::Global();
  if (!local::__gpGlobal->Init())
   break;


  result = dynamic_cast<uiframework::IUIFrameWork*>(local::Global::UIFrameWorkGet());
 } while (0);
 return result;
}

__shared_api_ void __stdcall api_object_uninit() {
 SK_DELETE_PTR(local::__gpGlobal);
}
