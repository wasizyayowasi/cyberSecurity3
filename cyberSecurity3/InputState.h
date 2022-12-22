#pragma once

#include <map>
#include <vector>
#include <string>

enum class InputType
{
	next,			/// ���֍s���{�^��
	prev,			/// �O�ɖ߂�{�^��
	pause,			/// �|�[�Y�{�^��
	keyconf,		/// �L�[�R���t�B�O
	change,			///�ύX
	up,				///��
	down,			///��
	max				///�ő���̓C���f�b�N�X
};

/// <summary>
/// ���͑��u�J�e�S��
/// </summary>
enum class InputCategory {
	keybd,		//�L�[�{�[�h
	pad,		//�Q�[���p�b�h
	mouse,		//�}�E�X
};

/// <summary>
/// ���͏��
/// </summary>
struct InputInfo {
	InputCategory cat;	//���͑��u�J�e�S��
	int id;				//����ID(KEY_INPUT_�`,PAD_INPUT_�`,MOUSE_INPUT_�`)
};

class KeyConfigScene;

/// <summary>
/// ���͏�Ԃ��Ǘ�����
/// </summary>
class InputState
{
	friend KeyConfigScene;//KeyConfigScene�ɂ����A���ׂĂ�������B
public:

	InputState();

	/// <summary>
	/// �������u�Ԃ�true�ɂȂ�
	/// </summary>
	/// <param name="type">InputType</param>
	/// <returns>�������u�ԂȂ�true,����ȊO�Ȃ�false</returns>
	bool isTriggered(InputType type) const;

	/// <summary>
	/// ������Ă���true�ɂȂ�
	/// </summary>
	/// <param name="type">InputType</param>
	/// <returns>������Ă���true, ������ĂȂ��Ȃ�false</returns>
	bool isPressed(InputType type) const;

	/// <summary>
	/// ���͏����X�V����
	/// (����)���t���[��Update���Ă΂Ȃ��Ɠ��͏�Ԃ�
	/// �X�V����܂���B
	/// </summary>
	void update();

	/// <summary>
	/// ���͏����X�V����
	/// </summary>
	/// <param name="type">�Q�[���̂�������͎��</param>
	/// <param name="cat">���̓J�e�S��(kyebd��)</param>
	/// <param name="id">���ۂ̓���</param>
	void rewriteInputInfo(InputType type, InputCategory cat, int id);

private:

	std::map<InputType, std::vector<InputInfo> > inputMapTable_;//���ۂ̓��͂ƃQ�[���{�^���̑Ή��e�[�u��

	//���̓^�C�v�Ƃ��̖��O�̑΂҃e�[�u��
	std::map<InputType, std::string> inputNameTable_;

	std::vector<bool> currentInput_;	//���݂̓��͏��(�����Ă��邩�����Ă��Ȃ���)
	std::vector<bool> lastInput_;		//���O�̓��͏��(���O�����Ă��邩�����Ă��Ȃ���)

	//int keypadState;			// �L�[�p�b�h���
	//int lastKeypadState;		// ���O�̃L�[�p�b�h���
	//char keystate[256];			// �L�[�{�[�h���
	//char lastKeystate[256];		// ���O�̃L�[�{�[�h���

};
