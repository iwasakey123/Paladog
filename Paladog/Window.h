#pragma once

#include "pch.h"

namespace Window
{
	static HINSTANCE g_instance;
	static HWND g_handle;

	inline LRESULT CALLBACK WinProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(handle, message, wParam, lParam);
		}

		return 0;
	}

	inline void Create(HINSTANCE hInstance, const UINT& width, const UINT& height)
	{
		WNDCLASSEX wnd_class;
		wnd_class.cbClsExtra = 0;
		wnd_class.cbWndExtra = 0;
		wnd_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		wnd_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wnd_class.hIcon = LoadIcon(nullptr, IDI_ERROR);
		wnd_class.hIconSm = LoadIcon(nullptr, IDI_ERROR);
		wnd_class.hInstance = hInstance;
		wnd_class.lpfnWndProc = WinProc;
		wnd_class.lpszClassName = L"Paladog";
		wnd_class.lpszMenuName = nullptr;
		wnd_class.style = CS_HREDRAW | CS_VREDRAW;
		wnd_class.cbSize = sizeof(WNDCLASSEX);

		auto check = RegisterClassEx(&wnd_class);
		assert(check != 0);

		g_handle = CreateWindowExW(
			WS_EX_APPWINDOW,
			L"Paladog",
			L"Paladog",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			static_cast<int>(width),
			static_cast<int>(height),
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);
		assert(g_handle != nullptr);
	}

	inline void Show()
	{
		SetForegroundWindow(g_handle);
		SetFocus(g_handle);
		ShowCursor(TRUE);
		ShowWindow(g_handle, SW_NORMAL);
		UpdateWindow(g_handle);
	}

	inline const bool Update()
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return msg.message != WM_QUIT;
	}

	inline void Destroy()
	{
		DestroyWindow(g_handle);
		UnregisterClass(L"Paladog", g_instance);
	}

	inline const UINT GetWidth()
	{
		RECT rect;
		GetClientRect(g_handle, &rect);
		return static_cast<UINT>(rect.right - rect.left);
	}

	inline const UINT GetHeight()
	{
		RECT rect;
		GetClientRect(g_handle, &rect);
		return static_cast<UINT>(rect.bottom - rect.top);
	}
}