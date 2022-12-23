#include "PC.h"

#include "../DrawFunctions.h"
#include "../Pad.h"

#include "DxLib.h"

namespace {
	const int max = 10;

	constexpr int pw_width = 124;				//ポーズ枠の幅
	constexpr int pw_height = 110;				//ポーズ枠の高さ
	constexpr int pw_start_x = 644;				//ポーズ枠に左
	constexpr int pw_start_y = 498;				//ポーズ枠上

	int white = GetColor(255, 255, 255);
	int color1 = GetColor(180, 180, 180);
	int color2 = GetColor(0, 0, 0);
	int black = GetColor(255, 255, 255);
}

PC::PC() :
	m_hWindows(-1),
	m_hWindowzzz(-1),
	m_hGoogle(-1),
	m_hGlegle(-1),
	m_hOutskirts(-1),
	m_hHuzi(-1),
	m_hHuzi2(-1),
	m_hInesayama(-1),
	m_hKokonoe(-1),
	m_hNisimiyako(-1),
	m_hYakusima(-1),
	m_hUzu(-1),
	m_hTukumo(-1),

	changeMonitorNum(4),
	monitorLv(1),
	traceMonitorLv(0),
	mouseX(0),
	mouseY(0),
	flashingTimer(0),
	flashingCount(0),
	hit(0),

	counterfeit(0),
	siteNum(7),
	lock(false),
	code(""),
	codeAnswer("huzisan"),
	search(""),
	searchAnswer("huzisan"),
	huzi("huzisan"),
	ine("inasayama"),
	koko("kokonoeyumeooturihasi"),
	nisi("saitobarukohunngunn"),
	tukumo("tukumozima"),
	uzu("uzugatake"),
	yaku("yakusima")

{
	m_hWindows = My::MyLoadGraph("data/Windows.png");
	m_hWindowzzz = My::MyLoadGraph("data/Windowzzz.png");
	m_hGoogle = My::MyLoadGraph("data/google.png");
	m_hGlegle = My::MyLoadGraph("data/glegle.png");
	m_hOutskirts = My::MyLoadGraph("data/misuwindows.png");
	m_hWallpaper = My::MyLoadGraph("data/kabegami2.png");

	m_hHuzi = My::MyLoadGraph("data/sHuzi.png");
	m_hHuzi2 = My::MyLoadGraph("data/sHuzi2.png");
	m_hInesayama = My::MyLoadGraph("data/sInesayama.png");
	m_hKokonoe = My::MyLoadGraph("data/sKokonoe.png");
	m_hNisimiyako = My::MyLoadGraph("data/sNisimiyako.png");
	m_hYakusima = My::MyLoadGraph("data/sYakusima.png");
	m_hUzu = My::MyLoadGraph("data/sUzu.png");
	m_hTukumo = My::MyLoadGraph("data/sTukumo.png");

	SetKeyInputStringColor(color2, color2, color1, white, white, white, 255, white, white, white, white, white, white, white, white, color2, white);
}

PC::~PC()
{
	DeleteGraph(m_hGoogle);
	DeleteGraph(m_hGlegle);
	DeleteGraph(m_hWindows);
	DeleteGraph(m_hWindowzzz);
	DeleteGraph(m_hOutskirts);
	DeleteGraph(m_hWallpaper);
	DeleteGraph(m_hHuzi);
	DeleteGraph(m_hHuzi2);
	DeleteGraph(m_hInesayama);
	DeleteGraph(m_hKokonoe);
	DeleteGraph(m_hNisimiyako);
	DeleteGraph(m_hYakusima);
	DeleteGraph(m_hUzu);
	DeleteGraph(m_hTukumo);
}

//描画を管理
int PC::drawManager()
{
	//画面の外枠
	{
		SetDrawBlendMode(DX_BLENDMODE_MULA, 50);//乗算合成
		//ポーズウィンドウセロファン(黒い)
		DrawBox(pw_width, pw_height, pw_start_x, pw_start_y, 0x000000, true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//通常描画に戻す

		DrawBox(pw_width, pw_height, pw_start_x, pw_start_y, 0xffffff, false);
	}

	switch (monitorLv) {
	case 0:
		windowsAcountDraw();
		break;
	case 1:
		counterfeitWindowsAcountDraw();
		break;
	case 2:
		outskirtsDraw();
		break;
	case 3:
		desktopDraw();
		break;
	case 4:
		siteDraw(siteNum);
		break;
	case 5:
		searchEngineDraw();
		break;
	case 6:
		counterfeitsearchEngineDraw();
		break;
	}
	return counterfeit;
}

//メインの処理
int PC::update()
{

	//マウス
	GetMousePoint(&mouseX, &mouseY);

	m_pos.x = mouseX;
	m_pos.y = mouseY;

	switch (monitorLv) {
	case 0:
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			if (StandbySymbolCollision()) {
				return 1;
			}
		}
		break;
	case 1:
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			if (StandbySymbolCollision()) {
				return 1;
			}
		}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	}
	
	
	

	if (Pad::isPress(PAD_INPUT_2)) {
		monitorLv = 2;
		return 1;
	}
	return 8;
}


