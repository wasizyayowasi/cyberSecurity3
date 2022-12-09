#pragma once

#include "Vec2.h"

class PC
{
public:

	PC();
	~PC();

	int update();
	void draw();

	void getRand();

	bool closeCollision();
	bool searchBarCollision();

private:
	int m_hGoogle;
	int m_hGlegle;

	int changeMonitorNum;

	int mouseX;
	int mouseY;

	int flashingTimer;

	int flashingCount;

	bool searchBarClick;

	Vec2 m_pos;
};

