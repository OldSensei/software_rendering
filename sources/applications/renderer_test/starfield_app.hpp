#pragma once

#include "../../system/platform/win_app.hpp"
#include "../../renderer/frame_buffer.hpp"

class StarFieldApp : public SFWR::System::WinBaseApp
{
public:
	StarFieldApp(HINSTANCE instance, std::string_view utf8CmdLine, std::uint32_t width, std::uint32_t height) :
		WinBaseApp(instance, utf8CmdLine, width, height),
		m_width{ width },
		m_height{ height },
		m_fb{ width, height, 32 }
	{};

	void update(SFWR::System::Utils::FloatSeconds delta) override;
	void render() override;

private:
	std::uint32_t m_width;
	std::uint32_t m_height;
	SFWR::Renderer::FrameBuffer m_fb;
};
