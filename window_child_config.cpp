#include "stdafx.h"

namespace local {

 WindowChildConfig::WindowChildConfig()
  : m_Identify(shared::Win::Time::TimeStamp<std::chrono::microseconds>()) {
  m_WndClassEx.cbSize = sizeof(m_WndClassEx);
  m_hbrBackground = ::CreateSolidBrush(RGB(255,255,255));
  m_WndClassEx.hbrBackground = m_hbrBackground;
 }
 WindowChildConfig::~WindowChildConfig() {
  if (m_hbrBackground) {
   ::DeleteObject(m_hbrBackground);
   m_hbrBackground = nullptr;
  }
 }
 void WindowChildConfig::Release() const {
  delete this;
 }
 void WindowChildConfig::Host(void* ptr) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_MdiCreateStructW.lParam = reinterpret_cast<LPARAM>(ptr);
 }
 const TypeIdentify& WindowChildConfig::Identify() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Identify;
 }
 const HINSTANCE& WindowChildConfig::Hinstance() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_hInstance;
 }
 void WindowChildConfig::Hinstance(const HINSTANCE& hInstance) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_hInstance = hInstance;
  m_WndClassEx.hInstance = m_hInstance;
  m_MdiCreateStructW.hOwner = m_hInstance;
 }
 void WindowChildConfig::UIType(const EnUIChildType& type) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_UIType = type;
 }
 const EnUIChildType& WindowChildConfig::UIType() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_UIType;
 }
 void WindowChildConfig::WindowClassName(const std::wstring& name) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_WindowClassName = name;
  m_WndClassEx.lpszClassName = m_WindowClassName.c_str();
  m_MdiCreateStructW.szClass = m_WindowClassName.c_str();
 }
 const std::wstring& WindowChildConfig::WindowClassName() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_WindowClassName;
 }
 void WindowChildConfig::WindowTitleText(const std::wstring& text) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_WindowTitleText = text;
  m_MdiCreateStructW.szTitle = m_WindowTitleText.c_str();
 }
 const std::wstring& WindowChildConfig::WindowTitleText() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_WindowTitleText;
 }
 void WindowChildConfig::WindowDefaultSize(const SIZE& size) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_DefaultSize.cx = size.cx;
  m_DefaultSize.cy = size.cy;
  m_MdiCreateStructW.cx = m_DefaultSize.cx;
  m_MdiCreateStructW.cy = m_DefaultSize.cy;
 }
 const WNDCLASSEXW& WindowChildConfig::WndClassEx() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_WndClassEx;
 }
 const MDICREATESTRUCTW& WindowChildConfig::MdiCreateStructW() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_MdiCreateStructW;
 }
 void WindowChildConfig::WndProcPtr(void* wndprocptr) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_WndClassEx.lpfnWndProc = reinterpret_cast<WNDPROC>(wndprocptr);;
 }
 void* WindowChildConfig::WndProcPtr() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_WndClassEx.lpfnWndProc;
 }
 const DWORD& WindowChildConfig::WindowStyle() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_WindowStyle;
 }
 void WindowChildConfig::WindowStyle(const DWORD& style) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_WindowStyle = style;
  m_WndClassEx.style = m_WindowStyle;
  m_MdiCreateStructW.style = m_WindowStyle;
 }
 void WindowChildConfig::WindowDefaultPosition(const POINT& point) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_DefaultXY.x = point.x;
  m_DefaultXY.y = point.y;
  m_MdiCreateStructW.x = m_DefaultXY.x;
  m_MdiCreateStructW.y = m_DefaultXY.y;
 }
 void WindowChildConfig::WindowDefaultBackgroundColor(const DWORD& rgb, const double& Transparency /*= 1.0*/) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_DefaultBackgroundColor = rgb;
  m_DefaultBackgroundTransparency = Transparency;
  if (m_hbrBackground) {
   ::DeleteObject(m_hbrBackground);
   m_hbrBackground = nullptr;
  }
  m_hbrBackground = ::CreateSolidBrush(rgb);
  m_WndClassEx.hbrBackground = m_hbrBackground;
 }
 const SIZE& WindowChildConfig::DefaultSize() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_DefaultSize;
 }
 const POINT& WindowChildConfig::DefaultPosition() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_DefaultXY;
 }
 const DWORD& WindowChildConfig::DefaultBackgroundColor() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_DefaultBackgroundColor;
 }
 const double& WindowChildConfig::DefaultBackgroundTransparency() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_DefaultBackgroundTransparency;
 }
 void WindowChildConfig::Visible(const bool& visible) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_IsVisible.store(visible);
 }
 bool WindowChildConfig::Visible() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_IsVisible.load();
 }
 const HWND& WindowChildConfig::ParentClientHwnd() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_hParentClient;
 }
 void WindowChildConfig::ParentClientHwnd(const HWND& hwnd) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_hParentClient = hwnd;
 }
 const HWND& WindowChildConfig::ParentHwnd() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_hParent;
 }
 void WindowChildConfig::ParentHwnd(const HWND& hwnd) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_hParent = hwnd;
 }
}///namespace lcoal