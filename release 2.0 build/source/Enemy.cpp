#include "Enemy.h"

Enemy::Enemy() {
	this->initEnemy();
}
Enemy::~Enemy() {

}

void Enemy::setCenters(float centerX, float centerY)
{
	this->centerX = centerX;
	this->centerY = centerY;

	this->body.setPosition(centerX, centerY);
}

sf::RectangleShape Enemy::getBody()
{
	return this->body;
}

std::vector<sf::RectangleShape>& Enemy::getMissiles()
{
	return this->missiles;
}
std::vector<sf::RectangleShape>::iterator Enemy::removeMissile(std::vector<sf::RectangleShape>::iterator missile)
{
	return this->missiles.erase(missile);
}

void Enemy::updateEnemyShooting()
{
	if (this->shootSpawnClock.getElapsedTime().asSeconds() >= this->shootSpawnInterval)
	{
		sf::RectangleShape newMissile;

		newMissile.setFillColor(sf::Color(237, 192, 9));
		newMissile.setSize(sf::Vector2f(5.0f, 20.0f));
		newMissile.setPosition(this->body.getPosition().x + this->body.getSize().x / 2, this->body.getPosition().y);

		this->missiles.push_back(newMissile);

		shootSpawnClock.restart();
	}

	//for (size_t i = 0; i < this->missiles.size(); )
	//{
	//	this->missiles[i].move(0.0f, 7.0f);

	//	if (this->missiles[i].getPosition().y + this->missiles[i].getSize().y > monitorY)
	//	{
	//		this->missiles.erase(this->missiles.begin() + i);
	//	}
	//	else
	//	{
	//		++i;
	//	}
	//}
}

void Enemy::initEnemy()
{
	this->centerX = 0.0f;
	this->centerY = 0.0f;

	this->shootSpawnInterval = 2.0f;

	this->body.setFillColor(sf::Color::Green);
	this->body.setSize(sf::Vector2f(50.0f, 50.0f));
}
