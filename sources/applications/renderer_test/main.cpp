#include <Windows.h>
#include <string>
#include "system/platform/auxiliary/string_conversion.hpp"
#include "test_app.hpp"

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, PWSTR cmdLine, int cmdShow)
{
	std::string utf8CmdLine = SFWR::Sytem::Utils::to_utf8(cmdLine);

	TestApp app{ instance, utf8CmdLine, 800, 600 };
	return app.run();
}