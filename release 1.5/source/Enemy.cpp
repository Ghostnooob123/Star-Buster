#include <Enemy.h>

Enemy::Enemy()
{
	this->initEnemy();
}
Enemy::~Enemy()
{

}

sf::RectangleShape Enemy::getBody()
{
	return this->body;
}

void Enemy::initEnemy()
{

}
