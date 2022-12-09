#pragma once
#include "SceneBase.h"
#include "FieldMain.h"

class SceneMain : public SceneBase
{
public:
	SceneMain(SceneManager& manager);
	~SceneMain();
	void update(const InputState& input);
	void draw();
private:

	int changeFieldNum = 0;

	

	static constexpr int fade_interval = 60;
	int fadeTimer_ = fade_interval;
	int fadeValue_ = 255;

	unsigned int FadeColor = 0x000000;//�t�F�[�h�F��

	void fadeInUpdate(const InputState& input);
	void normalUpdate(const InputState& input);
	void fadeOutUpdate(const InputState& input);

	using updateFunc_t = void (SceneMain::*)(const InputState& input);
	updateFunc_t updateFunc_ = nullptr;

	FieldMain m_fieldMain;
};
