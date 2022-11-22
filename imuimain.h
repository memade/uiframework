#if !defined(INC_H___F3BB539C_AF5E_4710_948E_A57D36BF77C7__HEAD__)
#define INC_H___F3BB539C_AF5E_4710_948E_A57D36BF77C7__HEAD__

namespace local {
 class ImGuiMain final : public UIBase {
 public:
  ImGuiMain(WindowConfig*);
 public:
  void Release() const override final;
 protected:
  void MainProcess() override final;
 private:
  ~ImGuiMain();
 private:
  ID3D10Device* m_pd3dDevice = nullptr;
  IDXGISwapChain* m_pSwapChain = nullptr;
  ID3D10RenderTargetView* m_mainRenderTargetView = nullptr;
 public:
  bool CreateDeviceD3D(const HWND&);
  void CleanupRenderTarget();
  void CreateRenderTarget();
  void CleanupDeviceD3D();
  static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
 public:
  static void CleanupRenderTarget(ID3D10RenderTargetView*);
  static void CleanupDeviceD3D(ID3D10Device*, IDXGISwapChain*);
  static bool CreateRenderTarget(ID3D10Device*, IDXGISwapChain*, ID3D10RenderTargetView**);
  static bool CreateDeviceD3D(const HWND&, ID3D10Device**, IDXGISwapChain**);
  static LRESULT IMGUI_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
 };

}///namespace local

/// /*新生®（上海）**/
/// /*2022_11_15T08:07:37.6227632Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___F3BB539C_AF5E_4710_948E_A57D36BF77C7__HEAD__

