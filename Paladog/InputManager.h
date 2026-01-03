#pragma once

enum class EKeyType
{
	LeftMouse = VK_LBUTTON,
	RightMouse = VK_RBUTTON,

	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,
	SpaceBar = VK_SPACE,

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
};

enum class EKeyState
{
	None,
	Press,
	Down,
	Up,

	End
};

enum
{
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<int32>(EKeyState::End),
};

class InputManager
{
	DECLARE_SINGLE(InputManager);

public:
	void Init(HWND hwnd);
	void Update();

	// 누르고 있을 때
	bool GetButtonPress(EKeyType key) { return GetState(key) == EKeyState::Press; }
	 
	// 맨 처음 눌렀을 때
	bool GetButtonDown(EKeyType key) { return GetState(key) == EKeyState::Down; }
	
	// 맨 처음 눌렀다가 땔 때
	bool GetButtonUp(EKeyType key) { return GetState(key) == EKeyState::Up; }

	inline const POINT& GetMousePos() { return _mousePos; }

private:
	EKeyState GetState(EKeyType key) { return _states[static_cast<uint8>(key)]; }

private:
	HWND _hwnd = {};
	vector<EKeyState> _states;
	POINT _mousePos;
};

