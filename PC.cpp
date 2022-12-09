#include "PC.h"

#include "DrawFunctions.h"
#include "Pad.h"

#include "DxLib.h"

namespace {
	const int max = 10;

	constexpr int pw_width = 124;				//ポーズ枠の幅
	constexpr int pw_height = 110;				//ポーズ枠の高さ
	constexpr int pw_start_x = 644;				//ポーズ枠に左
	constexpr int pw_start_y = 498;				//ポーズ枠上

	int color = GetColor(255, 255, 255);
}

PC::PC() :
	m_hWindows(-1),
	m_hWindowzzz(-1),
	m_hGoogle(-1),
	m_hGlegle(-1),
	changeMonitorNum(4),
	monitorLv(0),
	mouseX(0),
	mouseY(0),
	flashingTimer(0),
	flashingCount(0),
	searchBarClick(false)
{
	m_hWindows = My::MyLoadGraph("data/Windows.png");
	m_hWindowzzz = My::MyLoadGraph("data/Windowzzz.png");
	m_hGoogle = My::MyLoadGraph("data/google.png");
	m_hGlegle = My::MyLoadGraph("data/glegle.png");
	
}

PC::~PC()
{
	DeleteGraph(m_hGoogle);
	DeleteGraph(m_hGlegle);
	DeleteGraph(m_hWindows);
	DeleteGraph(m_hWindowzzz);
}

void PC::drawManager()
{
	switch (monitorLv) {
	case 0:
		windowsAcountDraw();
		DrawFormatString(170, 180, GetColor(0, 0, 0), "%d", changeMonitorNum);
		break;
	case 1:
		searchEngineDraw();
		DrawFormatString(170, 180, GetColor(0, 0, 0), "%d", changeMonitorNum);
		break;
	}
}

int PC::update()
{

	//マウス
	GetMousePoint(&mouseX, &mouseY);

	m_pos.x = mouseX;
	m_pos.y = mouseY;

	switch (monitorLv) {
	case 0:

		if (Pad::isPress(PAD_INPUT_3)) {
			monitorLv = 1;
		}

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			if (StandbySymbolCollision()) {
				return 1;
			}
		}
		break;
	case 1:

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			if (closeCollision()) {
				return 1;
			}
		}
		break;
	}
	
	
	

	if (Pad::isPress(PAD_INPUT_2)) {
		return 1;
	}
	return 6;
}


void PC::searchEngineDraw()
{
	//画面の外枠
	{
		SetDrawBlendMode(DX_BLENDMODE_MULA, 50);//乗算合成
		//ポーズウィンドウセロファン(黒い)
		DrawBox(pw_width, pw_height, pw_start_x, pw_start_y, 0x000000, true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//通常描画に戻す

		DrawBox(pw_width, pw_height, pw_start_x, pw_start_y, 0xffffff, false);
	}

	//描画種類
	{
		if (changeMonitorNum == 1 || changeMonitorNum < 4) {
			DrawGraph(144, 130, m_hGoogle, true);
		}
		else if (changeMonitorNum > 3) {
			DrawGraph(144, 130, m_hGlegle, true);
		}
	}

	//検索バーの点滅している奴
	{
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			if (searchBarCollision()) {
				searchBarClick = true;
			}
			else {
				searchBarClick = false;
			}
			flashingTimer = 800;
		}

		if (searchBarClick == true) {
			flashingTimer--;
		}

		if (flashingTimer <= 400) {
			DrawBox(256, 336, 258, 348, GetColor(200, 200, 200), true);
		}
		if (flashingTimer <= 0) {
			flashingTimer = 800;
		}
	}

	//デバッグ用
	{
		//タイマー
		DrawFormatString(170, 300, GetColor(0, 0, 0), "%d", flashingTimer);
		//マウスの判定用
		DrawBox(mouseX, mouseY, mouseX + 10, mouseY + 10, GetColor(0, 0, 0), false);
		//マウスの座標
		DrawFormatString(170, 200, GetColor(0, 0, 0), "%d:%d", mouseX, mouseY);
	}
}

void PC::windowsAcountDraw()
{
	//画面の外枠
	{
		SetDrawBlendMode(DX_BLENDMODE_MULA, 50);//乗算合成
		//ポーズウィンドウセロファン(黒い)
		DrawBox(pw_width, pw_height, pw_start_x, pw_start_y, 0x000000, true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//通常描画に戻す

		DrawBox(pw_width, pw_height, pw_start_x, pw_start_y, 0xffffff, false);
	}

	//描画種類
	{
		if (changeMonitorNum == 1 || changeMonitorNum < 4) {
			DrawGraph(144, 130, m_hWindows, true);
		}
		else if (changeMonitorNum > 3) {
			DrawGraph(144, 130, m_hWindowzzz, true);
		}
	}
}

void PC::getRand() {
	changeMonitorNum = GetRand(max);
	
}

struct PcColData {
	int left;
	int top;
	int right;
	int bottom;
};

PcColData googleColData[] = {
	{595,130,625,150}
};

PcColData searchBarColData[] = {
	{230,330,530,350}
};

PcColData standbySymbolColData[] = {
	{584, 440, 614, 471}
};


bool PC::closeCollision() {

	float playerLeft = m_pos.x;
	float playerRight = m_pos.x + 10;
	float playerTop = m_pos.y;
	float playerBottom = m_pos.y + 10;

	for (PcColData data : googleColData) {
		if (playerRight < data.left)return false;
		if (playerLeft > data.right)return false;
		if (playerBottom < data.top)return false;
		if (playerTop > data.bottom)return false;
		
	}
	return true;
}


bool PC::searchBarCollision() {

	float playerLeft = m_pos.x;
	float playerRight = m_pos.x + 10;
	float playerTop = m_pos.y;
	float playerBottom = m_pos.y + 10;

	for (PcColData data : searchBarColData) {
		if (playerRight < data.left)return false;
		if (playerLeft > data.right)return false;
		if (playerBottom < data.top)return false;
		if (playerTop > data.bottom)return false;

	}
	return true;
}


bool PC::StandbySymbolCollision() {

	float playerLeft = m_pos.x;
	float playerRight = m_pos.x + 10;
	float playerTop = m_pos.y;
	float playerBottom = m_pos.y + 10;

	for (PcColData data : standbySymbolColData) {
		if (playerRight < data.left)return false;
		if (playerLeft > data.right)return false;
		if (playerBottom < data.top)return false;
		if (playerTop > data.bottom)return false;

	}
	return true;
}