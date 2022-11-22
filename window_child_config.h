#include "stdafx.h"

namespace local {

 class WindowChildConfig final : public IWindowChildConfig {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  WindowChildConfig();
  virtual ~WindowChildConfig();
 public:
  const TypeIdentify& Identify() const override final;
  const HINSTANCE& Hinstance() const override final;
  void Hinstance(const HINSTANCE&) override final;
  void WindowClassName(const std::wstring&) override final;
  const std::wstring& WindowClassName() const override final;
  void WindowTitleText(const std::wstring&) override final;
  const std::wstring& WindowTitleText() const override final;
  void WindowDefaultSize(const SIZE&) override final;
  void WindowDefaultPosition(const POINT&) override final;
  void WindowDefaultBackgroundColor(const DWORD&, const double& Transparency = 1.0) override final;
  void UIType(const EnUIChildType&) override final;
  const EnUIChildType& UIType() const override final;
  void Visible(const bool&) override final;
  bool Visible() const override final;
  void WndProcPtr(void*) override final;
  void* WndProcPtr() const override final;
  const HWND& ParentClientHwnd() const override final;
  void ParentClientHwnd(const HWND&) override final;
  const HWND& ParentHwnd() const override final;
  void ParentHwnd(const HWND&) override final;
  const DWORD& WindowStyle() const override final;
  void WindowStyle(const DWORD&) override final;
  void Release() const override final;
 public:
  void Host(void*);
  const SIZE& DefaultSize() const;
  const POINT& DefaultPosition() const;
  const WNDCLASSEXW& WndClassEx() const;
  const MDICREATESTRUCTW& MdiCreateStructW() const;
  const DWORD& DefaultBackgroundColor() const;
  const double& DefaultBackgroundTransparency() const;
 protected:
  const TypeIdentify m_Identify;
  std::wstring m_WindowClassName;
  std::wstring m_WindowTitleText;
  HINSTANCE m_hInstance = nullptr;
  SIZE m_DefaultSize = { 0 };
  POINT m_DefaultXY = { 0 };
  DWORD m_DefaultBackgroundColor = 0;
  double m_DefaultBackgroundTransparency = 1.0;
  EnUIChildType m_UIType = EnUIChildType::Win32;
  std::atomic_bool m_IsVisible = true;
  HWND m_hParent = nullptr;
  HWND m_hParentClient = nullptr;
  DWORD m_WindowStyle = 0;
  MDICREATESTRUCTW m_MdiCreateStructW = { 0 };
  WNDCLASSEXW m_WndClassEx = { 0 };
  HBRUSH m_hbrBackground = nullptr;
 };

}///namespace malware