#include "stdafx.h"

namespace local {

	Setup::Setup(const std::string& setup_xml_pathname) : m_SetupXmlPathname(setup_xml_pathname) {

	}

	Setup::~Setup() {

	}
	void Setup::Init() {
		do {
			if (!shared::Win::AccessA(m_SetupXmlPathname))
				break;



			m_Ready.store(true);
		} while (0);
	}
	void Setup::UnInit() {
		m_Ready.store(false);
	}
	const Setup::Server& Setup::ServerGet() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_Server;
	}

}///namespace local