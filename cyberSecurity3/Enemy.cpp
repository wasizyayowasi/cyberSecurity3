#include "Enemy.h"
#include "DxLib.h"
#include "game.h"

Enemy::Enemy():
	enemySpeed(0.0f),
	playerPosX(0.0f),
	playerPosY(0.0f),
	m_waitFrame(0),
	m_animeNo(0),
	m_animeFrame(0),
	m_animeDirections(0)
{
	for (auto& handle : m_hEnemy) {
		handle = -1;
	}
	init();
}

Enemy::~Enemy()
{
}

void Enemy::init() {
	m_pos.x = Game::kScreenWidth / 2 - kGraphicSizeX / 2;
	m_pos.y = Game::kScreenHeight + 32;

	enemySpeed = 3.0f;

	playerPosX = 0;
	playerPosY = 0;

	m_waitFrame = 1;

	m_animeNo = 0;
	m_animeFrame = 0;
	m_animeDirections = 0;

}

void Enemy::update(Player& player) {

	playerPosX = player.getPos().x - m_pos.x;
	playerPosY = player.getPos().y - m_pos.y;


	m_pos.x += playerPosX * enemySpeed / 240;
	m_pos.y += playerPosY * enemySpeed / 240;
		
	

	if (player.getPos().x < m_pos.x) {
		m_animeNo = 4;
	}
	else if (player.getPos().x > m_pos.x) {
		m_animeNo = 7;
	}
	else if (static_cast<int>(player.getPos().y) > static_cast<int>(m_pos.y)) {
		m_animeNo = 0;
	}
	else if (static_cast<int>(player.getPos().y) < static_cast<int>(m_pos.y)) {
		m_animeNo = 10;
	}

}

void Enemy::draw()
{
	DrawGraph(m_pos.x, m_pos.y, m_hEnemy[m_animeNo], true);
}

//ÉvÉåÉCÉÑÅ[Ç∆ÇÃê⁄êGîªíË
bool Enemy::isCol(Player& player) {

	float EnemyLeft = getPos().x;
	float EnemyRight = getPos().x + 28;
	float EnemyTop = getPos().y;
	float EnemyBottom = getPos().y + 28;

	float playerLeft = player.getPos().x;
	float playerRight = player.getPos().x + 32;
	float playerTop = player.getPos().y;
	float playerBottom = player.getPos().y + 32;

	if (playerRight < EnemyLeft)	return false;
	if (playerLeft > EnemyRight)	return false;
	if (playerBottom < EnemyTop)	return false;
	if (playerTop > EnemyBottom)	return false;

	return true;
}