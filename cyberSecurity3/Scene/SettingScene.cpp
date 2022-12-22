#include "SettingScene.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "../InputState.h"
#include "KeyConfigScene.h"
#include "DxLib.h"

SettingScene::SettingScene(SceneManager& manager) : SceneBase(manager), updateFunc_(&SettingScene::fadeInUpdate)
{
}

SettingScene::~SettingScene()
{
}

void SettingScene::update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void SettingScene::draw()
{
	{
		DrawString(0, 0, "ê›íËâÊñ ", GetColor(255, 255, 255));

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
		DrawBox(0, 0, 768, 608, FadeColor, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}

void SettingScene::fadeInUpdate(const InputState& input)
{
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	if (--fadeTimer_ == 0) {
		updateFunc_ = &SettingScene::normalUpdate;
		fadeValue_ = 0;
	}
}

void SettingScene::normalUpdate(const InputState& input)
{
	if (input.isTriggered(InputType::next))
	{
		updateFunc_ = &SettingScene::fadeOutUpdate;
		FadeColor = 0xffffff;
	}
}

void SettingScene::fadeOutUpdate(const InputState& input)
{
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	if (++fadeTimer_ == fade_interval) {
		manager_.changeScene(new SceneTitle(manager_));
		return;
	}
}
