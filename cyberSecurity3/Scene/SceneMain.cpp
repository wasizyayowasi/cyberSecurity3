//シーン
#include "SceneMain.h"
#include "SceneTitle.h"
#include "ScenePause.h"
#include "../Field/FieldMain.h"
#include "GameEnd.h"

//ツール
#include "SceneManager.h"
#include "../InputState.h"
#include "../DrawFunctions.h"
#include "../game.h"
//脳みそ
#include <DxLib.h>

void SceneMain::fadeInUpdate(const InputState& input)
{
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	if (--fadeTimer_ == 0) {
		updateFunc_ = &SceneMain::normalUpdate;
		fadeValue_ = 0;
	}
}

void SceneMain::normalUpdate(const InputState& input)
{
	
	m_fieldMain.changeField();
	m_fieldMain.update();

	
	/*if (input.isTriggered(InputType::next))
	{
		updateFunc_ = &SceneMain::fadeOutUpdate;
		FadeColor = 0xffff00;
	}*/
	if (input.isTriggered(InputType::pause)) {
		manager_.pushScene(new ScenePause(manager_));
	}
}

void SceneMain::fadeOutUpdate(const InputState& input)
{
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	if (++fadeTimer_ == fade_interval) {
		manager_.changeScene(new GameEnd(manager_));
		return;
	}
}

SceneMain::SceneMain(SceneManager& manager) : SceneBase(manager), updateFunc_(&SceneMain::fadeInUpdate)
{
	m_fieldMain.mainFieldLoad();
}

SceneMain::~SceneMain() {
	
}

void SceneMain::update(const InputState& input)
{
	(this->*updateFunc_)(input);

}

void SceneMain::draw()
{
	m_fieldMain.draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, FadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}