#pragma once

#include "pch.h"

namespace Window
{
	inline static HINSTANCE g_instance;
	inline static HWND g_hWnd;

	inline int mousePosX;
	inline int mousePosY;

	inline LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_CLOSE:
			::DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			::PostQuitMessage(0);
			break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = ::BeginPaint(hWnd, &ps);	
			//			
			::EndPaint(hWnd, &ps);
		}
		break;
		case WM_MOUSEMOVE:
		{
			mousePosX = LOWORD(lParam);
			mousePosY = HIWORD(lParam);
			//::InvalidateRect(hWnd, nullptr, FALSE);
		}
		break;
		default:
			return ::DefWindowProc(hWnd, message, wParam, lParam);
		}

		return 0;
	}

	inline void Create(HINSTANCE hInstance, const UINT& width, const UINT& height)
	{
		WNDCLASSEXW wnd_class = {};
		wnd_class.cbSize = sizeof(WNDCLASSEX);
		wnd_class.style = CS_HREDRAW | CS_VREDRAW;
		wnd_class.lpfnWndProc = WinProc;
		wnd_class.cbClsExtra = 0;
		wnd_class.cbWndExtra = 0;
		wnd_class.hInstance = hInstance;
		wnd_class.lpszMenuName = nullptr;
		//wnd_class.hCursor = (HCURSOR)LoadImageW(nullptr, L"customCorsor.cur", IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
		//if (!wnd_class.hCursor)
		wnd_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wnd_class.hIcon = LoadIcon(nullptr, IDI_ERROR);
		wnd_class.hIconSm = LoadIcon(nullptr, IDI_ERROR);
		wnd_class.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
		wnd_class.lpszClassName = L"Paladog";
		
		auto check = ::RegisterClassEx(&wnd_class);
		assert(check != 0);

		g_instance = hInstance;

		RECT windowRect = { 0, 0, width, height };
		::AdjustWindowRectEx(&windowRect, WS_OVERLAPPEDWINDOW, false, WS_EX_APPWINDOW);

		int windowW = windowRect.right - windowRect.left;
		int windowH = windowRect.bottom - windowRect.top;

		g_hWnd = ::CreateWindowExW(
			WS_EX_APPWINDOW,
			L"Paladog",
			L"Paladog",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			windowW,
			windowH,
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);
		assert(g_hWnd != nullptr);
	}

	inline void Show()
	{
		::SetForegroundWindow(g_hWnd); //이 창을 현재 활성 창으로
		::SetFocus(g_hWnd); //키보드 입력 받게
		::ShowCursor(TRUE); //커서 표시
		::ShowWindow(g_hWnd, SW_NORMAL); //창을 화면에 표시
		::UpdateWindow(g_hWnd); //즉시 한 번 그리기
	}

	inline const bool Update() 
	{
		MSG msg; 
		::ZeroMemory(&msg, sizeof(MSG)); 

		if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
		{
			::TranslateMessage(&msg); 
			::DispatchMessage(&msg); 
		}
		return msg.message != WM_QUIT; 
	}

	inline void Destroy()
	{
		::DestroyWindow(g_hWnd);
		::UnregisterClass(L"Paladog", g_instance);
	}

	inline const UINT GetWidth()
	{
		RECT rect;
		::GetClientRect(g_hWnd, &rect);
		return static_cast<UINT>(rect.right - rect.left);
	}

	inline const UINT GetHeight()
	{
		RECT rect;
		::GetClientRect(g_hWnd, &rect);
		return static_cast<UINT>(rect.bottom - rect.top);
	}
}