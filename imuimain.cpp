#include "stdafx.h"

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace local {
 ImGuiMain::ImGuiMain(WindowConfig* pConfig)
  : UIBase(pConfig) {
  m_pConfig->Hinstance(__gpHinstance);
  WNDCLASSEXW wc = { 0 };
  wc.cbSize = sizeof(wc);
  wc.style = CS_CLASSDC;
  wc.lpfnWndProc = ImGuiMain::WndProc;
  wc.cbClsExtra = 0L;
  wc.cbWndExtra = 0L;
  wc.hInstance = pConfig->Hinstance();
  wc.hIcon = NULL;
  wc.hCursor = NULL;
  wc.hbrBackground = NULL;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = pConfig->WindowClassName().c_str();
  wc.hIconSm = NULL;
  void(::RegisterClassExW(&wc));
 }
 ImGuiMain::~ImGuiMain() {
  void(::UnregisterClassW(m_pConfig->WindowClassName().c_str(), m_pConfig->Hinstance()));
 }
 void ImGuiMain::Release() const {
  delete this;
 }
 void ImGuiMain::MainProcess() {
  do {
   // Create application window
   if (m_pConfig->EnableDpiAwareness())
    ImGui_ImplWin32_EnableDpiAwareness();

   m_hWnd = ::CreateWindowW(
    m_pConfig->WindowClassName().c_str(),
    m_pConfig->MainWindowTitleText().c_str(),
    WS_OVERLAPPEDWINDOW,
    m_pConfig->DefaultPosition().x,
    m_pConfig->DefaultPosition().y,
    m_pConfig->DefaultSize().cx,
    m_pConfig->DefaultSize().cy,
    NULL,
    NULL,
    m_pConfig->Hinstance(),
    this);
   if (!m_hWnd)
    break;
   if (!CreateDeviceD3D(m_hWnd))
    break;
   void(::ShowWindow(m_hWnd, m_ShowFlag.load() ? SW_SHOWNORMAL : SW_HIDE));
   void(::UpdateWindow(m_hWnd));
   // Setup Dear ImGui context
   IMGUI_CHECKVERSION();
   auto pImGuiContext = ImGui::CreateContext();
   if (!pImGuiContext)
    break;
   ImGuiIO& io = ImGui::GetIO(); (void)io;
   //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
   //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
   ImFont* font_segoeui = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
   ImFont* font_simfang = io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\simfang.ttf)", 50.0f, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
   //io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\simhei.ttf)", 13.0f, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());

   // Setup Dear ImGui style
   ImGui::StyleColorsDark();
   //ImGui::StyleColorsLight();

   // Setup Platform/Renderer backends
   if (!ImGui_ImplWin32_Init(m_hWnd))
    break;
   if (!ImGui_ImplDX10_Init(m_pd3dDevice))
    break;
   m_IsOpen.store(true);
   ::SetEvent(m_hUIMainCreateEvent);

   // Load Fonts
   // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
   // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
   // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
   // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
   // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
   // - Read 'docs/FONTS.md' for more instructions and details.
   // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
   //io.Fonts->AddFontDefault();
   //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
   //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
   //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
   //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
   //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
   //IM_ASSERT(font != NULL);
   //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
   //ImGui::PushFont(font);
   // Our state
   //ImFont* font1 = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());

   ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.0f);

   do {
    // Poll and handle messages (inputs, window resize, etc.)
    // See the WndProc() function below for our to dispatch events to the Win32 backend.
    MSG msg;
    while (::PeekMessageW(&msg, NULL, 0U, 0U, PM_REMOVE)) {
     ::TranslateMessage(&msg);
     ::DispatchMessageW(&msg);
     if (msg.message == WM_QUIT)
      m_IsOpen.store(false);
    }
    if (!m_IsOpen.load())
     break;
    // Start the Dear ImGui frame
    ImGui_ImplDX10_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    {
     ImGui::PushFont(font_segoeui);
     ImGui::Begin(std::format("Hello, martell !").c_str());
     ImGui::PopFont();

     ImGui::PushFont(font_simfang);
     ImGui::Text((char*)u8"您好 !"); // Display some text (you can use a format strings too)
     ImGui::PopFont();
     ImGui::End();
    }
    // Rendering
    ImGui::Render();
    const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
    //DWORD dwDefaultRgb = m_pConfig->DefaultBackgroundColor();
    //int B = dwDefaultRgb & 0xFF; dwDefaultRgb >>= 8;
    //int G = dwDefaultRgb & 0xFF; dwDefaultRgb >>= 8;
    //int R = dwDefaultRgb & 0xFF; dwDefaultRgb >>= 8;
    //const auto alpha = static_cast<float>(m_pConfig->DefaultBackgroundTransparency());
    //const float clear_color_with_alpha[4] = {
    // static_cast<float>(R / 255.0 * alpha),
    // static_cast<float>(G / 255.0 * alpha),
    // static_cast<float>(B / 255.0 * alpha),
    // alpha };
    m_pd3dDevice->OMSetRenderTargets(1, &m_mainRenderTargetView, NULL);
    m_pd3dDevice->ClearRenderTargetView(m_mainRenderTargetView, clear_color_with_alpha);
    ImGui_ImplDX10_RenderDrawData(ImGui::GetDrawData());
    m_pSwapChain->Present(1, 0); // Present with vsync


    __super::ShowControl();
   } while (1);


   ImGui_ImplDX10_Shutdown();
   ImGui_ImplWin32_Shutdown();
   ImGui::DestroyContext();
   CleanupDeviceD3D();
   ::DestroyWindow(m_hWnd);

  } while (0);

 }
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 void ImGuiMain::CreateRenderTarget() {
  ID3D10Texture2D* pBackBuffer = nullptr;
  m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
  if (pBackBuffer) {
   m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_mainRenderTargetView);
   pBackBuffer->Release();
  }
 }
 bool ImGuiMain::CreateRenderTarget(ID3D10Device* inpD3D10Device, IDXGISwapChain* inpDXGISwapChain, ID3D10RenderTargetView** outpD3D10RenderTargetView) {
  bool result = false;
  do {
   if (!inpD3D10Device || !inpDXGISwapChain)
    break;
   ID3D10Texture2D* pBackBuffer = nullptr;
   if (S_OK != inpDXGISwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer)) || !pBackBuffer)
    break;
   result = S_OK == inpD3D10Device->CreateRenderTargetView(pBackBuffer, NULL, outpD3D10RenderTargetView) && outpD3D10RenderTargetView;
   SK_COM_RELEASE(pBackBuffer);
  } while (0);
  return result;
 }
 void ImGuiMain::CleanupRenderTarget(ID3D10RenderTargetView* inpD3D10RenderTargetView) {
  SK_COM_RELEASE(inpD3D10RenderTargetView);
 }
 void ImGuiMain::CleanupDeviceD3D(ID3D10Device* inpD3D10Device, IDXGISwapChain* inpDXGISwapChain) {
  SK_COM_RELEASE(inpDXGISwapChain);
  SK_COM_RELEASE(inpD3D10Device);
 }
 void ImGuiMain::CleanupRenderTarget() {
  SK_COM_RELEASE(m_mainRenderTargetView);
 }
 void ImGuiMain::CleanupDeviceD3D() {
  CleanupRenderTarget();
  SK_COM_RELEASE(m_pSwapChain);
  SK_COM_RELEASE(m_pd3dDevice);
 }
 bool ImGuiMain::CreateDeviceD3D(const HWND& hWnd, ID3D10Device** outpD3D10Device, IDXGISwapChain** outpDXGISwapChain) {
  bool result = false;
  do {
   if (!hWnd)
    break;
   DXGI_SWAP_CHAIN_DESC sd = { 0 };
   sd.BufferCount = 2;
   sd.BufferDesc.Width = 0;
   sd.BufferDesc.Height = 0;
   sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
   sd.BufferDesc.RefreshRate.Numerator = 60;
   sd.BufferDesc.RefreshRate.Denominator = 1;
   sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
   sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
   sd.OutputWindow = hWnd;
   sd.SampleDesc.Count = 1;
   sd.SampleDesc.Quality = 0;
   sd.Windowed = TRUE;
   sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
   UINT createDeviceFlags = 0;
   //createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
   if (S_OK != ::D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, D3D10_SDK_VERSION, &sd, outpDXGISwapChain, outpD3D10Device))
    break;
   if (!*outpDXGISwapChain || !*outpD3D10Device)
    break;
   result = true;
  } while (0);
  return result;
 }
 // Forward declarations of helper functions
 bool ImGuiMain::CreateDeviceD3D(const HWND& hWnd) {
  bool result = false;
  do {
   if (!hWnd)
    break;
   // Setup swap chain
   DXGI_SWAP_CHAIN_DESC sd = { 0 };
   sd.BufferCount = 2;
   sd.BufferDesc.Width = 0;
   sd.BufferDesc.Height = 0;
   sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
   sd.BufferDesc.RefreshRate.Numerator = 60;
   sd.BufferDesc.RefreshRate.Denominator = 1;
   sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
   sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
   sd.OutputWindow = hWnd;
   sd.SampleDesc.Count = 1;
   sd.SampleDesc.Quality = 0;
   sd.Windowed = TRUE;
   sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
   UINT createDeviceFlags = 0;
   //createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
   if (D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, D3D10_SDK_VERSION, &sd, &m_pSwapChain, &m_pd3dDevice) != S_OK)
    break;
   CreateRenderTarget();
   result = true;
  } while (0);
  return result;
 }
 LRESULT ImGuiMain::IMGUI_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
 }
 LRESULT WINAPI ImGuiMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
   return 1;

  switch (msg) {
  case WM_CREATE: {
   LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
   if (!pCreateStruct)
    break;
   ::SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
   return 1;
  }break;
  case WM_SIZE: {
   LONG_PTR this_ptr = ::GetWindowLongPtrW(hWnd, GWLP_USERDATA);
   auto pThis = reinterpret_cast<ImGuiMain*>(this_ptr);
   if (!pThis)
    break;

   if (pThis->m_pd3dDevice != NULL && wParam != SIZE_MINIMIZED) {
    pThis->CleanupRenderTarget();
    pThis->m_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
    pThis->CreateRenderTarget();
   }
   return 0;
  }break;
  case WM_SYSCOMMAND:
   if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
    return 0;
   break;
  case WM_DESTROY:
   ::PostQuitMessage(0);
   return 0;
  }
  return ::DefWindowProcW(hWnd, msg, wParam, lParam);
 }

}///namespace local
