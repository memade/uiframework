#if !defined(INC_H___0AE7CDEA_2500_463B_B00E_E351BF0E87B8__HEAD__)
#define INC_H___0AE7CDEA_2500_463B_B00E_E351BF0E87B8__HEAD__

namespace local {

	class UIMessageBox final : public shared::ui::UIFrame, public UIBase {
	public:
		UIMessageBox(const UIType&, const bool&);
		~UIMessageBox();
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
		LPCTSTR GetWindowClassName() const override final { return _TEXT("uiconfigure"); }
		LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
		LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
		LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
		LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
		LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
		LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
		LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
	};

}///namespace local

/// /*新生®（上海）**/
/// /*2022_09_12T04:06:04.2045632Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___0AE7CDEA_2500_463B_B00E_E351BF0E87B8__HEAD__


