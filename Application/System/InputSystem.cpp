

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include<Windows.h>

#include "InputSystem.h"

bool App::InputDevice::get_async_key(int key) const
{
	return (GetAsyncKeyState(key) & 0x8000) != 0;
}

int App::InputDevice::convert_key(InputKeyBoard key)
{

	//	数値
	if (
		key >= InputKeyBoard::Zero &&
		key < InputKeyBoard::A
		)
	{
		const int num = '0';
		return num + (int)key;
	}
	else if (
		key >= InputKeyBoard::A &&
		key < InputKeyBoard::F1
		)
	{
		const int alpha = 'A';
		return alpha + (int)key - (int)InputKeyBoard::A;
	}
	else if (
		key >= InputKeyBoard::F1 &&
		key < InputKeyBoard::Space
		)
	{
		const int f1 = VK_F1;
		return f1 + (int)key - (int)InputKeyBoard::F1;
	}

	switch (key)
	{
	case App::InputKeyBoard::Space:
		return VK_SPACE;
	case App::InputKeyBoard::Enter:
		return VK_EXECUTE;
	case App::InputKeyBoard::Esc:
		return VK_ESCAPE;
	case App::InputKeyBoard::Shift:
		return VK_SHIFT;
	case App::InputKeyBoard::Contrl:
		return VK_CONTROL;
	case App::InputKeyBoard::Tab:
		return VK_TAB;
	case App::InputKeyBoard::UpArrow:
		return VK_UP;
	case App::InputKeyBoard::DownArrow:
		return VK_DOWN;
	case App::InputKeyBoard::LeftArrow:
		return VK_LEFT;
	case App::InputKeyBoard::RightArrow:
		return VK_RIGHT;
	default:
		return 0;
	}
}

int App::InputDevice::convert_key(InputMouse key)
{
	switch (key)
	{
	case InputMouse::Left:
		return VK_LBUTTON;

	case InputMouse::Right:
		return VK_RBUTTON;
	}

	return 0;
}
