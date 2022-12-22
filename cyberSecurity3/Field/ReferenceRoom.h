#pragma once
//#include "../DrawMap.h"

class ReferenceRoom
{
public:
	ReferenceRoom();
	~ReferenceRoom();

	void drawMap(int handle, int graphWidth, int graphHeight,int offsetX,int offsetY,int aiu);

	void textDraw(int textNum);

	int chipNumX(int graphWidth);
	int chipNumY(int graphHeight);
	int chipNum(int graphWidth, int graphHeight);

	void referenceRoomMapDataLoad();

	int update(int change);
	void draw(int num);

private:
	int m_hBook;
	int m_hBook2;
	int m_hBook3;
	int m_hBook4;

	//DrawMap m_draw;
};

