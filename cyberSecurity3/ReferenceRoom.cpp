#include "ReferenceRoom.h"
#include "DxLib.h"
#include "DrawFunctions.h"
#include "Pad.h"

namespace {
	constexpr int pw_width = 124;				//�|�[�Y�g�̕�
	constexpr int pw_height = 110;				//�|�[�Y�g�̍���
	constexpr int pw_start_x = 644;				//�|�[�Y�g�ɍ�
	constexpr int pw_start_y = 498;				//�|�[�Y�g��
}

ReferenceRoom::ReferenceRoom():
	m_hBook(-1)
{
	m_hBook = My::MyLoadGraph("data/hon1.png");
}

ReferenceRoom::~ReferenceRoom()
{
	DeleteGraph(m_hBook);
}

int ReferenceRoom::update()
{
	if (Pad::isPress(PAD_INPUT_2)) {
		return 2;
	}
	return 7;
}

void ReferenceRoom::draw()
{
	//��ʂ̊O�g
	{
		SetDrawBlendMode(DX_BLENDMODE_MULA, 50);//��Z����
		//�|�[�Y�E�B���h�E�Z���t�@��(����)
		DrawBox(pw_width, pw_height, pw_start_x, pw_start_y, 0x000000, true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//�ʏ�`��ɖ߂�

		DrawBox(pw_width, pw_height, pw_start_x, pw_start_y, 0xffffff, false);
	}

	DrawGraph(144, 130, m_hBook, true);
}
