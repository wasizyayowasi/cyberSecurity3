#include "ReferenceRoom.h"
#include "DxLib.h"
#include "DrawFunctions.h"
#include "Pad.h"

namespace {
	constexpr int pw_width = 124;				//ポーズ枠の幅
	constexpr int pw_height = 110;				//ポーズ枠の高さ
	constexpr int pw_start_x = 644;				//ポーズ枠に左
	constexpr int pw_start_y = 498;				//ポーズ枠上
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
	//画面の外枠
	{
		SetDrawBlendMode(DX_BLENDMODE_MULA, 50);//乗算合成
		//ポーズウィンドウセロファン(黒い)
		DrawBox(pw_width, pw_height, pw_start_x, pw_start_y, 0x000000, true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//通常描画に戻す

		DrawBox(pw_width, pw_height, pw_start_x, pw_start_y, 0xffffff, false);
	}

	DrawGraph(144, 130, m_hBook, true);
}
