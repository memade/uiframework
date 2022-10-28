#if !defined(INC_H___32635550_CB94_418B_9EC2_781093F45F3C__HEAD__)
#define INC_H___32635550_CB94_418B_9EC2_781093F45F3C__HEAD__

namespace local {

 class UIStatusBar final : public shared::ui::UIFrame, public UIBase {
 public:
  UIStatusBar(const UIType&, const bool&);
  ~UIStatusBar();
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
  LPCTSTR GetWindowClassName() const override final { return _TEXT("uistatusbar"); }
  LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
 private:
  CButtonUI* m_pUIButtonActivateDownTable = nullptr;
  CButtonUI* m_pUIButtonDownTotalCount = nullptr;
  CProgressUI* m_pUIProgress = nullptr;
  CLabelUI* m_pUITextGameDownload = nullptr;
 protected:
  void DownStatusTotalCount(const size_t&) override final;
  size_t DownStatusTotoalCount() const override final;
  void StatusbarProgressCtrl(const bool&) override final;
  void Refresh() const override final;
 };

}///namespace local

/// /*新生®（上海）**/
/// /*2022_09_10T22:40:11.1950911Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___32635550_CB94_418B_9EC2_781093F45F3C__HEAD__
