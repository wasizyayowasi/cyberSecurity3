#include "ReferenceRoom.h"
#include "FieldMain.h"
#include "DxLib.h"
#include "../DrawFunctions.h"
#include "../Pad.h"
#include "../game.h"
#include "../MapData.h"
#include <cassert>

namespace {
	constexpr int pw_width = 124;				//ポーズ枠の幅
	constexpr int pw_height = 110;				//ポーズ枠の高さ
	constexpr int pw_start_x = 644;				//ポーズ枠に左
	constexpr int pw_start_y = 498;				//ポーズ枠上
}

namespace {
	
}

ReferenceRoom::ReferenceRoom():
	m_hBook(-1),
	m_hBook2(-1),
	m_hBook3(-1),
	m_hBook4(-1)
{
	m_hBook = My::MyLoadGraph("data/hon1.png");
	m_hBook2 = My::MyLoadGraph("data/hon2.png");
	m_hBook3 = My::MyLoadGraph("data/hon3.png");
	m_hBook4 = My::MyLoadGraph("data/hon4.png");
}

ReferenceRoom::~ReferenceRoom()
{
	DeleteGraph(m_hBook);
}

void ReferenceRoom::drawMap(int handle, int graphWidth, int graphHeight, int offsetX, int offsetY,int aiu)
{

	//m_draw.drawMap(handle, graphWidth, graphHeight, offsetX, offsetY, aiu);

	//マップデータの描画①
	for (int x = 0; x < Map::kBgNumX; x++) {
		for (int y = 0; y < Map::kBgNumY; y++) {

			int chipNo = Map::kMapData2[y][x];

			//多分ここが問題三回描画しているけれどデータが同じ
			switch (aiu) {
			case 0:
				chipNo = Map::kMapData[y][x];
				break;
			case 1:
				chipNo = Map::kMapData2[y][x];
				break;
			case 2:
				chipNo = Map::kMapData3[y][x];
				break;
			}
							
			assert(chipNo >= 0);
			assert(chipNo < chipNum(graphWidth,graphHeight));

			int graphX = (chipNo % chipNumX(graphWidth)) * Map::kChipSize;
			int graphY = (chipNo / chipNumX(graphWidth)) * Map::kChipSize;

			DrawRectGraph(x * Map::kChipSize + offsetX, y * Map::kChipSize + offsetY,
				graphX, graphY, Map::kChipSize, Map::kChipSize,
				handle, true, false);
		}
	}
}

