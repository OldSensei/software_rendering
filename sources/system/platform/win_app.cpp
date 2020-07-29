#include "win_app.hpp"

namespace SFWR::Sytem
{
	namespace
	{
		LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
		{
			if ( msg == WM_CREATE )
			{
				LPCREATESTRUCT cs = reinterpret_cast<LPCREATESTRUCT>(lp);
				WinBaseApp* app = reinterpret_cast<WinBaseApp*>(cs->lpCreateParams);
				SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(app));
			}
			else
			{
				auto app = reinterpret_cast<WinBaseApp*>(::GetWindowLongPtr(hwnd, GWLP_USERDATA));
				if (app)
				{
					return app->handleMessage(hwnd, msg, wp, lp);
				}
			}
			return DefWindowProc(hwnd, msg, wp, lp);
		}
	}

	WinBaseApp::WinBaseApp(HINSTANCE instance, std::string_view utf8CmdLine, std::uint32_t width, std::uint32_t height) :
		m_viewPort(nullptr),
		m_isExit(false)
	{
		constexpr const  wchar_t* wndClsName = L"SFWR.window";

		WNDCLASSEX wndclass;
		ZeroMemory(&wndclass, sizeof(WNDCLASSEX));

		wndclass.cbSize = sizeof(WNDCLASSEX);
		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc = windowProc;
		wndclass.lpszClassName = wndClsName;
		wndclass.hInstance = instance;
		wndclass.hbrBackground = static_cast<HBRUSH>( ::GetStockObject(BLACK_BRUSH) );
		wndclass.hCursor = static_cast<HCURSOR>( ::LoadCursor(0, IDC_ARROW) );
		wndclass.hIcon = 0;
		wndclass.hIconSm = 0;
		wndclass.lpszMenuName = nullptr;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;

		::RegisterClassEx(&wndclass);

		::RECT viewportRect{ 0L, 0L, static_cast<LONG>(width), static_cast<LONG>(height) };
		::RECT windowsRect{ viewportRect };
		::AdjustWindowRect( &windowsRect, WS_OVERLAPPEDWINDOW, false );

		m_hwnd = ::CreateWindowEx(
			0,
			wndClsName,
			L"SFWR::Window",
			WS_OVERLAPPEDWINDOW,
			10, 10,
			windowsRect.right - windowsRect.left, windowsRect.bottom - windowsRect.top,
			nullptr,
			nullptr,
			instance,
			this
		);

		if (!m_hwnd)
		{
			::UnregisterClass( wndClsName, instance );
		}

		m_viewPort = std::make_unique<ViewPort>(m_hwnd, viewportRect);
	}

	LRESULT WinBaseApp::handleMessage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
			case WM_DESTROY:
			{
				m_isExit = true;
				PostQuitMessage(0);
				return 0;
			}

			default:
				return DefWindowProc(hwnd, msg, wp, lp);
		}
	}

	int WinBaseApp::run()
	{
		::ShowWindow(m_hwnd, SW_SHOWDEFAULT);

		MSG msg = {};

		constexpr SFWR::Sytem::Utils::FloatSeconds delta{0.016};
		std::uint64_t time;
		char message[255] = {0};

		while (!isExit())
		{
			if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			else
			{
				{
					SFWR::Sytem::Utils::ScopedTimer t{ time };
					update(delta);
					render();
				}
				float msTime = time / 1000000.f;
				snprintf(message, 255, "update + render: %.4f\n", msTime);
				OutputDebugStringA(message);
			}
		}

		return 0;
	}
} // namespace SFWR::Sytem
