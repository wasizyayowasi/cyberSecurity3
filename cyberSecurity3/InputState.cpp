#include "InputState.h"
#include <DxLib.h>

InputState::InputState()
{
	inputMapTable_[InputType::next] = { {InputCategory::keybd,KEY_INPUT_RETURN},
										{InputCategory::pad,PAD_INPUT_R},
										{InputCategory::mouse,MOUSE_INPUT_LEFT} };//スタートボタン

	inputMapTable_[InputType::prev] = { {InputCategory::keybd,KEY_INPUT_SPACE },
										{InputCategory::pad,PAD_INPUT_B} };

	inputMapTable_[InputType::pause] = { {InputCategory::keybd,KEY_INPUT_P},
										 {InputCategory::pad,PAD_INPUT_L} };//セレクトボタン

	inputMapTable_[InputType::keyconf] = { {InputCategory::keybd,KEY_INPUT_K},
										   {InputCategory::pad,PAD_INPUT_Y} };//左ショルダー

	inputMapTable_[InputType::change] = { {InputCategory::keybd,KEY_INPUT_C},
										   {InputCategory::pad,PAD_INPUT_Z} };//右ショルダー

	inputMapTable_[InputType::up] = { {InputCategory::keybd,KEY_INPUT_UP},
										   {InputCategory::pad,PAD_INPUT_UP} };//上
	inputMapTable_[InputType::down] = { {InputCategory::keybd,KEY_INPUT_DOWN},
										   {InputCategory::pad,PAD_INPUT_DOWN} };//下

	//入力タイプの名前のテーブルを作る
	inputNameTable_[InputType::next] = "next";
	inputNameTable_[InputType::prev] = "prev";
	inputNameTable_[InputType::pause] = "pause";
	inputNameTable_[InputType::keyconf] = "keyconf";
	inputNameTable_[InputType::change] = "change";


	currentInput_.resize(static_cast<int>(InputType::max));
	lastInput_.resize(static_cast<int>(InputType::max));
}

void InputState::update()
{
	lastInput_ = currentInput_;//直前の入力情報を記憶しておく

	char keystate[256];
	GetHitKeyStateAll(keystate);//全キー情報取得

	int padState = GetJoypadInputState(DX_INPUT_PAD1);//パッド1コンの情報を取得する
	int mouseState = GetMouseInput();

	for (const auto& keymap : inputMapTable_) {			//マップの全情報をループする
		for (const auto& input : keymap.second) {		//入力情報配列をループする
			//この中身は、keybd,KEY_INPUT_RETURNなどのセット(InputInfo)が入ってる
			//keymap.secondには、この入力情報セットInputInfoが入っている。
			//keymap.firstには、対応するゲーム入力名の"InputType"などが入っている
			if (input.cat == InputCategory::keybd) {
				currentInput_[static_cast<int>(keymap.first)] = keystate[input.id];
			}
			else if (input.cat == InputCategory::pad) {
				currentInput_[static_cast<int>(keymap.first)] = padState & input.id;
			}
			else if (input.cat == InputCategory::mouse) {
				currentInput_[static_cast<int>(keymap.first)] = mouseState & input.id;
			}
			if (currentInput_[static_cast<int>(keymap.first)]) {
				break;
			}
		}
	}


}

void InputState::rewriteInputInfo(InputType type, InputCategory cat, int id)
{
	//入力種別(割り当て先)がなければ、無効なので無視します。
	if (inputMapTable_.count(type) == 0) {
		return;
	}

	bool isRewrite = false;

	for (auto& InputInfo : inputMapTable_[type]) {
		if (InputInfo.cat == cat)//カテゴリがヒットしたら
		{
			InputInfo.id = id;//IDを上書きする
			isRewrite = true;
			break;
		}
	}
	if (!isRewrite) {//もしカテゴリが存在しなかったら、ここで追加しておく
		inputMapTable_[type].push_back({ cat,id });
	}
}

bool InputState::isPressed(InputType type) const
{
	return currentInput_[static_cast<int>(type)];
}

bool InputState::isTriggered(InputType type) const
{
	return isPressed(type) && !lastInput_[static_cast<int>(type)];
}