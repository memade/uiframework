#include "stdafx.h"

namespace local {
	UIMessageBox::UIMessageBox(const UIType& uitype, const bool& init_show) : UIBase(uitype, init_show) {
		Init();
	}
	UIMessageBox::~UIMessageBox() {
		UnInit();
	}
	void UIMessageBox::Init() {
	}
	void UIMessageBox::UnInit() {
	}
	void UIMessageBox::OnFinalMessage(HWND hWnd) {
		/*delete this;*////Release can cause a crash
	}
	const HWND& UIMessageBox::Hwnd() const {
		return UIBase::m_hWnd;
	}
	bool UIMessageBox::IsOpen() const {
		return m_IsOpen.load();
	}
	void UIMessageBox::Create() {
		do {
			if (m_IsOpen.load())
				break;
			CPaintManagerUI::SetInstance(__gpHinstance);
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
			DWORD dwCreateStyle = UI_WNDSTYLE_FRAME;
			do {
				if (m_Show.load())
					break;
				if (!(dwCreateStyle & WS_VISIBLE))
					break;
				dwCreateStyle &= ~WS_VISIBLE;
			} while (0);
			UIBase::m_hWnd = UIFrame::Create(NULL, _TEXT("PCDown Configure®"), dwCreateStyle, 0L);
			if (!UIBase::m_hWnd)
				break;
			m_IsOpen.store(true);
			CenterWindow();
			CPaintManagerUI::MessageLoop();
		} while (0);
	}
	void UIMessageBox::Destory() {
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
	void UIMessageBox::InitWindow() {

#if 0
		m_Threads.emplace_back(
			[&]() {
			
				bool success = false;
				do {
					const auto& objects = Global::SetupGet()->Objects();
					do {//!@ 初始化主推软件信息
						auto pSoftName = GetCtrl<CLabelUI>(_T("5350E081"));
						if (pSoftName)
							pSoftName->SetText(shared::IConv::MBytesToWString(Global::SetupGet()->RecommendGet().Name).c_str());
						auto pSoftSize = GetCtrl<CLabelUI>(_T("E29020F5"));
						if (pSoftSize) {
							auto text = pSoftSize->GetText();
							pSoftSize->SetText(
								std::format(text.GetData(), shared::IConv::MBytesToWString(Global::SetupGet()->RecommendGet().Size)).c_str());
						}
						auto pSoftDownCount = GetCtrl<CLabelUI>(_T("4FB1106F"));
						if (pSoftDownCount) {
							std::uint64_t seed = time(0);
							seed = seed * 214013L + 2531011L;
							int nDownCount = 30000 + ((seed >> 16) % 99999);

							auto text = pSoftDownCount->GetText();
							pSoftDownCount->SetText(
								std::format(text.GetData(), std::to_wstring(nDownCount)).c_str());
						}
					} while (0);









					//!@ 初始化资源列表
					do {
						if (objects.empty())
							break;
						auto pResList = GetCtrl<CListUI>(_T("FD334C31"));
						if (!pResList)
							break;
						CDialogBuilder builder;
						for (const auto& object : objects) {
							do {
								auto pNote = builder.Create<CContainerUI>(_T("object.xml"));
								if (!pNote)
									break;
								auto name = pNote->GetSubCtrl<CLabelUI>(_T("30A91164"));
								if (name)
									name->SetText(shared::IConv::MBytesToWString(object.second.china).c_str());
								pResList->Add(pNote);
							} while (0);
						}
						success = true;
					} while (0);

					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					if (!m_IsOpen.load() || success)
						break;
				} while (1);
			
			

			});
#endif


	}


	LRESULT UIMessageBox::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		bHandled = FALSE;
		return 0;
	}
	LRESULT UIMessageBox::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		LONG styleValue = ::GetWindowLongW(*this, GWL_STYLE);
		styleValue &= ~WS_CAPTION;
		::SetWindowLongW(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

		LONG ExStyleValue = ::GetWindowLongW(*this, GWL_EXSTYLE);
		ExStyleValue |= WS_EX_TOOLWINDOW;
		::SetWindowLongW(*this, GWL_EXSTYLE, ExStyleValue);

		m_pm.Init(GetHWND());
		CDialogBuilder builder;
		CControlUI* pRoot = builder.Create(std::wstring(GetWindowClassName()).append(_TEXT(".xml")).c_str(), (LPCTSTR)0, NULL, &m_pm);
		ASSERT(pRoot && "Failed to parse 'ui.xml'");
		m_pm.AttachDialog(pRoot);
		m_pm.AddNotifier(this);
		bHandled = TRUE;
		return 0;
	}

	LRESULT UIMessageBox::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		bHandled = FALSE;
		return 0;
	}
	LRESULT UIMessageBox::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		bHandled = FALSE;
		return 0;
	}
	LRESULT UIMessageBox::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		bHandled = FALSE;
		return 0;
	}
	LRESULT UIMessageBox::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}

	LRESULT UIMessageBox::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		bHandled = FALSE;
		return 0;
	}
	CControlUI* UIMessageBox::CreateControl(LPCTSTR pstrClassName) {
		return nullptr;
	}











	void UIMessageBox::Notify(TNotifyUI& msg) {
		if (msg.sType == DUI_MSGTYPE_HEADERCLICK) {
		}///DUI_MSGTYPE_HEADERCLICK
		else if (msg.sType == DUI_MSGTYPE_LINK) {
			CTextUI* pText = (CTextUI*)msg.pSender;
			CDuiString* strUrl = pText->GetLinkContent(0);
			::ShellExecute(NULL, _T("open"), strUrl->GetData(), NULL, NULL, SW_SHOWNORMAL);
		}
		else if (msg.sType == DUI_MSGTYPE_CHECKCLICK) {

		}
		else if (msg.sType == DUI_MSGTYPE_CLICK) {
			const auto name = msg.pSender->GetName();
			if (!name.Compare(_T("0B3A1B17"))) {
				OnShowMininized();
			}
			else if (!name.Compare(_T("A3B405BB"))) {
				UIMessageBox::Close();
			}
		}
		else {

		}
	}
}///namespace local
