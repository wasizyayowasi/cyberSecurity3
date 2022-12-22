#include "InputState.h"
#include <DxLib.h>

InputState::InputState()
{
	inputMapTable_[InputType::next] = { {InputCategory::keybd,KEY_INPUT_RETURN},
										{InputCategory::pad,PAD_INPUT_R},
										{InputCategory::mouse,MOUSE_INPUT_LEFT} };//�X�^�[�g�{�^��

	inputMapTable_[InputType::prev] = { {InputCategory::keybd,KEY_INPUT_SPACE },
										{InputCategory::pad,PAD_INPUT_B} };

	inputMapTable_[InputType::pause] = { {InputCategory::keybd,KEY_INPUT_P},
										 {InputCategory::pad,PAD_INPUT_L} };//�Z���N�g�{�^��

	inputMapTable_[InputType::keyconf] = { {InputCategory::keybd,KEY_INPUT_K},
										   {InputCategory::pad,PAD_INPUT_Y} };//���V�����_�[

	inputMapTable_[InputType::change] = { {InputCategory::keybd,KEY_INPUT_C},
										   {InputCategory::pad,PAD_INPUT_Z} };//�E�V�����_�[

	inputMapTable_[InputType::up] = { {InputCategory::keybd,KEY_INPUT_UP},
										   {InputCategory::pad,PAD_INPUT_UP} };//��
	inputMapTable_[InputType::down] = { {InputCategory::keybd,KEY_INPUT_DOWN},
										   {InputCategory::pad,PAD_INPUT_DOWN} };//��

	//���̓^�C�v�̖��O�̃e�[�u�������
	inputNameTable_[InputType::next] = "next";
	inputNameTable_[InputType::prev] = "prev";
	inputNameTable_[InputType::pause] = "pause";
	inputNameTable_[InputType::keyconf] = "keyconf";
	inputNameTable_[InputType::change] = "change";


	currentInput_.resize(static_cast<int>(InputType::max));
	lastInput_.resize(static_cast<int>(InputType::max));
}

void InputState::update()
{
	lastInput_ = currentInput_;//���O�̓��͏����L�����Ă���

	char keystate[256];
	GetHitKeyStateAll(keystate);//�S�L�[���擾

	int padState = GetJoypadInputState(DX_INPUT_PAD1);//�p�b�h1�R���̏����擾����
	int mouseState = GetMouseInput();

	for (const auto& keymap : inputMapTable_) {			//�}�b�v�̑S�������[�v����
		for (const auto& input : keymap.second) {		//���͏��z������[�v����
			//���̒��g�́Akeybd,KEY_INPUT_RETURN�Ȃǂ̃Z�b�g(InputInfo)�������Ă�
			//keymap.second�ɂ́A���̓��͏��Z�b�gInputInfo�������Ă���B
			//keymap.first�ɂ́A�Ή�����Q�[�����͖���"InputType"�Ȃǂ������Ă���
			if (input.cat == InputCategory::keybd) {
				currentInput_[static_cast<int>(keymap.first)] = keystate[input.id];
			}
			else if (input.cat == InputCategory::pad) {
				currentInput_[static_cast<int>(keymap.first)] = padState & input.id;
			}
			else if (input.cat == InputCategory::mouse) {
				currentInput_[static_cast<int>(keymap.first)] = mouseState & input.id;
			}
			if (currentInput_[static_cast<int>(keymap.first)]) {
				break;
			}
		}
	}


}

void InputState::rewriteInputInfo(InputType type, InputCategory cat, int id)
{
	//���͎��(���蓖�Đ�)���Ȃ���΁A�����Ȃ̂Ŗ������܂��B
	if (inputMapTable_.count(type) == 0) {
		return;
	}

	bool isRewrite = false;

	for (auto& InputInfo : inputMapTable_[type]) {
		if (InputInfo.cat == cat)//�J�e�S�����q�b�g������
		{
			InputInfo.id = id;//ID���㏑������
			isRewrite = true;
			break;
		}
	}
	if (!isRewrite) {//�����J�e�S�������݂��Ȃ�������A�����Œǉ����Ă���
		inputMapTable_[type].push_back({ cat,id });
	}
}

bool InputState::isPressed(InputType type) const
{
	return currentInput_[static_cast<int>(type)];
}

bool InputState::isTriggered(InputType type) const
{
	return isPressed(type) && !lastInput_[static_cast<int>(type)];
}