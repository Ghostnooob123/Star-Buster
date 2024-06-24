#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#include <WindowConfig.h>

class Enemy {
public:
	Enemy();
	~Enemy();

	void setCenters(float centerX, float centerY);

	sf::RectangleShape getBody();

	std::vector<sf::RectangleShape>& getMissiles();
	std::vector<sf::RectangleShape>::iterator removeMissile(std::vector<sf::RectangleShape>::iterator missile);

	void updateEnemyShooting();

private:
	float centerX;
	float centerY;

	sf::RectangleShape body;
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Clock shootSpawnClock;
	float shootSpawnInterval;

	std::vector<sf::RectangleShape> missiles;

	void initEnemy();
};

#endif // !ENEMY_H