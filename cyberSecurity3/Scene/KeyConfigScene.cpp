#include "KeyConfigScene.h"
#include "../InputState.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include  <DxLib.h>

KeyConfigScene::KeyConfigScene(SceneManager& manager, const InputState& input) :inputState_(input), SceneBase(manager), currentInputIndex_(0)
{

}

void KeyConfigScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void KeyConfigScene::Draw()
{
	constexpr int pw_width = 450;							//キーコンフィグ枠の幅
	constexpr int pw_height = 350;							//キーコンフィグ枠の高さ
	constexpr int pw_start_x = (640 - pw_width) / 2 + 50;	//キーコンフィグ枠に左
	constexpr int pw_start_y = (480 - pw_height) / 2 + 50;	//キーコンフィグ枠上

	//キーコンフィグウィンドウセロファン(黒い)
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0x008800, true);

	//キーコンフィグメッセージ
	DrawString(pw_start_x + 10, pw_start_y + 10, "KeyConfig...", 0xffffaa);



	auto y = pw_start_y + 30;
	int idx = 0;
	for (const auto& name : inputState_.inputNameTable_) {
		int offset = 0;
		unsigned int color = 0xffffff;
		if (currentInputIndex_ == idx) {
			offset = 10;
			if (isEditing) {
				color = 0xff0000;
			}
		}
		//各キーの表示
		int x = pw_start_x + 20 + offset;
		DrawString(x, y, name.second.c_str(), color);

		auto type = name.first;
		auto it = inputState_.inputMapTable_.find(type);

		x += 64;
		DrawString(x, y, " : ", color);
		x += 20;
		for (const auto elem : it->second) {

			if (elem.cat == InputCategory::keybd) {
				DrawFormatString(x, y, color, "key = %d", elem.id);
			}
			else if (elem.cat == InputCategory::pad) {
				DrawFormatString(x, y, color, "pad = %d", elem.id);
			}
			else if (elem.cat == InputCategory::mouse) {
				DrawFormatString(x, y, color, "mse = %d", elem.id);
			}
			x += 100;
		}
		y += 18;
		++idx;
	}

	y += 20;
	//各キーの表示
	DrawString(pw_start_x + 100, y, " 確定します ", 0xffffff);

	//キーコンフィグウィンドウ枠線
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0xffffff, false);
}

void KeyConfigScene::fadeInUpdate(const InputState& input)
{
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	if (--fadeTimer_ == 0) {
		updateFunc_ = &KeyConfigScene::normalUpdate;
		fadeValue_ = 0;
	}
}

void KeyConfigScene::normalUpdate(const InputState& input)
{

	auto& configInput = const_cast<InputState&>(input);

	if (!isEditing) {
		if (input.isTriggered(InputType::keyconf)) {
			manager_.popScene();
			return;
		}
		if (input.isTriggered(InputType::change)) {

			configInput.rewriteInputInfo(InputType::prev, InputCategory::keybd, KEY_INPUT_ESCAPE);
			configInput.rewriteInputInfo(InputType::prev, InputCategory::pad, PAD_INPUT_A);
			configInput.rewriteInputInfo(InputType::prev, InputCategory::mouse, MOUSE_INPUT_RIGHT);

			static int count = 0;
			++count;
			char logstr[64] = {};
			sprintf_s(logstr, sizeof(logstr), "%d回キーが書き換えられました。\n", count);
			OutputDebugStringA(logstr);

		}

		const int nameCount = input.inputNameTable_.size();

		if (input.isTriggered(InputType::up)) {
			currentInputIndex_ = ((currentInputIndex_ - 1) + nameCount) % nameCount;
		}
		else if (input.isTriggered(InputType::down)) {
			currentInputIndex_ = (currentInputIndex_ + 1) % nameCount;
		}
	}

	if (input.isTriggered(InputType::next)) {
		isEditing = !isEditing;
		return;
	}

	if (isEditing) {
		char keystate[256];
		GetHitKeyStateAll(keystate);
		auto padState = GetJoypadInputState(DX_INPUT_PAD1);
		auto mouseState = GetMouseInput();

		int idx = 0;
		InputType currentType = InputType::max;
		for (const auto& name : inputState_.inputNameTable_) {
			if (currentInputIndex_ == idx) {
				currentType = name.first;
				break;
			}
			++idx;
		}

		for (int i = 0; i < 256; i++) {
			if (keystate[i]) {
				configInput.rewriteInputInfo(currentType, InputCategory::keybd, i);

			}
		}
		if (padState != 0) {
			configInput.rewriteInputInfo(currentType, InputCategory::pad, padState);
		}
		if (mouseState != 0) {
			configInput.rewriteInputInfo(currentType, InputCategory::mouse, mouseState);
		}
	}


	if (input.isTriggered(InputType::next))
	{
		updateFunc_ = &KeyConfigScene::fadeOutUpdate;
		FadeColor = 0xffffff;
	}
}

void KeyConfigScene::fadeOutUpdate(const InputState& input)
{
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	if (++fadeTimer_ == fade_interval) {
		manager_.changeScene(new SceneTitle(manager_));
		return;
	}
}

