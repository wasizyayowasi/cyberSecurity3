#include "ScenePause.h"
#include "SceneManager.h"
#include "../InputState.h"
#include "DxLib.h"

ScenePause::ScenePause(SceneManager& manager) :SceneBase(manager) {

}

ScenePause::~ScenePause()
{
}

void ScenePause::update(const InputState& input)
{
	if (input.isTriggered(InputType::pause)) {
		manager_.popScene();
		return;
	}
}

void ScenePause::draw()
{


	constexpr int pw_width = 400;
	constexpr int pw_height = 300;
	constexpr int pw_start_x = (640 - pw_width) / 2;
	constexpr int pw_start_y = (480 - pw_height) / 2;

	SetDrawBlendMode(DX_BLENDMODE_MULA, 128);
	//ポーズウィンドウセロファン(黒い)
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0x000000, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//ポーズウィンドウ枠線
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0xffffff, false);
}