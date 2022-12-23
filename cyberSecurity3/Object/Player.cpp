#include "Player.h"
#include "Player.h"
#include "DxLib.h"
#include "../game.h"

namespace {
	//�L�����N�^�[�A�j���[�V����1�R�}������̃t���[����
	constexpr int kAnimeChangeFrame = 8;
	constexpr int speed = 4;
}

Player::Player() :
	m_animeNo(0),
	m_animeFrame(0),
	m_animeDirections(0),
	m_pos(486, 208),
	tracePosX(0),
	tracePosY(0)
{
	for (auto& handle : m_handle) {
		handle = -1;
	}
}

Player::~Player() {

}

void Player::init() {

}

void Player::end() {

}

void Player::update() {
	// �p�b�h(�������̓L�[�{�[�h)����̓��͂��擾����
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	bool isKey = false;
	if (padState & PAD_INPUT_UP)
	{
		//��@73�`96
		m_pos.y -= speed;
		m_animeDirections = 3;
		if (m_pos.y < 0) {
			m_pos.y = 0;
		}
		isKey = true;
	}
	if (padState & PAD_INPUT_DOWN)
	{
		//���@1�`24
		m_pos.y += speed;
		m_animeDirections = 0;
		if (m_pos.y > Game::kScreenHeight - 48) {
			m_pos.y = Game::kScreenHeight - 48;
		}
		isKey = true;
	}
	if (padState & PAD_INPUT_LEFT)
	{
		//���@25�`48
		m_pos.x -= speed;
		m_animeDirections = 1;
		if (m_pos.x < -36) {
			m_pos.x = -36;
		}
		isKey = true;
	}
	if (padState & PAD_INPUT_RIGHT)
	{
		//�E�@49�`72
		m_pos.x += speed;
		m_animeDirections = 2;
		if (m_pos.x > Game::kScreenWidth - 36) {
			m_pos.x = Game::kScreenWidth - 36;
		}
		isKey = true;
	}


	//�L�����N�^�[�̃A�j���[�V����
	if (isKey) m_animeFrame++;

	if (m_animeFrame >= kGraphicDivX * kAnimeChangeFrame) {
		m_animeFrame = 1;
	}

	int tempAnimeNo = m_animeFrame / kAnimeChangeFrame;
	m_animeNo = m_animeDirections * kGraphicDivX + tempAnimeNo;
}

void Player::draw() {

	DrawGraph(m_pos.x, m_pos.y, m_handle[m_animeNo], true);
}

//�ЂƂO�̍��W���c��
void Player::trace() {
	tracePosX = m_pos.x;
	tracePosY = m_pos.y;
}

void Player::tradePos() {
	m_pos.x = tracePosX;
	m_pos.y = tracePosY;
}