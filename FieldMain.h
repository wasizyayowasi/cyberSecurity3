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

	//�}�b�v�f�[�^�ǂݍ���
	void mainFieldUpdate();
	void searchEngineRoomUpdate();
	void referenceRoomUpdate();
	void corridorUpdate();
	void corridor2Update();
	void corridor3Update();


	//�V�[���؂�ւ��A�X�V
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

	//�}�b�v�̕`��
	void drawMap(int offsetX, int offsetY);

	//�}�b�v�`�b�v�̐����擾����
	int chipNumX();
	int chipNumY();
	int chipNum();

	//�}�b�v�`�b�v�̐����擾����
	int chipNum2X();
	int chipNum2Y();
	int chipNum2();

	int chipNum3X();
	int chipNum3Y();
	int chipNum3();

private:

	//�t�B�[���h�ύX�p�̕ϐ�
	int changeFieldNum;

	int changeMonitor;
	
	// �v���C���[�摜
	int m_hPlayer[Player::kGraphicDivNum];

	//�O���t�B�b�N�f�[�^�̃n���h��
	int m_hWall;
	int m_hOrnament;
	int m_hOrnament2;
	

	//�O���t�B�b�N�̃f�[�^
	int m_wallGraphWidth;
	int m_wallGraphHeight;

	int m_ornamentGraphWidth;
	int m_ornamentGraphHeight;

	int m_ornamentGraphWidth2;
	int m_ornamentGraphHeight2;

	//�}�b�v�`�b�v�ҏW�p�f�[�^
	std::vector<int> m_mapData;

	Player m_player;
	PC m_pc;
	ReferenceRoom m_referenceRoom;
};

