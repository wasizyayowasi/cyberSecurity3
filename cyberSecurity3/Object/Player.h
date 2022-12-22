#pragma once
#include "../Vec2.h"

class Player {
public:

	//プレイヤーグラフィックの分割数
	static constexpr int kGraphicDivX = 3;
	static constexpr int kGraphicDivY = 4;
	static constexpr int kGraphicDivNum = kGraphicDivX * kGraphicDivY;

	//プレイヤーグラフィックサイズ
	static constexpr int kGraphicSizeX = 48;
	static constexpr int kGraphicSizeY = 48;

public:



	Player();
	~Player();

	void setHanlde(int index, int handle) { m_handle[index] = handle; }
	void setPos(int posX, int posY) { m_pos.x = posX, m_pos.y = posY; }

	void init();

	Vec2 getPos()const { return m_pos; }

	void end();

	void update();
	void draw();

	void trace();

	void tradePos();

private:

	//グラフィック
	int m_handle[kGraphicDivNum];

	int tracePosX;
	int tracePosY;

	// 表示位置
	Vec2 m_pos;
	// 移動
	Vec2 m_vec;

	//キャラクターのアニメーション
	int m_animeNo;			//表示する番号
	int m_animeFrame;
	int m_animeDirections;	//表示する方向
};

