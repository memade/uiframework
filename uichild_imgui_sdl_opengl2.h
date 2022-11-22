#if !defined(INC_H___23F518E1_175A_449C_98E1_E650B29F571F__HEAD__)
#define INC_H___23F518E1_175A_449C_98E1_E650B29F571F__HEAD__
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl2.h>
#pragma comment(lib,"Setupapi.lib")
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"Imm32.lib")
#pragma comment(lib,"Version.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"SDL2.lib")
#include <SDL.h>
#include <SDL_opengl.h>

namespace local {

 class UIChildImGuiSDLOpenGL2 final : public UIChild {
 public:
  UIChildImGuiSDLOpenGL2(WindowChildConfig* pConfig);
 protected:
  bool Create() override final;
  void Destory() override final;
  void Release() const override final;
 private:
  virtual ~UIChildImGuiSDLOpenGL2();
  void Init();
  void UnInit();
 protected:
  void OnRender() override final;
 private:
  SDL_Window* m_pSDLWindow = nullptr;
 private:
  bool OnWindowProc(HWND, UINT, WPARAM, LPARAM) override final;
 };

}///namespace local
/// /*新生®（上海）**/
/// /*2022_11_22T04:55:13.6413276Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___23F518E1_175A_449C_98E1_E650B29F571F__HEAD__
