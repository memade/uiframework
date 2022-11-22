#include "stdafx.h"

namespace local {
 UIChildImGuiDX10::UIChildImGuiDX10(WindowChildConfig* pConfig) : UIChild(pConfig) {
  Init();
 }
 UIChildImGuiDX10::~UIChildImGuiDX10() {
  UnInit();
 }
 void UIChildImGuiDX10::Release() const {
  delete this;
 }
 void UIChildImGuiDX10::Init() {
  do {
   m_pConfig->Host(this);
   if (!m_pConfig->WndProcPtr())
    m_pConfig->WndProcPtr((void*)
     [](HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)->LRESULT {
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
       if (!pThis)
        break;
      }break;
      default:
       break;
      }
      if (pThis && pThis->OnWindowProc(hwnd, message, wParam, lParam))
       return 0;
      return ::DefMDIChildProcW(hwnd, message, wParam, lParam);   
     });
   if (m_pConfig->WindowStyle() == 0)
    m_pConfig->WindowStyle(CS_CLASSDC);
   if (m_pConfig->WindowClassName().empty())
    m_pConfig->WindowClassName(__mapChildWindowClassName.at(EnUIChildType::DearImGui));
   if (m_pConfig->WindowTitleText().empty())
    m_pConfig->WindowTitleText(LR"(Untitled)");
   if (FALSE == ::RegisterClassExW(&m_pConfig->WndClassEx()))
    break;
  } while (0);

 }
 void UIChildImGuiDX10::UnInit() {
  if (m_Ready.load()) {
   ImGui_ImplDX10_Shutdown();
   ImGui_ImplWin32_Shutdown();
   ImGui::DestroyContext();
   ImGuiMain::CleanupRenderTarget(m_pD3D10RenderTargetView);
   ImGuiMain::CleanupDeviceD3D(m_pD3D10Device, m_pDXGISwapChain);
  }
  ::UnregisterClassW(m_pConfig->WindowClassName().c_str(), m_pConfig->Hinstance());
  m_Ready.store(false);
 }
 bool UIChildImGuiDX10::Create() {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_hWnd = (HWND)::SendMessageW(
   m_pConfig->ParentClientHwnd(),
   WM_MDICREATE,
   0,
   (LPARAM)&m_pConfig->MdiCreateStructW());
  return m_hWnd ? true : false;
 }
 void UIChildImGuiDX10::Destory() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };

 }
 void UIChildImGuiDX10::OnRender() {
  do {
   if (!m_Ready.load())
    break;
   ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.0f);
   // Start the Dear ImGui frame
   ImGui_ImplDX10_NewFrame();
   ImGui_ImplWin32_NewFrame();
   ImGui::NewFrame();
   {
    ImGui::PushFont(m_ImFonts[LR"(segoeui)"]);
    ImGui::Begin(std::format("Hello, martell !").c_str());
    ImGui::PopFont();

    ImGui::PushFont(m_ImFonts[LR"(simfang)"]);
    ImGui::Text((char*)u8"您好 !"); // Display some text (you can use a format strings too)
    ImGui::PopFont();
    ImGui::End();
   }
   // Rendering
   ImGui::Render();
   /*const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };*/
   DWORD dwDefaultRgb = m_pConfig->DefaultBackgroundColor();
   int B = dwDefaultRgb & 0xFF;
   dwDefaultRgb >>= 8;
   int G = dwDefaultRgb & 0xFF;
   dwDefaultRgb >>= 8;
   int R = dwDefaultRgb & 0xFF;
   dwDefaultRgb >>= 8;
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
 bool UIChildImGuiDX10::OnWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (ImGuiMain::IMGUI_WndProc(hwnd, message, wParam, lParam))
   return true;
  bool result = false;
  switch (message) {
  case WM_ACTIVATE: {

   result = true;
  }break;
  case WM_SIZE: {
   if (wParam == SIZE_MINIMIZED)
    break;
   if (!m_Ready.load())
    break;
   void(ImGuiMain::CleanupRenderTarget(m_pD3D10RenderTargetView));
   void(m_pDXGISwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0));
   void(ImGuiMain::CreateRenderTarget(m_pD3D10Device, m_pDXGISwapChain, &m_pD3D10RenderTargetView));
  }break;
  case WM_CREATE: {
   m_hWnd = hwnd;
   if (!ImGuiMain::CreateDeviceD3D(hwnd, &m_pD3D10Device, &m_pDXGISwapChain))
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
   m_ImFonts.emplace(LR"(segoeui)", io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\segoeui.ttf)", 18.0f));
   m_ImFonts.emplace(LR"(simhei)", io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\simhei.ttf)", 18.0f));
   m_ImFonts.emplace(LR"(simfang)", io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\simfang.ttf)", 50.0f, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon()));
   // Setup Dear ImGui style
   ImGui::StyleColorsDark();
   //ImGui::StyleColorsLight();
   // Setup Platform/Renderer backends
   if (!ImGui_ImplWin32_Init(hwnd))
    break;
   if (!ImGui_ImplDX10_Init(m_pD3D10Device))
    break;
   m_Ready.store(true);
   result = true;
  }break;
  case WM_DESTROY: {
   result = true;
  }break;
  default:
   break;
  }///switch

  return result;
 }
}///namespace local
