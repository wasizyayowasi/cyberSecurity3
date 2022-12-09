#pragma once

#include "Vec2.h"

class PC
{
public:

	PC();
	~PC();

	void drawManager();

	int update();
	void searchEngineDraw();
	void windowsAcountDraw();

	void getRand();

	bool closeCollision();
	bool searchBarCollision();
	bool StandbySymbolCollision();

private:
	int m_hWindows;
	int m_hWindowzzz;
	int m_hGoogle;
	int m_hGlegle;

	int changeMonitorNum;
	int monitorLv;

	int mouseX;
	int mouseY;

	int flashingTimer;

	int flashingCount;

	bool searchBarClick;

	Vec2 m_pos;
};

