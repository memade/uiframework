#include "stdafx.h"

namespace local {
	UIDownManager::UIDownManager(const UIType& uitype, const bool& init_show) : UIBase(uitype, init_show) {
		Init();
	}
	UIDownManager::~UIDownManager() {
		UnInit();
	}
	void UIDownManager::Init() {
	}
	void UIDownManager::UnInit() {
	}
	void UIDownManager::OnFinalMessage(HWND hWnd) {
		/*delete this;*////Release can cause a crash
	}
	const HWND& UIDownManager::Hwnd() const {
		return UIBase::m_hWnd;
	}
	bool UIDownManager::IsOpen() const {
		return m_IsOpen.load();
	}
	void UIDownManager::Create() {
		do {
			if (m_IsOpen.load())
				break;
			CPaintManagerUI::SetInstance(__gpHinstance);
#if 0
#ifdef _DEBUG
			/*auto sss = CPaintManagerUI::GetInstancePath();*/
			CPaintManagerUI::SetResourcePath(LR"(D:\__SVN__\Memade\projects\pcdown\res\skin\)");
#else
			//std::string res = shared::Win::File::Read(R"(D:\__SVN__\Memade\projects\pcdown\res\skin.zip)");
			////*Global::SetupGet() << shared::Win::File::Read(R"(E:\__SVN__\Memade\projects\downtool\res\setup.xml)");
			//if (res.empty())
			//	break;
			std::string res = std::string((char*)&skin_zip_res[0], sizeof(skin_zip_res));
			res = shared::Encryption::WemadeDecode(res);
			if (!shared::Zip::IsZipCompress(res))
				break;
			CPaintManagerUI::SetResourceZip(res.data(), static_cast<unsigned int>(res.size()));
#endif
#else
#ifdef _DEBUG
			CPaintManagerUI::SetResourcePath(LR"(D:\__SVN__\Memade\projects\pcdown\res\skin\)");
#else
			CPaintManagerUI::SetResourcePath(Global::PCHackerGet()->UISkinDirectory().c_str());
#endif
#endif

			DWORD dwCreateStyle = UI_WNDSTYLE_FRAME;
			do {
				if (m_Show.load())
					break;
				if (!(dwCreateStyle & WS_VISIBLE))
					break;
				dwCreateStyle &= ~WS_VISIBLE;
			} while (0);
			UIBase::m_hWnd = UIFrame::Create(NULL, _TEXT("PCDown Manager®"), dwCreateStyle, 0L);
			if (!UIBase::m_hWnd)
				break;
			m_IsOpen.store(true);
			CenterWindow();
			CPaintManagerUI::MessageLoop();
		} while (0);
	}
	void UIDownManager::Destory() {
		do {
			if (!m_IsOpen.load())
				break;
			for (auto& it : m_Threads)
				it.join();
			m_Threads.clear();
			UIFrame::Close(IDOK);
			m_IsOpen.store(false);
		} while (0);

	}
	void UIDownManager::InitWindow() {
		m_pUITabLayoutMain = GetCtrl<CTabLayoutUI>(LR"(F8CB64B38563)");
		m_pUITabLayoutDowning = GetCtrl<CTabLayoutUI>(LR"(D6B8863320C6)");
		m_pUITabLayoutDownsuc = GetCtrl<CTabLayoutUI>(LR"(516D679BA67B)");
		m_pUIListLocalResource = GetCtrl<CListUI>(LR"(CB0884D16B20)");
		m_pUIListDownTask = GetCtrl<CListUI>(LR"(0B36A7206C94)");
		m_pUIOptionDowning = GetCtrl<COptionUI>(LR"(BC7F1E5583F8)");
		m_pUIOptionDownsuc = GetCtrl<COptionUI>(LR"(7F3985EFCB8E)");
		m_pUIButtonSystemClose = GetCtrl<CButtonUI>(LR"(7A98852B5AD7)");

		if (m_pUIOptionDowning)
			m_pUIOptionDowning->Selected(true);
	}

