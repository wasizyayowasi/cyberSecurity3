#pragma once
#include "SceneBase.h"
#include "SelectMenu.h"

class InputState;

class SceneTitle : public SceneBase
{
public:
	SceneTitle(SceneManager& manager);
	~SceneTitle() {}

	void update(const InputState& input);
	void draw();
private:

	SelectMenu m_menu;

	static constexpr int fade_interval = 60;

	int num = 0;

	int titleH_ = -1;
	int fadeTimer_ = fade_interval;
	int fadeValue_ = 255;

	unsigned int FadeColor = 0x000000;

	
	void fadeInUpdate(const InputState& input);
	
	void normalUpdate(const InputState& input);
	
	void fadeOutUpdate(const InputState& input);

	void (SceneTitle::* updateFunc_)(const InputState& input);

};

