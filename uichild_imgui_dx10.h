#if !defined(INC_H___3BF252AE_6FA2_4D4F_ABFB_993AD5FD022D__HEAD__)
#define INC_H___3BF252AE_6FA2_4D4F_ABFB_993AD5FD022D__HEAD__
#include <backends/imgui_impl_dx10.h>
#include <backends/imgui_impl_win32.h>
#include <d3d10.h>
#pragma comment(lib,"d3d10.lib")

namespace local {

 class UIChildImGuiDX10 final : public UIChild {
 public:
  UIChildImGuiDX10(WindowChildConfig* pConfig);
 protected:
  bool Create() override final;
  void Destory() override final;
  void Release() const override final;
 private:
  virtual ~UIChildImGuiDX10();
  void Init();
  void UnInit();
 protected:
  void OnRender() override final;
  //bool OnWindowProc(HWND, UINT, WPARAM, LPARAM) override final;
 private:
  std::map<std::wstring, ImFont*> m_ImFonts;
  ID3D10Device* m_pD3D10Device = nullptr;
  IDXGISwapChain* m_pDXGISwapChain = nullptr;
  ID3D10RenderTargetView* m_pD3D10RenderTargetView = nullptr;
  bool OnWindowProc(HWND, UINT, WPARAM, LPARAM) override final;
 };

}///namespace local

/// /*新生®（上海）**/
/// /*2022_11_21T02:28:10.4185513Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___3BF252AE_6FA2_4D4F_ABFB_993AD5FD022D__HEAD__