void ReferenceRoom::textDraw(int textNum)
{
	//{//デバッグ用
	//	int mouseX, mouseY;
	//	//マウス
	//	GetMousePoint(&mouseX, &mouseY);
	//	//マウスの座標
	//	DrawFormatString(170, 200, GetColor(0, 0, 0), "%d:%d", mouseX, mouseY);
	//}
	
	//画面の外枠
	{
		SetDrawBlendMode(DX_BLENDMODE_MULA, 50);//乗算合成
		//ポーズウィンドウセロファン(黒い)
		DrawBox(88, 410, 680, 540, 0x000000, true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//通常描画に戻す

		DrawBox(88, 410, 680, 540, 0xffffff, false);
	}

	DrawString(126, 444, "★(将来行きたいところ)", GetColor(255, 255, 255));

	switch (textNum) {
	case 0:
		DrawString(126, 474, "雲海テラス", GetColor(255, 255, 255));
		break;
	case 1:
		DrawString(126, 474, "青い池", GetColor(255, 255, 255));
		break;
	case 2:
		DrawString(126, 474, "神の子池", GetColor(255, 255, 255));
		break;
	case 3:
		DrawString(126, 474, "亀岩の洞窟", GetColor(255, 255, 255));
		break;
	case 4:
		DrawString(126, 474, "涸沢カール", GetColor(255, 255, 255));
		break;
	case 5:
		DrawString(126, 474, "高ボッチ高原", GetColor(255, 255, 255));
		break;
	case 6:
		DrawString(126, 474, "元乃隅稲成神社", GetColor(255, 255, 255));
		break;
	case 7:
		DrawString(126, 474, "銀水洞", GetColor(255, 255, 255));
		break;
	case 8:
		DrawString(126, 474, "稲積水中鍾乳洞", GetColor(255, 255, 255));
		break;
	case 9:
		DrawString(126, 474, "はての浜", GetColor(255, 255, 255));
		break;
	case 10:
		DrawString(126, 474, "弘前公園の桜", GetColor(255, 255, 255));
		break;
	case 11:
		DrawString(126, 474, "イエローナイフのオーロラ", GetColor(255, 255, 255));
		break;
	case 12:
		DrawString(126, 474, "ウユニ塩湖", GetColor(255, 255, 255));
		break;
	case 13:
		DrawString(126, 474, "マウナ・ケア山の星空", GetColor(255, 255, 255));
		break;
	case 14:
		DrawString(126, 474, "パムッカレ", GetColor(255, 255, 255));
		break;
	case 15:
		DrawString(126, 474, "マッターホルンとリッフェル湖", GetColor(255, 255, 255));
		break;
	}
}

int ReferenceRoom::chipNumX(int graphWidth) {
	return (graphWidth / Map::kChipSize);
}

int ReferenceRoom::chipNumY(int graphHeight) {
	return (graphHeight / Map::kChipSize);
}

int ReferenceRoom::chipNum(int graphWidth, int graphHeight) {
	return (chipNumX(graphWidth) * chipNumY(graphHeight));
}

void ReferenceRoom::referenceRoomMapDataLoad()
{

	//m_draw.loadMapData();
	
	constexpr int kReferenceRoomData[Map::kBgNumY][Map::kBgNumX] =
	{
		{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
		{151,151,151,151,151,151,151,151,151,151, 76, 76, 76, 76,151,151,151,151,151,151,151,151,151,151},
		{151,151, 76, 76, 76, 76, 76, 76, 76, 76, 84,151,151, 84, 76, 76, 76, 76, 76, 76, 76, 76,151,151},
		{151,151, 84, 84, 84, 84, 84, 84, 84, 84, 92,151,151, 92, 84, 84, 84, 84, 84, 84, 84, 84,151,151},
		{151,151, 92, 92, 92, 92, 92, 92, 92, 92,151,151,151,151, 92, 92, 92, 92, 92, 92, 92, 92,151,151},
		{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
		{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
		{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
		{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
		{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
		{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
		{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
		{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
		{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
		{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
		{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
		{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
		{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
		{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	};

	constexpr int kReferenceRoomData2[Map::kBgNum2Y][Map::kBgNum2X] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,62,62,62,62, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62, 0, 0},
		{ 0, 0,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62, 0, 0},
		{ 0, 0,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62, 0, 0},
		{ 0,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62, 0, 0},
		{ 0,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62, 0, 0},
		{ 0,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62, 0, 0},
		{ 0,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62, 0, 0},
		{ 0, 0,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62, 0, 0},
		{ 0, 0,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62, 0, 0},
		{ 0, 0,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62, 0, 0},
		{ 0, 0,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62, 0, 0},
		{ 0, 0,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62, 0, 0},
		{ 0, 0,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	};

	constexpr int kReferenceRoomData3[Map::kBgNum3Y][Map::kBgNum3X] =
	{
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{  0,  0,214,215,214,215,214,215,214,215,  0,  0,  0,  0,214,215,214,215,214,215,214,215,  0,  0},
		{  0,  0,230,231,230,231,230,231,230,231,  0,  0,  0,  0,230,231,230,231,230,231,230,231,  0,  0},
		{  0,  0,246,247,246,247,246,247,246,247,  0,  0,  0,  0,246,247,246,247,246,247,246,247,  0,  0},
		{  0,  0,214,215,214,215,214,215,214,215,  0,  0,  0,  0,214,215,214,215,214,215,214,215,  0,  0},
		{  0,  0,230,231,230,231,230,231,230,231,  0,  0,  0,  0,230,231,230,231,230,231,230,231,  0,  0},
		{  0,  0,246,247,246,247,246,247,246,247,  0,  0,  0,  0,246,247,246,247,246,247,246,247,  0,  0},
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{  0,  0,214,215,214,215,214,215,214,215,  0,  0,  0,  0,214,215,214,215,214,215,214,215,  0,  0},
		{  0,  0,230,231,230,231,230,231,230,231,  0,  0,  0,  0,230,231,230,231,230,231,230,231,  0,  0},
		{  0,  0,246,247,246,247,246,247,246,247,  0,  0,  0,  0,246,247,246,247,246,247,246,247,  0,  0},
		{  0,  0,214,215,214,215,214,215,214,215,  0,  0,  0,  0,214,215,214,215,214,215,214,215,  0,  0},
		{  0,  0,230,231,230,231,230,231,230,231,  0,  0,  0,  0,230,231,230,231,230,231,230,231,  0,  0},
		{  0,  0,246,247,246,247,246,247,246,247,  0,  0,  0,  0,246,247,246,247,246,247,246,247,  0,  0},
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	};

	for (int y = 0; y < Map::kBgNumY; y++) {
		for (int x = 0; x < Map::kBgNumX; x++) {
			Map::kMapData[y][x] = kReferenceRoomData[y][x];
			Map::kMapData2[y][x] = kReferenceRoomData2[y][x];
			Map::kMapData3[y][x] = kReferenceRoomData3[y][x];
		}
	}
}

int ReferenceRoom::update(int change)
{
	if (Pad::isPress(PAD_INPUT_2)) {
		return 2;
	}
	return change;
}

void ReferenceRoom::draw(int num)
{
	//画面の外枠
	{
		SetDrawBlendMode(DX_BLENDMODE_MULA, 50);//乗算合成
		//ポーズウィンドウセロファン(黒い)
		DrawBox(pw_width, pw_height, pw_start_x, pw_start_y, 0x000000, true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//通常描画に戻す

		DrawBox(pw_width, pw_height, pw_start_x, pw_start_y, 0xffffff, false);
	}

	switch (num) {
	case 0:
		DrawGraph(144, 130, m_hBook, true);
		break;
	case 1:
		DrawGraph(144, 130, m_hBook2, true);
		break;
	case 2:
		DrawGraph(144, 130, m_hBook3, true);
		break;
	case 3:
		DrawGraph(144, 130, m_hBook4, true);
		break;
	}
	
}


