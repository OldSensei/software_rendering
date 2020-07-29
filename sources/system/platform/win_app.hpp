#pragma once
#include <Windows.h>
#include <memory>
#include <string_view>
#include <chrono>

#include "../base/base_app.hpp"
#include "../platform/view_port.hpp"
#include "../time_utils.hpp"

namespace SFWR::Sytem
{
	class WinBaseApp : public IBaseApp
	{
	public:
		WinBaseApp(HINSTANCE instance, std::string_view utf8CmdLine, std::uint32_t width, std::uint32_t height);
		LRESULT handleMessage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

		bool isExit() const { return m_isExit; };

		int run() override;
		virtual void update( Utils::FloatSeconds delta ) = 0;
		virtual void render() = 0;

	private:
		HWND m_hwnd;
		bool m_isExit;

	protected:
		std::unique_ptr<ViewPort> m_viewPort;
	};

} //SFWR::Sytem
