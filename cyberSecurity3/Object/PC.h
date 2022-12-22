#pragma once

#include "../Vec2.h"

class PC
{
public:

	PC();
	~PC();

	int drawManager();

	int update();
	void searchEngineDraw();
	void windowsAcountDraw();
	void counterfeitWindowsAcountDraw();
	void desktopDraw();
	void siteDraw(int num);
	void counterfeitsearchEngineDraw();

	void outskirtsDraw();

	void getRand();

	bool closeCollision();
	bool searchBarCollision();
	bool StandbySymbolCollision();
	bool acountBarCollision();
	bool okCollision();
	bool reSearchCollision();
	bool explorerIconCollision();
	bool googleIconCollision();

	int returnSiteNum() { return siteNum; }

private:
	int m_hWindows;
	int m_hWindowzzz;
	int m_hGoogle;
	int m_hGlegle;
	int m_hOutskirts;
	int m_hWallpaper;
	int m_hHuzi;
	int m_hHuzi2;
	int m_hInesayama;
	int m_hKokonoe;
	int m_hNisimiyako;
	int m_hYakusima;
	int m_hUzu;
	int m_hTukumo;

	int changeMonitorNum;
	int monitorLv;
	int traceMonitorLv;

	int mouseX;
	int mouseY;

	int flashingTimer;

	int flashingCount;

	char code[12];
	char codeAnswer[12];
	char search[12];
	char searchAnswer[12];
	char huzi[12];
	char ine[12];
	char koko[30];
	char nisi[30];
	char tukumo[12];
	char uzu[12];
	char yaku[12];

	int hit;
	
	int counterfeit;

	int siteNum;

	bool lock;

	Vec2 m_pos;
};

