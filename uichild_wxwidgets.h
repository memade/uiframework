#if !defined(INC_H___675957F6_10BB_4DC7_BAF2_CFCE169F2F5A__HEAD__)
#define INC_H___675957F6_10BB_4DC7_BAF2_CFCE169F2F5A__HEAD__

namespace local {

 class UIChildWxwidgets final : public UIChild {
 public:
  UIChildWxwidgets(WindowChildConfig* pConfig);
 protected:
  bool Create() override final;
  void Destory() override final;
  void Release() const override final;
 private:
  virtual ~UIChildWxwidgets();
  void Init();
  void UnInit();
 protected:
  void OnRender() override final;
  bool OnWindowProc(HWND, UINT, WPARAM, LPARAM) override final;
 private:
  shared::wx::IwxApp* m_pwxApp = nullptr;
  wxWindow* m_pwxWindow = nullptr;
 };

}///namespace local

/// /*新生®（上海）**/
/// /*2022_11_21T16:03:44.7129434Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___675957F6_10BB_4DC7_BAF2_CFCE169F2F5A__HEAD__


