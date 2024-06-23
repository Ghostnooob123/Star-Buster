#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
public:
	Enemy();
	~Enemy();


	sf::RectangleShape getBody();
private:
	sf::RectangleShape body;
	sf::Texture texture;
	sf::Sprite sprite;

	void initEnemy();
};

#endif // !ENEMY_H