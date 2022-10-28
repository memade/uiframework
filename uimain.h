#if !defined(INC_H___9EB34D25_2683_4373_BC71_57A08FCA40E1__HEAD__)
#define INC_H___9EB34D25_2683_4373_BC71_57A08FCA40E1__HEAD__

namespace local {

 class UIMain final : public shared::ui::UIFrame, public UIBase {
 public:
  UIMain(const UIType&, const bool&);
  ~UIMain();
 protected:
  void Init();
  void UnInit();
  void Create() override final;
  void Destory() override final;
  const HWND& Hwnd() const;
  bool IsOpen() const;
 protected:
  void InitWindow() override final;
  void Notify(TNotifyUI& msg) override final;
  void OnFinalMessage(HWND hWnd) override final;
  CControlUI* CreateControl(LPCTSTR pstrClassName) override final;
  LPCTSTR GetWindowClassName() const override final { return _TEXT("uimain"); }
  LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
 private:
  CTabLayoutUI* m_pTabLayoutUIMain = nullptr;
  std::vector<CControlUI*> m_CustomControls;
 };

}///namespace local

/// /*新生®（上海）**/
/// /*2022_09_28T01:28:54.4670736Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___9EB34D25_2683_4373_BC71_57A08FCA40E1__HEAD__

