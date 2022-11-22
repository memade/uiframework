#include "stdafx.h"

namespace local {

 WindowConfig::WindowConfig()
  :m_Identify(shared::Win::Time::TimeStamp<std::chrono::microseconds>()) {
  m_WindowClassExW.cbSize = sizeof(m_WindowClassExW);
  m_DefaultBackgroundColor = RGB(255, 255, 255);
  m_hbrBackground = ::CreateSolidBrush(m_DefaultBackgroundColor);
  m_WindowClassExW.hbrBackground = m_hbrBackground;
 }

 WindowConfig::~WindowConfig() {
  if (m_hbrBackground) {
   ::DeleteObject(m_hbrBackground);
   m_hbrBackground = nullptr;
  }
 }
 void WindowConfig::Release() const {
  delete this;
 }
 const WNDCLASSEXW& WindowConfig::WndClassExW() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_WindowClassExW;
 }
 const TypeIdentify& WindowConfig::Identify() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Identify;
 }
 void WindowConfig::UIType(const EnUIType& type) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_UIType = type;
 }
 const EnUIType& WindowConfig::UIType() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_UIType;
 }
 void WindowConfig::WindowClassName(const std::wstring& name) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_WindowClassName = name;
  m_WindowClassExW.lpszClassName = m_WindowClassName.c_str();
 }
 const std::wstring& WindowConfig::WindowClassName() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_WindowClassName;
 }
 void WindowConfig::MainWindowTitleText(const std::wstring& text) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_MainWindowTitleText = text;
 }
 const std::wstring& WindowConfig::MainWindowTitleText() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_MainWindowTitleText;
 }
 const HINSTANCE& WindowConfig::Hinstance() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_hInstance;
 }
 void WindowConfig::Hinstance(const HINSTANCE& hInstance) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_hInstance = hInstance;
  m_WindowClassExW.hInstance = hInstance;
 }
 void WindowConfig::WindowDefaultSize(const SIZE& size) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_DefaultSize.cx = size.cx;
  m_DefaultSize.cy = size.cy;
 }
 void WindowConfig::WindowDefaultPosition(const POINT& point) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_DefaultXY.x = point.x;
  m_DefaultXY.y = point.y;
 }
 void WindowConfig::WindowDefaultBackgroundColor(const DWORD& rgb, const double& Transparency /*= 1.0*/) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_DefaultBackgroundColor = rgb;
  m_DefaultBackgroundTransparency = Transparency;
  if (m_hbrBackground) {
   ::DeleteObject(m_hbrBackground);
   m_hbrBackground = nullptr;
  }
  m_hbrBackground = ::CreateSolidBrush(rgb);
  m_WindowClassExW.hbrBackground = m_hbrBackground;
 }
 void WindowConfig::EnableDpiAwareness(const bool& enable) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_EnableDpiAwareness.store(enable);
 }
 bool WindowConfig::EnableDpiAwareness() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_EnableDpiAwareness.load();
 }
 const SIZE& WindowConfig::DefaultSize() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_DefaultSize;
 }
 const POINT& WindowConfig::DefaultPosition() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_DefaultXY;
 }
 const HWND& WindowConfig::Parent() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Parent;
 }
 void WindowConfig::Parent(const HWND& parent) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_Parent = parent;
 }
 void WindowConfig::WndProcPtr(void* wndprocptr) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_WindowClassExW.lpfnWndProc = reinterpret_cast<WNDPROC>(wndprocptr);
 }
 void* WindowConfig::WndProcPtr() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_WindowClassExW.lpfnWndProc;
 }
 const DWORD& WindowConfig::DefaultBackgroundColor() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_DefaultBackgroundColor;
 }
 const double& WindowConfig::DefaultBackgroundTransparency() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_DefaultBackgroundTransparency;
 }
 void WindowConfig::Visible(const bool& visible) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_IsVisible.store(visible);
 }
 bool WindowConfig::Visible() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_IsVisible.load();
 }
}///namespace lcoal