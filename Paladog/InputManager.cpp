#include "pch.h"
#include "InputManager.h"

void InputManager::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_states.resize(KEY_TYPE_COUNT, EKeyState::None);
}

void InputManager::Update()
{
	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(asciiKeys) == false)
		return;

	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		// 키가 눌려 있으면 true
		if (asciiKeys[key] & 0x80)
		{
			EKeyState& state = _states[key];

			// 이전 프레임에 키를 누른 상태라면 PRESS
			if (state == EKeyState::Press || state == EKeyState::Down)
				state = EKeyState::Press;
			else
				state = EKeyState::Down;
		}
		else
		{
			EKeyState& state = _states[key];

			// 이전 프레임에 키를 누른 상태라면 PRESS
			if (state == EKeyState::Press || state == EKeyState::Down)
				state = EKeyState::Up;
			else
				state = EKeyState::None;
		}
	}

	//Mouse
	::GetCursorPos(&_mousePos); // 커서의 좌표를 알아온다
	::ScreenToClient(_hwnd, &_mousePos);
}