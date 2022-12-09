#pragma once
#include <vector>
#include "Vec2.h"
#include "Pad.h"

class SelectMenu {
public:
	SelectMenu();
	virtual ~SelectMenu();

	//�������A�I������
	void init();
	void end();

	//�X�V
	int update();
	//�`��
	void draw();

	//�J�[�\���̏�����
	void setUpCursor();

	//�\���ʒu�̐ݒ�
	void setPos(float x, float y);
	void setPos(Vec2 vec);

	//���j���[���ڂ̒ǉ�
	void addItem(const char* text);

	//�E�C���h�E�T�C�Y�̎擾
	int getWindowWidth();
	int getWindowHeight();

private:
	int m_num;

private:
	class Item {
	public:
		Item();
		virtual ~Item();

		//���j���[���ڂ̕\��
		void draw(int x, int y);

		//�\�����镶�����ݒ�
		void setText(const char* text);

		//������̕����擾
		int getTextWidth();
	private:
		//�\�����镶����
		const char* m_text;


	};
	class Cursor {
	public:
		Cursor();
		virtual ~Cursor();

		//�X�V
		int update();
		//�\��
		void draw();

		void setMenuPos(Vec2 pos) { m_menuPos = pos; }
		void setSize(Vec2 size) { m_size = size; }
		void setItemNum(int num) { m_itemNum = num; }
	private:
		//���j���[�̕\���ʒudraw
		Vec2 m_menuPos;
		//�J�[�\���̃T�C�Y
		Vec2 m_size;

		//���j���[�̍��ڐ�
		int m_itemNum;

		//���s�[�g���̓J�E���^
		int m_repeatUp;
		int m_repeatDown;

		//�I�����Ă��鍀�ڂ̔ԍ�
		int m_selectIndex;

	};


private:
	//�\���ʒu(������W)
	Vec2 m_pos;
	//���j���[�̑I������
	std::vector<Item*> m_pItem;
	//�J�[�\��
	Cursor m_cursor;
};

