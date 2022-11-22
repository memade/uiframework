#if !defined(INC_H___7C3CE2F1_B221_4448_9F73_8CDCC9E1DA75__HEAD__)
#define INC_H___7C3CE2F1_B221_4448_9F73_8CDCC9E1DA75__HEAD__

namespace local {

 class UIChildWin32 final : public UIChild {
 public:
  UIChildWin32(WindowChildConfig* pConfig);
 protected:
  bool Create() override final;
  void Destory() override final;
  void Release() const override final;
 private:
  virtual ~UIChildWin32();
  void Init();
  void UnInit();
 protected:
  void OnRender() override final;
  bool OnWindowProc(HWND, UINT, WPARAM, LPARAM) override final;
 };

}///namespace local

/// /*新生®（上海）**/
/// /*2022_11_21T09:41:24.0049213Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___7C3CE2F1_B221_4448_9F73_8CDCC9E1DA75__HEAD__






