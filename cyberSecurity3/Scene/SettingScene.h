#pragma once
#include "SceneBase.h"

class SettingScene : public SceneBase
{
public:
	SettingScene(SceneManager& manager);
	~SettingScene();

	void update(const InputState& input);
	void draw();
private:

	static constexpr int fade_interval = 60;
	int fadeTimer_ = fade_interval;
	int fadeValue_ = 255;

	unsigned int FadeColor = 0x000000;//フェード色黒

	void fadeInUpdate(const InputState& input);
	void normalUpdate(const InputState& input);
	void fadeOutUpdate(const InputState& input);

	using updateFunc_t = void (SettingScene::*)(const InputState& input);
	updateFunc_t updateFunc_ = nullptr;

};

