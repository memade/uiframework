#include "stdafx.h"

namespace local {

 class WindowConfig final : public IWindowConfig {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  WindowConfig();
  virtual ~WindowConfig();
 public:
  const TypeIdentify& Identify() const override final;
  void WindowClassName(const std::wstring&) override final;
  const std::wstring& WindowClassName() const override final;
  void MainWindowTitleText(const std::wstring&) override final;
  const std::wstring& MainWindowTitleText() const override final;
  const HINSTANCE& Hinstance() const override final;
  void Hinstance(const HINSTANCE&) override final;
  void WindowDefaultSize(const SIZE&) override final;
  void WindowDefaultPosition(const POINT&) override final;
  void EnableDpiAwareness(const bool&) override final;
  bool EnableDpiAwareness() const override final;
  void WindowDefaultBackgroundColor(const DWORD&, const double& Transparency = 1.0) override final;
  void UIType(const EnUIType&) override final;
  const EnUIType& UIType() const override final;
  void Visible(const bool&) override final;
  bool Visible() const override final;
  void Release() const override final;
  void WndProcPtr(void*) override final;
  void* WndProcPtr() const override final;
  const HWND& Parent() const override final;
  void Parent(const HWND&) override final;
 public:
  const SIZE& DefaultSize() const;
  const POINT& DefaultPosition() const;
  const DWORD& DefaultBackgroundColor() const;
  const double& DefaultBackgroundTransparency() const;
  const WNDCLASSEXW& WndClassExW() const;
 protected:
  const TypeIdentify m_Identify;
  std::wstring m_WindowClassName;
  std::wstring m_MainWindowTitleText;
  HINSTANCE m_hInstance = nullptr;
  SIZE m_DefaultSize = { 0 };
  POINT m_DefaultXY = { 0 };
  DWORD m_DefaultBackgroundColor = 0;
  double m_DefaultBackgroundTransparency = 1.0;
  EnUIType m_UIType = EnUIType::Win32SDKSDI;
  std::atomic_bool m_EnableDpiAwareness = false;
  std::atomic_bool m_IsVisible = true;
  WNDCLASSEXW m_WindowClassExW = { 0 };
  HBRUSH m_hbrBackground = nullptr;
  HWND m_Parent = nullptr;
 };

}///namespace malware