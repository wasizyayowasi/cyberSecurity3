#pragma once
#include "../Scene/SceneBase.h"
#include "../Object/Player.h"
#include "../Enemy.h"
#include "../Object/PC.h"
#include"ReferenceRoom.h"
#include "SearchEngineRoom.h"
#include <vector>

class SearchEngineRoom;

class FieldMain 
{
public:

	FieldMain();
	~FieldMain();

	void mainFieldLoad();
	void searchEngineRoom();
	void referenceRoom();
	void corridor();
	void corridor2();
	void corridor3();
	void bookmark();

	void changeField();

	void update();
	void draw();

	void textDraw();

	void examinationDraw();

	//マップデータ読み込み
	void mainFieldUpdate();
	void searchEngineRoomUpdate();
	void referenceRoomUpdate();
	void corridorUpdate();
	void corridor2Update();
	void corridor3Update();
	void bookmarkUpdate();
	void carrierPigeonUpdate();


	//シーン切り替え、更新
	bool shareCollision1();
	bool shareCollision2();
	bool shareCollision3();
	bool searchEngineCollision();
	bool corridorCollision();
	bool corridorCollision2();
	bool corridor2Collision();
	bool corridor2Collision2();
	bool corridor3Collision();
	bool corridor3Collision2();
	bool corridor3Collision3();
	bool carrierPigeonCollision();


	bool mainFieldCollision();
	bool mainFieldItemCollision();
	bool searchEngineRoomCollision();
	bool searchEngineRoomPcCollision();
	bool referenceRoomCollision();
	bool corridorWallCollision();
	bool corridorWall2Collision();
	bool corridorWall3Collision();

	bool bookshelfCollision();
	bool bookshelfCollision2();
	bool bookshelfCollision3();
	bool bookshelfCollision4();
	bool meaninglessBookshelfCollision();
	bool bookmarkCollision();
	bool cutCollision();

	void siteDraw();

private:

	//マップの描画
	void drawMap(int offsetX, int offsetY);

	//マップチップの数を取得する
	int chipNumX();
	int chipNumY();
	int chipNum();

	//マップチップの数を取得する
	int chipNum2X();
	int chipNum2Y();
	int chipNum2();

	int chipNum3X();
	int chipNum3Y();
	int chipNum3();

private:
	int textNum = 0;
	int siteNum = 7;
	int photo = 0;

	//フィールド変更用の変数
	int changeFieldNum;

	int changeMonitor;
	
	int collapse;

	int bookNum;

	// プレイヤー画像
	int m_hPlayer[Player::kGraphicDivNum];
	int m_hEnemy[Enemy::kGraphicDivNum];

	//グラフィックデータのハンドル
	int m_hWall;
	int m_hOrnament;
	int m_hOrnament2;
	
	int m_hHuzi;
	int m_hHuzi2;
	int m_hInesayama;
	int m_hKokonoe;
	int m_hNisimiyako;
	int m_hYakusima;
	int m_hUzu;
	int m_hTukumo;

	//グラフィックのデータ
	int m_wallGraphWidth;
	int m_wallGraphHeight;

	int m_ornamentGraphWidth;
	int m_ornamentGraphHeight;

	int m_ornamentGraphWidth2;
	int m_ornamentGraphHeight2;

	int itemCount = 0;

	static constexpr int fade_interval = 60;
	int fadeTimer_ = fade_interval;
	int fadeValue_ = 255;

	unsigned int FadeColor = 0x000000;//フェード色黒

	//マップチップ編集用データ
	std::vector<int> m_mapData;

	Player m_player;
	Enemy m_enemy;
	PC m_pc;
	ReferenceRoom m_referenceRoom;
	SearchEngineRoom m_search;
};

