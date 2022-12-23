#pragma once
#include "Vec2.h"
#include "Object/Player.h"
class Enemy
{
public:
	//プレイヤーグラフィックの分割数
	static constexpr int kGraphicDivX = 3;
	static constexpr int kGraphicDivY = 4;
	static constexpr int kGraphicDivNum = kGraphicDivX * kGraphicDivY;

	//プレイヤーグラフィックサイズ
	static constexpr int kGraphicSizeX = 48;
	static constexpr int kGraphicSizeY = 64;

public:
	Enemy();
	~Enemy();

	void setHanlde(int index, int handle) { m_hEnemy[index] = handle; }

	Vec2 getPos()const { return m_pos; }

	void init();
	void update(Player& player);
	void draw();

	bool isCol(Player& player);
private:
	int m_hEnemy[kGraphicDivNum];

	int m_animeNo;			//表示する番号
	int m_animeFrame;
	int m_animeDirections;	//表示する方向

	float enemySpeed;

	float playerPosX;
	float playerPosY;

	int m_waitFrame;

	Vec2 m_pos;
};

