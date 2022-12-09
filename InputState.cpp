#include "InputState.h"
#include <DxLib.h>

void InputState::update()
{
	// 目のフレームのキー状況をコピー
	for (int i = 0; i < _countof(lastKeystate); ++i)
	{
		lastKeystate[i] = keystate[i];
	}
	GetHitKeyStateAll(keystate);
}

bool InputState::isPressed(InputType type) const
{
	if (type == InputType::next)
	{
		return keystate[KEY_INPUT_RETURN];
	}
	return false;
}

bool InputState::isTriggered(InputType type) const
{
	if (type == InputType::next)
	{
		return !lastKeystate[KEY_INPUT_RETURN] &&
			keystate[KEY_INPUT_RETURN];
	}
	else if (type == InputType::pause) {
		return !lastKeystate[KEY_INPUT_P] &&
			keystate[KEY_INPUT_P];
	}
	return false;
}