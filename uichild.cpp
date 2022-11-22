#include "stdafx.h"

namespace local {

 UIChild::UIChild(WindowChildConfig* pConfig) : m_pConfig(pConfig) {
 }
 UIChild::~UIChild() {
 }
 bool UIChild::Ready() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Ready.load();
 }
#if 0
 LRESULT __stdcall UIChild::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  static UIChild* pThis = nullptr;
  switch (message) {
  case WM_CREATE: {
   LPCREATESTRUCTW pCreateStructW = reinterpret_cast<LPCREATESTRUCTW>(lParam);
   if (!pCreateStructW)
    break;
   LPMDICREATESTRUCTW pMdiCreateStructW = reinterpret_cast<LPMDICREATESTRUCTW>(pCreateStructW->lpCreateParams);
   if (!pMdiCreateStructW)
    break;
   pThis = reinterpret_cast<UIChild*>(pMdiCreateStructW->lParam);
  }break;
  default:
   break;
  }
  if (pThis && pThis->OnWindowProc(hwnd, message, wParam, lParam))
   return 0;
  return ::DefMDIChildProcW(hwnd, message, wParam, lParam);
 }
#endif
#if 0
 void UIChild::Init() {
  if (m_WindowText.empty())
   m_WindowText = shared::IConv::MBytesToWString(m_Identify);
  m_WindowClass = __mapChildWindowClassName.at(m_UIType);
  m_WndClassExW.cbSize = sizeof(m_WndClassExW);
  m_WndClassExW.lpszClassName = m_WindowClass.c_str();
  m_WndClassExW.hInstance = m_hInstance;
  m_WndClassExW.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  m_MdiCreateStructW.szTitle = m_WindowText.c_str();
  m_MdiCreateStructW.hOwner = m_hInstance;
  m_MdiCreateStructW.szClass = m_WindowClass.c_str();
  m_MdiCreateStructW.lParam = reinterpret_cast<LPARAM>(this);

  switch (m_UIType) {
  case EnUIChildType::Win32: {
   m_WndClassExW.style = CS_HREDRAW | CS_VREDRAW;
   m_MdiCreateStructW.style = WS_OVERLAPPEDWINDOW;
  }break;
  case EnUIChildType::Chromium: {

  }break;
  case EnUIChildType::DearImGui: {
   m_WndClassExW.style = CS_CLASSDC;
   m_MdiCreateStructW.style = m_WndClassExW.style;
  }break;
  case EnUIChildType::DuiLib: {

  }break;
  case EnUIChildType::WxWidgets: {

  }break;
  default:
   break;
  }///switch

  m_WndClassExW.lpfnWndProc = &UIChild::WndProc;
  void(::RegisterClassExW(&m_WndClassExW));
 }
 void UIChild::UnInit() {

 }
#endif
#if 0
 void UIChild::SetBackground(const DWORD& bkcolor) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_Background = bkcolor;
 }
 const DWORD& UIChild::GetBackground() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Background;
 }
#endif
 IWindowChildConfig* UIChild::Config() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_pConfig;
 }
 const HWND& UIChild::GetHwnd() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_hWnd;
 }
 const TypeIdentify& UIChild::Identify() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_pConfig->Identify();
 }
 const EnUIChildType& UIChild::UIType() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_UIType;
 }
 bool UIChild::Show() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ShowFlag.load();
 }
 void UIChild::Show(const bool& show_flag) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  if (!m_hWnd || m_ShowFlag.load() == show_flag)
   return;
  m_ShowFlag.store(show_flag);
  ::ShowWindow(m_hWnd, m_ShowFlag.load() ? SW_SHOW : SW_HIDE);
 }
