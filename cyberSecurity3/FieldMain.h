#pragma once
#include "SceneBase.h"
#include "Player.h"
#include "PC.h"
#include"ReferenceRoom.h"
#include <vector>

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


	//シーン切り替え、更新
	bool shareCollision1();
	bool shareCollision2();
	bool shareCollision3();
	bool corridorCollision();
	bool corridorCollision2();
	bool corridor2Collision();
	bool corridor2Collision2();
	bool corridor3Collision();
	bool corridor3Collision2();


	bool mainFieldCollision();
	bool searchEngineRoomCollision();
	bool searchEngineRoomPcCollision();
	bool referenceRoomCollision();
	bool corridorWallCollision();
	bool corridorWall2Collision();
	bool corridorWall3Collision();

	bool bookshelfCollision();

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

	//フィールド変更用の変数
	int changeFieldNum;

	int changeMonitor;
	
	// プレイヤー画像
	int m_hPlayer[Player::kGraphicDivNum];

	//グラフィックデータのハンドル
	int m_hWall;
	int m_hOrnament;
	int m_hOrnament2;
	

	//グラフィックのデータ
	int m_wallGraphWidth;
	int m_wallGraphHeight;

	int m_ornamentGraphWidth;
	int m_ornamentGraphHeight;

	int m_ornamentGraphWidth2;
	int m_ornamentGraphHeight2;

	//マップチップ編集用データ
	std::vector<int> m_mapData;

	Player m_player;
	PC m_pc;
	ReferenceRoom m_referenceRoom;
};

