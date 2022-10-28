#if !defined(INC_H___63609CD0_85F1_4F8C_89CB_943FB4658EFF__HEAD__)
#define INC_H___63609CD0_85F1_4F8C_89CB_943FB4658EFF__HEAD__


namespace local {

	class UIDownManager final : public shared::ui::UIFrame, public UIBase {
	public:
		UIDownManager(const UIType&, const bool&);
		~UIDownManager();
	protected:
		void Init();
		void UnInit();
		void Create() override final;
		void Destory() override final;
		const HWND& Hwnd() const;
		bool IsOpen() const;
	protected:
		void ShowWindow(bool bShow = true, bool bTakeFocus = true);
		void InitWindow() override final;
		void Notify(TNotifyUI& msg) override final;
		void OnFinalMessage(HWND hWnd) override final;
		CControlUI* CreateControl(LPCTSTR pstrClassName) override final;
		LPCTSTR GetWindowClassName() const override final { return _TEXT("uidownmanager"); }
		LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
		LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
		LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
		LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
		LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
		LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
		LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
	public:
		CTabLayoutUI* m_pUITabLayoutMain = nullptr;
		CTabLayoutUI* m_pUITabLayoutDownsuc = nullptr;
		CTabLayoutUI* m_pUITabLayoutDowning = nullptr;
		CListUI* m_pUIListLocalResource = nullptr;
		CListUI* m_pUIListDownTask = nullptr;
		COptionUI* m_pUIOptionDowning = nullptr;
		COptionUI* m_pUIOptionDownsuc = nullptr;
		CButtonUI* m_pUIButtonSystemClose = nullptr;
	protected:
		bool RemoveDownTaskNode(TaskNode*) override final;
		bool AppendDownTaskNode(TaskNode*) override final;
		unsigned int UIListDownTaskCount() const override final;
		bool SwitchPage(const EnChildPageType&) override final;
	};


}///namespace local

/// /*新生®（上海）**/
/// /*2022_09_10T22:44:17.2090544Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___63609CD0_85F1_4F8C_89CB_943FB4658EFF__HEAD__
