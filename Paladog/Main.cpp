#include "pch.h"
#include "Window.h"
#include "Game.h"

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevInstance, _In_ LPSTR lpszCmdParam, _In_ int nCmdShow)
{
	Window::Create(hInstance, 800, 600);
	Window::Show();

	Game game = {};
	game.Init(Window::g_hWnd);

	uint64 prevTick = 0;

	while (Window::Update())
	{
		uint64 now = ::GetTickCount64();

		if (now - prevTick >= 10)
		{
			game.Update();
			game.Render();

			prevTick = now;
		}
	}

	Window::Destroy();
	return 0;
}