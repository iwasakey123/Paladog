#include "pch.h"
#include "Window.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE prevINSTANCe, LPSTR lpszCmdParam, int nCmdShow)
{
	Window::Create(hInstance, 500, 500);
	Window::Show();

	while (Window::Update())
	{
		//깃허브 테스트
	}

	Window::Destroy();
	return 0;
}