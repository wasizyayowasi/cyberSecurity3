#include "GameEnd.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "InputState.h"
#include "DxLib.h"


void GameEnd::fadeInUpdate(const InputState& input)
{
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	if (--fadeTimer_ == 0) {
		updateFunc_ = &GameEnd::normalUpdate;
		fadeValue_ = 0;
	}
}

void GameEnd::normalUpdate(const InputState& input)
{
	if (input.isTriggered(InputType::next))
	{
		updateFunc_ = &GameEnd::fadeOutUpdate;
		FadeColor = 0xff0000;
	}
}

void GameEnd::fadeOutUpdate(const InputState& input)
{
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	if (++fadeTimer_ == fade_interval) {
		manager_.changeScene(new SceneTitle(manager_));
		return;
	}
}

GameEnd::GameEnd(SceneManager& manager) : SceneBase(manager), updateFunc_(&GameEnd::fadeInUpdate)
{
	
}

void GameEnd::update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void GameEnd::draw()
{
	DrawRotaGraph(320, 240, 1.0f, 0.0f, gameoverH_, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	DrawBox(0, 0, 640, 480, FadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}