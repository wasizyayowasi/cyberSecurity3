#include "SceneTitle.h"
#include "SceneManager.h"
#include "SceneMain.h"
#include "SettingScene.h"
#include "KeyConfigScene.h"
#include "../InputState.h"
#include <DxLib.h>

void SceneTitle::fadeInUpdate(const InputState& input) {
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	if (--fadeTimer_ == 0) {
		updateFunc_ = &SceneTitle::normalUpdate;
		fadeValue_ = 0;
	}
}

void SceneTitle::normalUpdate(const InputState& input) {
	
	Pad::update();
	num = m_menu.update();

	if (input.isTriggered(InputType::next) && num == 0)
	{
		updateFunc_ = &SceneTitle::fadeOutUpdate;
		FadeColor = 0x0000ff;
	}
	if (input.isTriggered(InputType::next) && num == 1)
	{
		updateFunc_ = &SceneTitle::fadeOutUpdate;
		FadeColor = 0x0000ff;
	}
}

void SceneTitle::fadeOutUpdate(const InputState& input) {
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	switch (num) {
	case 0:
		if (++fadeTimer_ == fade_interval) {
			manager_.changeScene(new SceneMain(manager_));
			return;
		}
		break;
	case 1:
		if (++fadeTimer_ == fade_interval) {
			manager_.changeScene(new SettingScene(manager_));
			return;
		}
		break;
	case 2:
		DxLib_End();
		break;
	}
}

SceneTitle::SceneTitle(SceneManager& manager) : SceneBase(manager), updateFunc_(&SceneTitle::fadeInUpdate)
{
	m_menu.init();
	//CreateFontToHandle(char* FontName, int Size, int Thick, int FontType);
	m_menu.addItem("起動");
	m_menu.addItem("設定");
	m_menu.addItem("終了");
	//m_menu.addItem("デバッグ");

	m_menu.setPos(600, 320);

	m_menu.setUpCursor();
}


void SceneTitle::update(const InputState& input)
{
	(this->*updateFunc_)(input);

}

void SceneTitle::draw()
{

	m_menu.draw();

	//普通の描画
	DrawRotaGraph(320, 240, 1.0f, 0.0f, titleH_, true);

	//今から描く画像と、すでに描画されてるスクリーンとの
	//ブレンドの仕方を指定している。
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	//画面全体を真っ黒に塗りつぶす
	DrawBox(0, 0, 768, 608, FadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}