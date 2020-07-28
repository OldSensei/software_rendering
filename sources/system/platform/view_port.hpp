#pragma once
#include <Windows.h>
#include <cstdint>
#include <string_view>

namespace SFWR::Sytem
{
	class ViewPort final
	{

	public:
		ViewPort(HWND hwnd, const RECT& wndRect);
		~ViewPort();
		void present(const std::byte* const bitmap);

	private:
		HWND m_hwnd;
		HDC m_hdc;
		std::int32_t m_width;
		std::int32_t m_height;
	};
} //namespace SFWR::Sytem