#if 0
 void UIChild::OnCreate(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, BOOL& Handle) {
  Handle = FALSE;
  do {
   m_hWnd = hwnd;
   switch (m_UIType) {
   case EnUIChildType::Win32: {

    auto sk = 0;
   }break;
   case EnUIChildType::DearImGui: {
    if (!ImGuiMain::CreateDeviceD3D(m_hWnd, &m_pD3D10Device, &m_pDXGISwapChain))
     break;
    if (!ImGuiMain::CreateRenderTarget(m_pD3D10Device, m_pDXGISwapChain, &m_pD3D10RenderTargetView))
     break;
    IMGUI_CHECKVERSION();
    auto pImGuiContext = ImGui::CreateContext();
    if (!pImGuiContext)
     break;
    ImGuiIO& io = ImGui::GetIO();
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    __mapImFont.emplace(LR"(segoeui)", io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\segoeui.ttf)", 18.0f));
    __mapImFont.emplace(LR"(simhei)", io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\simhei.ttf)", 18.0f));
    __mapImFont.emplace(LR"(simfang)", io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\simfang.ttf)", 50.0f, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon()));
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    // Setup Platform/Renderer backends
    if (!ImGui_ImplWin32_Init(m_hWnd))
     break;
    if (!ImGui_ImplDX10_Init(m_pD3D10Device))
     break;

   }break;
   default:
    break;
   }
   Handle = TRUE;
  } while (0);
 }
 void UIChild::OnSize(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, BOOL& Handle) {
  Handle = FALSE;
  do {
   switch (m_UIType) {
   case EnUIChildType::Win32: {

   }break;
   case EnUIChildType::DearImGui: {
    if (wParam == SIZE_MINIMIZED)
     break;
    if (!m_pD3D10Device || !m_pDXGISwapChain || !m_pD3D10RenderTargetView)
     break;
    void(ImGuiMain::CleanupRenderTarget(m_pD3D10RenderTargetView));
    void(m_pDXGISwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0));
    void(ImGuiMain::CreateRenderTarget(m_pD3D10Device, m_pDXGISwapChain, &m_pD3D10RenderTargetView));
   }break;
   default:
    break;
   }
   Handle = TRUE;
  } while (0);
 }
 void UIChild::OnDestory(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, BOOL& Handle) {
  Handle = FALSE;
  do {
   switch (m_UIType) {
   case EnUIChildType::Win32: {

   }break;
   case EnUIChildType::DearImGui: {

   }break;
   default:
    break;
   }
   Handle = TRUE;
  } while (0);
 }
 void UIChild::OnRender() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {//!@ Win32 SDK

  } while (0);

  do {//!@ DearImGui
   if (m_UIType != EnUIChildType::DearImGui)
    break;
   ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.0f);
   // Start the Dear ImGui frame
   ImGui_ImplDX10_NewFrame();
   ImGui_ImplWin32_NewFrame();
   ImGui::NewFrame();
   {
    ImGui::PushFont(__mapImFont[LR"(segoeui)"]);
    ImGui::Begin(std::format("Hello, martell !").c_str());
    ImGui::PopFont();

    ImGui::PushFont(__mapImFont[LR"(simfang)"]);
    ImGui::Text((char*)u8"您好 !"); // Display some text (you can use a format strings too)
    ImGui::PopFont();
    ImGui::End();
   }
   // Rendering
   ImGui::Render();
   /*const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };*/
   DWORD dwDefaultRgb = m_Background;
   int B = dwDefaultRgb & 0xFF; dwDefaultRgb >>= 8;
   int G = dwDefaultRgb & 0xFF; dwDefaultRgb >>= 8;
   int R = dwDefaultRgb & 0xFF; dwDefaultRgb >>= 8;
   const float clear_color_with_alpha[4] = {
    static_cast<float>(R / 255.0),
    static_cast<float>(G / 255.0),
    static_cast<float>(B / 255.0),
    1.0 };
   m_pD3D10Device->OMSetRenderTargets(1, &m_pD3D10RenderTargetView, NULL);
   m_pD3D10Device->ClearRenderTargetView(m_pD3D10RenderTargetView, clear_color_with_alpha);
   ImGui_ImplDX10_RenderDrawData(ImGui::GetDrawData());
   m_pDXGISwapChain->Present(1, 0); // Present with vsync
  } while (0);
 }
 LRESULT __stdcall UIChild::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  BOOL Handle = FALSE;
  static UIChild* pThis = nullptr;
  do {
   if (!pThis)
    break;
   if (pThis->m_UIType != EnUIChildType::DearImGui)
    break;
   if (ImGuiMain::IMGUI_WndProc(hwnd, message, wParam, lParam))
    return 1;
  } while (0);

  switch (message) {
  case WM_MDIACTIVATE: {
   Handle = TRUE;
  }break;
  case WM_SIZE: {
   if (!pThis)
    break;
   pThis->OnSize(hwnd, message, wParam, lParam, Handle);
  }break;
  case WM_CREATE: {
   auto pCreateStructW = reinterpret_cast<LPCREATESTRUCTW>(lParam);
   auto pMdiCreateStructW = reinterpret_cast<LPMDICREATESTRUCTW>(pCreateStructW->lpCreateParams);
   if (!pMdiCreateStructW)
    break;
   pThis = reinterpret_cast<UIChild*>(pMdiCreateStructW->lParam);
   if (!pThis)
    break;
   pThis->OnCreate(hwnd, message, wParam, lParam, Handle);
  }break;
  case WM_DESTROY: {
   pThis->OnDestory(hwnd, message, wParam, lParam, Handle);
  }break;
  default:
   break;
  }
  if (Handle == TRUE)
   return 1;
  return ::DefMDIChildProcW(hwnd, message, wParam, lParam);
 }
#endif
#if 0
 bool UIChild::Create() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_hWnd = (HWND)::SendMessageW(m_hParentClient, WM_MDICREATE, 0, (LPARAM)&m_MdiCreateStructW);
  return m_hWnd ? true : false;
 }
 void UIChild::Destory() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
 }
 bool UIChild::Show() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Visible.load();
 }
 void UIChild::Show(const bool& visible) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_Visible.store(visible);
 }
#endif
#if 0
 void UIChild::WndClassExW(const std::function<void(WNDCLASSEXW&)>& wndClass_set_cb) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  wndClass_set_cb(m_WndClassExW);
 }
 const WNDCLASSEXW& UIChild::WndClassExW() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_WndClassExW;
 }
 void UIChild::MdiCreateStructW(const std::function<void(MDICREATESTRUCTW&)>& createStruct_set_cb) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  createStruct_set_cb(m_MdiCreateStructW);
 }
 const MDICREATESTRUCTW& UIChild::MdiCreateStructW() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_MdiCreateStructW;
 }
 const std::string& UIChild::Identify() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Identify;
 }
 const EnUIChildType& UIChild::UIType() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_UIType;
 }
 void UIChild::WindowText(const std::wstring& window_text) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_WindowText = window_text;
 }
 const std::wstring& UIChild::WindowText() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_WindowText;
 }
 void UIChild::WindowClass(const std::wstring& class_name) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_WindowClass = class_name;
 }
 const std::wstring& UIChild::WindowClass() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_WindowClass;
 }
#endif
}///namespace local
