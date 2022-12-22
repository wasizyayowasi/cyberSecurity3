#pragma once
#include "SceneBase.h"

class InputState;
class SceneManager;

/// <summary>
/// キーコンフィグシーン
/// </summary>
class KeyConfigScene : public SceneBase
{
public:
	KeyConfigScene(SceneManager& manager, const InputState& input);

	void Update(const InputState& input);
	void Draw();
private:
	int currentInputIndex_;//現在選択中のインデックス
	bool isEditing = false;//現在特定の入力は編集中です。

	
	static constexpr int fade_interval = 60;
	int fadeTimer_ = fade_interval;
	int fadeValue_ = 255;

	unsigned int FadeColor = 0x000000;//フェード色黒
	

	void fadeInUpdate(const InputState& input);
	void normalUpdate(const InputState& input);
	void fadeOutUpdate(const InputState& input);

	using updateFunc_t = void (KeyConfigScene::*)(const InputState& input);
	updateFunc_t updateFunc_ = nullptr;

	const InputState& inputState_;
};

