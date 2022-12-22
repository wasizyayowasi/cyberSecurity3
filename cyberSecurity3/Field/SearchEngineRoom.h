#pragma once
class SearchEngineRoom
{
public:
	SearchEngineRoom(){}
	~SearchEngineRoom(){}

	int update();
	void draw(int handle, int graphWidth, int graphHeight, int offsetX, int offsetY);

	void drawMap(int handle, int graphWidth, int graphHeight, int offsetX, int offsetY, int aiu);

	int chipNumX(int graphWidth);
	int chipNumY(int graphHeight);
	int chipNum(int graphWidth, int graphHeight);

	void searchEngineRoomMapDataLoad();

private:
	int changeMapData = 3;
};

