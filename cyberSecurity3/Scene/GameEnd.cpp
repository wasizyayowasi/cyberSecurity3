#include "GameEnd.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "../DrawFunctions.h"
#include "../InputState.h"
#include "DxLib.h"
#include "../game.h"


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
	
	kuriaH_ = My::MyLoadGraph("data/kuria.png");
}

GameEnd::~GameEnd()
{
	
	DeleteGraph(kuriaH_); 
}

void GameEnd::update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void GameEnd::draw()
{
	
	
	DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, 1.0f, 0.0f, kuriaH_, true);
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	DrawBox(0, 0, Game::kScreenWidth , Game::kScreenHeight, FadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}