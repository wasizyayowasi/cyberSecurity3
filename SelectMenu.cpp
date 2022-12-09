#include "SelectMenu.h"
#include "DxLib.h"
#include "Pad.h"

namespace {
	//ÉÅÉjÉÖÅ[çÄñ⁄ÇÃä‘äu
	constexpr int kMenuItemInterval = 64;

}


//====================================================//
//SelectMenu::Item
//====================================================//

SelectMenu::Item::Item() {
	m_text = nullptr;
}
SelectMenu::Item::~Item() {

}
void SelectMenu::Item::draw(int x, int y) {
	DrawString(x, y, m_text, GetColor(255, 255, 255));
}

void SelectMenu::Item::setText(const char* text) {
	m_text = text;
}

int SelectMenu::Item::getTextWidth() {
	return GetDrawStringWidth(m_text, strlen(m_text));
}

//====================================================//
//SelectMenu
//====================================================//

SelectMenu::Cursor::Cursor() :
	m_itemNum(0),
	m_repeatUp(0),
	m_repeatDown(0),
	m_selectIndex(0)
{

}

SelectMenu::Cursor::~Cursor() {

}

int SelectMenu::Cursor::update() {
	if (Pad::isPress(PAD_INPUT_UP))
	{
		if (m_repeatUp <= 0) {

			m_selectIndex--;
			m_repeatUp = 8;
			if (m_selectIndex < 0) {
				if (Pad::isTrigger(PAD_INPUT_UP)) {
					m_selectIndex = m_itemNum - 1;
				}
				else {
					m_selectIndex = 0;
				}
			}
		}
		else {
			m_repeatUp--;
		}
	}
	else {
		m_repeatUp = 0;
	}

	if (Pad::isPress(PAD_INPUT_DOWN)) {
		if (m_repeatDown <= 0) {
			m_selectIndex++;
			m_repeatDown = 8;
			if (m_selectIndex > m_itemNum - 1) {
				if (Pad::isTrigger(PAD_INPUT_DOWN)) {
					m_selectIndex = 0;
				}
				else {
					m_selectIndex = m_itemNum - 1;
				}
			}
		}
		else {
			m_repeatDown--;
		}
	}
	else {
		m_repeatDown = 0;
	}

	return m_selectIndex;
}

void SelectMenu::Cursor::draw() {
	int posX = m_menuPos.x;
	int posY = m_menuPos.y + kMenuItemInterval * m_selectIndex;

	//DrawBox(posX - 13, posY - 3, posX - 2, posY + 8, GetColor(255, 255, 255), true);
	//DrawBox(posX - 10, posY, posX - 5, posY + 5, GetColor(255, 0, 0), true);
	DrawCircle(posX - 10, posY + 8, 5, GetColor(255, 255, 255), true);
}

//====================================================//
//SelectMenu
//====================================================//
SelectMenu::SelectMenu() {

}

SelectMenu::~SelectMenu() {

}

void SelectMenu::init() {

}

void SelectMenu::end() {
	for (auto& pItem : m_pItem) {
		delete pItem;
	}
	//m_pItem.clear();
}

int SelectMenu::update() {
	m_num = m_cursor.update();
	return m_num;
}

void SelectMenu::draw() {

	int width = getWindowWidth();
	int height = getWindowHeight();

	//ï∂éöÇÃîwåi
	//DrawBox(m_pos.x, m_pos.y, m_pos.x + width, m_pos.y + height, GetColor(64, 64, 64), true);

	for (int i = 0; i < m_pItem.size(); i++) {
		m_pItem[i]->draw(m_pos.x, m_pos.y + i * kMenuItemInterval);
	}
	m_cursor.draw();
}

void SelectMenu::setUpCursor() {
	m_cursor.setMenuPos(m_pos);
	m_cursor.setSize(Vec2(getWindowWidth(), kMenuItemInterval));
	m_cursor.setItemNum(m_pItem.size());
}

void SelectMenu::setPos(float x, float y) {
	setPos(Vec2(x, y));
}

void SelectMenu::setPos(Vec2 pos) {
	m_pos = pos;
}

void SelectMenu::addItem(const char* text) {
	Item* pItem = new Item;
	pItem->setText(text);
	m_pItem.push_back(pItem);
}

int SelectMenu::getWindowWidth() {

	int width = 0;
	for (auto& pItem : m_pItem) {
		if (width < pItem->getTextWidth()) {
			width = pItem->getTextWidth();
		}
	}
	return width;
}
int SelectMenu::getWindowHeight() {
	int height = kMenuItemInterval * m_pItem.size();
	return height;
}