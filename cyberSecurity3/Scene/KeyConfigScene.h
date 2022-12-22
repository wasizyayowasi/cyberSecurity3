#pragma once
#include "SceneBase.h"

class InputState;
class SceneManager;

/// <summary>
/// �L�[�R���t�B�O�V�[��
/// </summary>
class KeyConfigScene : public SceneBase
{
public:
	KeyConfigScene(SceneManager& manager, const InputState& input);

	void Update(const InputState& input);
	void Draw();
private:
	int currentInputIndex_;//���ݑI�𒆂̃C���f�b�N�X
	bool isEditing = false;//���ݓ���̓��͕͂ҏW���ł��B

	
	static constexpr int fade_interval = 60;
	int fadeTimer_ = fade_interval;
	int fadeValue_ = 255;

	unsigned int FadeColor = 0x000000;//�t�F�[�h�F��
	

	void fadeInUpdate(const InputState& input);
	void normalUpdate(const InputState& input);
	void fadeOutUpdate(const InputState& input);

	using updateFunc_t = void (KeyConfigScene::*)(const InputState& input);
	updateFunc_t updateFunc_ = nullptr;

	const InputState& inputState_;
};

