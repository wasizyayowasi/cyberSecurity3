#pragma once
#include "SceneBase.h"

class GameEnd : public SceneBase
{
public:
	GameEnd(SceneManager& manager);
	~GameEnd() {}

	void update(const InputState& input);
	void draw();

private:
	int gameoverH_ = -1;// �^�C�g���摜
	static constexpr int fade_interval = 60;
	int fadeTimer_ = fade_interval;
	int fadeValue_ = 255;

	unsigned int FadeColor = 0x000000;//�t�F�[�h�F��

	void fadeInUpdate(const InputState& input);
	void normalUpdate(const InputState& input);
	void fadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void (GameEnd::*)(const InputState&);
	UpdateFunc_t updateFunc_;

};