//ログイン画面
void PC::windowsAcountDraw()
{
	//描画種類
	{
		DrawGraph(144, 130, m_hWindows, true);
		DrawString(350, 390, "ヒント", GetColor(255, 255, 255));
		DrawString(250, 420, "思い出の本に写真がない場所の名前", GetColor(255, 255, 255));
	}

	//検索バーの点滅している奴
	{
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			if (acountBarCollision()) {
				if (KeyInputSingleCharString(320, 360, 25, code, true) == 1) {
					for (int i = 0; i < 12; i++) {
						if (code[i] == codeAnswer[i]) {
							hit++;
						}
					}
					if (hit == 12) {
						monitorLv = 3;
						lock = true;
					}
					else if (hit != 12) {
						traceMonitorLv = monitorLv;
						hit = 0;
						monitorLv = 2;
						for (int i = 0; i < 12; i++) {
							code[i] = NULL;
						}
					}
				}
			}
		}
	}



	
}


void PC::counterfeitWindowsAcountDraw()
{
	//描画種類
	{
		DrawGraph(144, 130, m_hWindowzzz, true);
	}

	//検索バーの点滅している奴
	{
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			if (acountBarCollision()) {
				if (KeyInputSingleCharString(320, 360, 25, code, true) == 1) {
					traceMonitorLv = monitorLv;
					monitorLv = 2;
					for (int i = 0; i < 12; i++) {
						code[i] = NULL;
					}
					counterfeit++;
				}
			}
		}
	}

	
}


//パスワードを間違ったときの描画
void PC::outskirtsDraw()
{
	DrawGraph(144, 130, m_hOutskirts, true);

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_10) {
		monitorLv = traceMonitorLv;
	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		if (okCollision()) {
			monitorLv = traceMonitorLv;
		}
	}
	
}


void PC::desktopDraw()
{
	DrawGraph(144, 130, m_hWallpaper, true);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		if (googleIconCollision()) {
			if (GetRand(1) == 0) {
				monitorLv = 5;
			}
			else {
				monitorLv = 6;
			}
		}
	}

	
}


//検索サイトの描画
void PC::searchEngineDraw()
{
	//描画種類
	{
		DrawGraph(144, 130, m_hGoogle, true);
	}

	//検索バーの点滅している奴
	{
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			if (searchBarCollision()) {
				if (KeyInputSingleCharString(258, 334, 25, search, true) == 1) {
					for (int i = 0; i < 1; i++) {
						if (search[i] == huzi[i]) {
							siteNum = 0;
							monitorLv = 4;
							
						}
						else if (search[i] == ine[i]) {
							siteNum = 1;
							monitorLv = 4;
						}
						else if (search[i] == koko[i]) {
							siteNum = 2;
							monitorLv = 4;
						}
						else if (search[i] == nisi[i]) {
							siteNum = 3;
							monitorLv = 4;
						}
						else if (search[i] == tukumo[i]) {
							siteNum = 4;
							monitorLv = 4;
						}
						else if (search[i] == uzu[i]) {
							siteNum = 5;
							monitorLv = 4;
						}
						else if (search[i] == yaku[i]) {
							siteNum = 6;
							monitorLv = 4;
						}
						
					}
				}
			}
		}
		hit = 0;
		/*for (int i = 0; i < 3; i++) {
			search[i] = NULL;
		}*/
	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		if (closeCollision()) {
			monitorLv = 3;
		}
	}
	

	
}


void PC::counterfeitsearchEngineDraw()
{
	//描画種類
	{
		DrawGraph(144, 130, m_hGlegle, true);
	}

	//検索バーの点滅している奴
	{
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			if (searchBarCollision()) {
				if (KeyInputSingleCharString(258, 334, 25, search, true) == 1) {

					counterfeit++;
				}
			}
		}
	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		if (closeCollision()) {
			monitorLv = 3;
		}
	}


}


