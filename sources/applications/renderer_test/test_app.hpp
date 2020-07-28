#pragma once

#include "../../system/platform/win_app.hpp"

class TestApp : public SFWR::Sytem::WinBaseApp
{
public:
	TestApp(HINSTANCE instance, std::string_view utf8CmdLine, std::uint32_t width, std::uint32_t height) : WinBaseApp(instance, utf8CmdLine, width, height)
	{};

	void update(float deltaTs) override;
	void render() override;
};
