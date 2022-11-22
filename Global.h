#if !defined(INC_H___4A6B3036_6348_477A_960D_AFAB295FE18F__HEAD__)
#define INC_H___4A6B3036_6348_477A_960D_AFAB295FE18F__HEAD__

namespace local {

	class Global final {
	public:
		Global();
		~Global();
	public:
		bool Init();
	private:
		void UnInit();
	public:
		static UIFrameWork* UIFrameWorkGet();
	private:
		std::atomic_bool m_Ready = false;
		UIFrameWork* m_pUIFrameWork = nullptr;
	};

	
	extern const std::map<EnUIType, std::wstring> __mapMainWindowClassName;
	extern const std::map<EnUIChildType, std::wstring> __mapChildWindowClassName;

	extern Global* __gpGlobal;
	extern Global* GlobalGet();
	extern HINSTANCE __gpHinstance;
}///namespace local

/// /*新生®（上海）**/
/// /*2022_09_21T01:22:05.6053548Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___4A6B3036_6348_477A_960D_AFAB295FE18F__HEAD__



