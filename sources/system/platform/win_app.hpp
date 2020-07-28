#pragma once
#include <Windows.h>
#include <memory>
#include <string_view>


#include "../base/base_app.hpp"
#include "../platform/view_port.hpp"

namespace SFWR::Sytem
{
	class WinBaseApp : public IBaseApp
	{
	public:
		WinBaseApp(HINSTANCE instance, std::string_view utf8CmdLine, std::uint32_t width, std::uint32_t height);
		LRESULT handleMessage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

		bool isExit() const { return m_isExit; };

		int run() override;
		virtual void update(float deltaTs) = 0;
		virtual void render() = 0;

	private:
		HWND m_hwnd;
		std::unique_ptr<ViewPort> viewPort;
		bool m_isExit;
	};

} //SFWR::Sytem