	LRESULT UIDownManager::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		bHandled = FALSE;
		return 0;
	}
	LRESULT UIDownManager::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		LONG styleValue = ::GetWindowLongW(*this, GWL_STYLE);
		styleValue &= ~WS_CAPTION;
		::SetWindowLongW(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

		LONG ExStyleValue = ::GetWindowLongW(*this, GWL_EXSTYLE);
		if (!(ExStyleValue & WS_EX_TOOLWINDOW)) {
			ExStyleValue |= WS_EX_TOOLWINDOW;
			::SetWindowLongW(*this, GWL_EXSTYLE, ExStyleValue);
		}

		m_pm.Init(GetHWND());
		CDialogBuilder builder;
		CControlUI* pRoot = builder.Create(std::wstring(GetWindowClassName()).append(_TEXT(".xml")).c_str(), (LPCTSTR)0, NULL, &m_pm);
		

		ASSERT(pRoot && "Failed to parse 'ui.xml'");
		m_pm.AttachDialog(pRoot);
		m_pm.AddNotifier(this);
		bHandled = TRUE;
		return 0;
	}

	LRESULT UIDownManager::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		bHandled = FALSE;
		return 0;
	}
	LRESULT UIDownManager::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		bHandled = FALSE;
		return 0;
	}
	LRESULT UIDownManager::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		bHandled = FALSE;
		return 0;
	}
	LRESULT UIDownManager::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}

	LRESULT UIDownManager::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		bHandled = FALSE;
		return 0;
	}
	CControlUI* UIDownManager::CreateControl(LPCTSTR pstrClassName) {
		return nullptr;
	}

	void UIDownManager::Notify(TNotifyUI& msg) {
		if (msg.sType == DUI_MSGTYPE_HEADERCLICK) {
		}///DUI_MSGTYPE_HEADERCLICK
#if 0
		else if (msg.sType == DUI_MSGTYPE_LINK) {
			CTextUI* pText = (CTextUI*)msg.pSender;
			CDuiString* strUrl = pText->GetLinkContent(0);
			::ShellExecute(NULL, _T("open"), strUrl->GetData(), NULL, NULL, SW_SHOWNORMAL);
		}
#endif
		else if (msg.sType == DUI_MSGTYPE_CHECKCLICK) {

		}
		else if (msg.sType == DUI_MSGTYPE_CLICK) {
			if (msg.pSender == m_pUIButtonSystemClose || \
				/*浏览游戏*/
				msg.pSender->GetName() == L"A66590EB6D37" || 
				msg.pSender->GetName() == L"6DBE42A6ACC5"
				) {
				ShowWindow(false);
			}
			else if (msg.pSender->GetName() == L"469E58562CD1") {//!@ 下载任务节点移除
				auto parent = shared::ui::FindControlParent(msg.pSender, L"89AF1FBB3D8B");
				do {
					if (!parent)
						break;
					Global::PCHackerGet()->TaskAction(parent->GetTagUINT64(),EnActionType::DownRemove);
				} while (0);
			}
			else if (msg.pSender->GetName() == L"06A057E7350B") {//!@ 下载任务节点暂停/停止 | 开始/启动
				auto running = ((COptionUI*)msg.pSender)->IsSelected();
				auto parent = shared::ui::FindControlParent(msg.pSender, L"89AF1FBB3D8B");
				do {
					if (!parent)
						break;
					Global::PCHackerGet()->TaskAction(parent->GetTagUINT64(), running ? EnActionType::DownPause : EnActionType::DownPreparation);
				} while (0);
			}
			else if (msg.pSender->GetName() == L"D90336733AF1") {//!@ 下载任务节点重置
				auto parent = shared::ui::FindControlParent(msg.pSender, L"89AF1FBB3D8B");
				do {
					if (!parent)
						break;
					Global::PCHackerGet()->TaskAction(parent->GetTagUINT64(), EnActionType::DownReset);
				} while (0);
			}
			else if (msg.pSender == m_pUIOptionDowning) {
				do {
					if (!m_pUITabLayoutMain)
						break;
					m_pUITabLayoutMain->SelectItem(static_cast<int>(EnMainPageType::Downing));
				} while (0);
			}
			else if (msg.pSender == m_pUIOptionDownsuc) {
				do {
					if (!m_pUITabLayoutMain)
						break;
					m_pUITabLayoutMain->SelectItem(static_cast<int>(EnMainPageType::Success));
				} while (0);
			}


		}
		else {

		}
	}
	bool UIDownManager::SwitchPage(const EnChildPageType& type) {
		bool result = false;
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		do {
			if (!m_pUITabLayoutDowning)
				break;
			if (m_pUITabLayoutDowning->GetCount() < static_cast<int>(type))
				break;
			if (m_pUITabLayoutDowning->GetCurSel() == static_cast<int>(type)) {
				result = true;
				break;
			}
			if (!m_pUITabLayoutDowning->SelectItem(static_cast<int>(type)))
				break;
			result = true;
		} while (0);
		return result;
	}
	void UIDownManager::ShowWindow(bool bShow /*= true*/, bool bTakeFocus /*= true*/) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_Show.store(bShow);
		__super::ShowWindow(bShow, bTakeFocus);
	}
	unsigned int UIDownManager::UIListDownTaskCount() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_pUIListDownTask->GetCount();
	}
	bool UIDownManager::RemoveDownTaskNode(TaskNode* pTaskNode) {
		bool result = false;
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		do {
			if (!pTaskNode)
				break;
			if (!pTaskNode->Verify())
				break;
			if (!m_pUIListDownTask)
				break;
			int lines = m_pUIListDownTask->GetCount();
			if (lines <= 0)
				break;
			auto found_id = pTaskNode->ID();
			for (int i = 0; i < lines; ++i) {
				auto the = m_pUIListDownTask->GetItemAt(i);
				if (!the)
					continue;
				if (found_id != the->GetTagUINT64())
					continue;
				result = m_pUIListDownTask->RemoveAt(i);
				break;
			}
		} while (0);
		return result;
	}
	bool UIDownManager::AppendDownTaskNode(TaskNode* pTaskNode) {
		bool result = false;
		std::lock_guard<std::mutex> lock{ *m_Mutex };
#if 0
		do {
			if (!pTaskNode)
				break;
			if (!pTaskNode->Verify())
				break;
			if (!m_pUIListDownTask)
				break;			
			auto theTaskNode = pTaskNode->UIDownTaskElementGet();
			if (!theTaskNode)
				theTaskNode = pTaskNode->UIDownTaskElementCreate();
			if (!theTaskNode)
				break;
			theTaskNode->SetTagUINT64(pTaskNode->ID());
			if (!m_pUIListDownTask->Add(theTaskNode))
				break;
			result = true;
		} while (0);
#endif
		return result;
	}
}///namespace local
