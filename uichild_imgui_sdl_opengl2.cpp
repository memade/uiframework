#include "stdafx.h"

namespace local {
 UIChildImGuiSDLOpenGL2::UIChildImGuiSDLOpenGL2(WindowChildConfig* pConfig) : UIChild(pConfig) {
  Init();
 }
 UIChildImGuiSDLOpenGL2::~UIChildImGuiSDLOpenGL2() {
  UnInit();
 }
 void UIChildImGuiSDLOpenGL2::Release() const {
  delete this;
 }
 void UIChildImGuiSDLOpenGL2::Init() {
  do {
   // Setup SDL
   // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
   // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to the latest version of SDL is recommended!)
   if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    break;

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
 void UIChildImGuiSDLOpenGL2::UnInit() {
  if (m_Ready.load()) {

  }
  ::UnregisterClassW(m_pConfig->WindowClassName().c_str(), m_pConfig->Hinstance());
  m_Ready.store(false);
 }
 bool UIChildImGuiSDLOpenGL2::Create() {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_hWnd = (HWND)::SendMessageW(
   m_pConfig->ParentClientHwnd(),
   WM_MDICREATE,
   0,
   (LPARAM)&m_pConfig->MdiCreateStructW());
  return m_hWnd ? true : false;
 }
 void UIChildImGuiSDLOpenGL2::Destory() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };

 }
 void UIChildImGuiSDLOpenGL2::OnRender() {
  do {
   if (!m_Ready.load())
    break;
   bool done = false;
   SDL_Event event;
   while (SDL_PollEvent(&event))
   {
    ImGui_ImplSDL2_ProcessEvent(&event);
    if (event.type == SDL_QUIT)
     done = true;
    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(m_pSDLWindow))
     done = true;
   }
   // Start the Dear ImGui frame
   ImGui_ImplOpenGL2_NewFrame();
   ImGui_ImplSDL2_NewFrame();
   ImGui::NewFrame();
   ImGuiIO& io = ImGui::GetIO();

   bool show_demo_window = true;
   bool show_another_window = false;
   ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

   // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
   if (show_demo_window)
    ImGui::ShowDemoWindow(&show_demo_window);

   // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
   {
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
     counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
   }

   // 3. Show another simple window.
   if (show_another_window)
   {
    ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close Me"))
     show_another_window = false;
    ImGui::End();
  }

   // Rendering
   ImGui::Render();
   glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
   glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
   glClear(GL_COLOR_BUFFER_BIT);
   //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
   ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
   SDL_GL_SwapWindow(m_pSDLWindow);
  } while (0);
 }
 bool UIChildImGuiSDLOpenGL2::OnWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (ImGuiMain::IMGUI_WndProc(hwnd, message, wParam, lParam))
   return true;
  bool result = false;
  switch (message) {
  case WM_ACTIVATE: {

   result = true;
  }break;
  case WM_CREATE: {
   // Setup window
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
   SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
   SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
   //SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
   m_pSDLWindow = SDL_CreateWindowFrom(hwnd);
   SDL_GLContext gl_context = SDL_GL_CreateContext(m_pSDLWindow);
   SDL_GL_MakeCurrent(m_pSDLWindow, gl_context);
   SDL_GL_SetSwapInterval(1); // Enable vsync

   // Setup Dear ImGui context
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO& io = ImGui::GetIO(); (void)io;
   //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
   //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

   // Setup Dear ImGui style
   ImGui::StyleColorsDark();
   //ImGui::StyleColorsLight();

   // Setup Platform/Renderer backends
   if (!ImGui_ImplSDL2_InitForOpenGL(m_pSDLWindow, gl_context))
    break;
   if (!ImGui_ImplOpenGL2_Init())
    break;

   m_Ready.store(true);
   result = true;
  }break;
  case WM_SIZE: {
   if (wParam == SIZE_MINIMIZED)
    break;
   if (!m_Ready.load())
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