void PC::siteDraw(int num)
{
	switch (siteNum) {
	case 0:
		DrawGraph(144, 130, m_hHuzi, true);
		break;
	case 1:
		DrawGraph(144, 130, m_hInesayama, true);
		break;
	case 2:
		DrawGraph(144, 130, m_hKokonoe, true);
		break;
	case 3:
		DrawGraph(144, 130, m_hNisimiyako, true);
		break;
	case 4:
		DrawGraph(144, 130, m_hTukumo, true);
		break;
	case 5:
		DrawGraph(144, 130, m_hUzu, true);
		break;
	case 6:
		DrawGraph(144, 130, m_hYakusima, true);
		break;
	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		if (closeCollision()) {
			monitorLv = 3;
		}
	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		if (reSearchCollision()) {
			if (KeyInputSingleCharString(358, 168, 10, search, true) == 1) {
				for (int i = 0; i < 1; i++) {
					if (search[i] == huzi[i]) {
						siteNum = 0;
						monitorLv = 4;
					}
					else if (search[i] == ine[i]) {
						siteNum = 1;
						monitorLv = 4;
					}
					else if (search[i] == koko[i]) {
						siteNum = 2;
						monitorLv = 4;
					}
					else if (search[i] == nisi[i]) {
						siteNum = 3;
						monitorLv = 4;
					}
					else if (search[i] == tukumo[i]) {
						siteNum = 4;
						monitorLv = 4;
					}
					else if (search[i] == uzu[i]) {
						siteNum = 5;
						monitorLv = 4;
					}
					else if (search[i] == yaku[i]) {
						siteNum = 6;
						monitorLv = 4;
					}
					search[i] = NULL;
				}
			}
		}
	}
	hit = 0;

	
}


void PC::getRand() {
	if (!lock) {
		monitorLv = GetRand(1);
	}
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

PcColData barColData[] = {
	{310, 356, 466, 376}
};

PcColData okColData[] = {
	{358, 386, 408, 408}
};

PcColData reSearchColData[] = {
	{202, 166, 352, 184}
};

PcColData explorerIconColData[] = {
	{152,138,184,166},
	{260,460,276,474},
};

PcColData googleIconColData[] = {
	{152,184,184,220},
	{286,460,300,474},
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

bool PC::acountBarCollision() {

	float playerLeft = m_pos.x;
	float playerRight = m_pos.x + 10;
	float playerTop = m_pos.y;
	float playerBottom = m_pos.y + 10;

	for (PcColData data : barColData) {
		if (playerRight < data.left)return false;
		if (playerLeft > data.right)return false;
		if (playerBottom < data.top)return false;
		if (playerTop > data.bottom)return false;

	}
	return true;
}

bool PC::okCollision() {

	float playerLeft = m_pos.x;
	float playerRight = m_pos.x + 10;
	float playerTop = m_pos.y;
	float playerBottom = m_pos.y + 10;

	for (PcColData data : okColData) {
		if (playerRight < data.left)return false;
		if (playerLeft > data.right)return false;
		if (playerBottom < data.top)return false;
		if (playerTop > data.bottom)return false;

	}
	return true;
}


bool PC::reSearchCollision() {

	float playerLeft = m_pos.x;
	float playerRight = m_pos.x + 10;
	float playerTop = m_pos.y;
	float playerBottom = m_pos.y + 10;

	for (PcColData data : reSearchColData) {
		if (playerRight < data.left)return false;
		if (playerLeft > data.right)return false;
		if (playerBottom < data.top)return false;
		if (playerTop > data.bottom)return false;

	}
	return true;
}


bool PC::explorerIconCollision() {

	float playerLeft = m_pos.x;
	float playerRight = m_pos.x + 10;
	float playerTop = m_pos.y;
	float playerBottom = m_pos.y + 10;

	for (PcColData data : explorerIconColData) {
		if (playerRight < data.left)continue;
		if (playerLeft > data.right)continue;
		if (playerBottom < data.top)continue;
		if (playerTop > data.bottom)continue;
		return true;
	}
	return false;
}

bool PC::googleIconCollision()
{
	float playerLeft = m_pos.x;
	float playerRight = m_pos.x + 10;
	float playerTop = m_pos.y;
	float playerBottom = m_pos.y + 10;

	for (PcColData data : googleIconColData) {
		if (playerRight < data.left)continue;
		if (playerLeft > data.right)continue;
		if (playerBottom < data.top)continue;
		if (playerTop > data.bottom)continue;
		return true;
	}
	return false;
}
