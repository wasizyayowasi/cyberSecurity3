#pragma once
#include "SceneBase.h"
#include "../Field/FieldMain.h"
#include "../Object/Player.h"

class GameEnd : public SceneBase
{
public:
	GameEnd(SceneManager& manager);
	~GameEnd();

	void update(const InputState& input);
	void draw();

private:
	
	int kuriaH_ = -1;// タイトル画像
	static constexpr int fade_interval = 60;
	int fadeTimer_ = fade_interval;
	int fadeValue_ = 255;

	unsigned int FadeColor = 0x000000;//フェード色黒

	void fadeInUpdate(const InputState& input);
	void normalUpdate(const InputState& input);
	void fadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void (GameEnd::*)(const InputState&);
	UpdateFunc_t updateFunc_;

	FieldMain m_filed;
	Player m_player;
};

