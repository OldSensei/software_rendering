#include <cassert>
#include "view_port.hpp"

namespace SFWR::System
{
	ViewPort::ViewPort(HWND hwnd, const RECT& wndRect) :
		m_hwnd(hwnd),
		m_hdc(::GetDC(hwnd)),
		m_width(wndRect.right - wndRect.left),
		m_height(wndRect.bottom - wndRect.top)
	{
		if (!m_hdc)
		{
			throw std::exception("Unable get hdc");
		}
	}

	ViewPort::~ViewPort()
	{
		if (m_hdc)
		{
			::ReleaseDC(m_hwnd, m_hdc);
		}
	}

	void ViewPort::present(const std::byte* const bitmap)
	{
		assert(m_hdc);

		static BITMAPINFO info;
		ZeroMemory(&info, sizeof(info));

		info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		info.bmiHeader.biWidth = m_width;
		info.bmiHeader.biHeight = m_height;
		info.bmiHeader.biPlanes = 1;
		info.bmiHeader.biBitCount = 32;
		info.bmiHeader.biCompression = BI_RGB;
		info.bmiHeader.biSizeImage = 0;

		::SetDIBitsToDevice(m_hdc,
			0, 0,
			m_width, m_height,
			0, 0,
			0, m_height,
			bitmap,
			&info,
			DIB_RGB_COLORS
			);
	}

} // namespace SFWR::Sytem