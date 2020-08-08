#include <Windows.h>
#include <string>
#include "system/platform/auxiliary/string_conversion.hpp"
#include "starfield_app.hpp"
#include "solid_shape_app.hpp"

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, PWSTR cmdLine, int cmdShow)
{
	std::string utf8CmdLine = SFWR::System::Utils::to_utf8(cmdLine);

	//StarFieldApp app{ instance, utf8CmdLine, 800, 600 };
	SolidShapeApp app{ instance, utf8CmdLine, 800, 600 };
	return app.run();
}