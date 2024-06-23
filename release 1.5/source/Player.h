#ifndef Player_H
#define Player_H

#include <iostream>
#include <vector>

#include <WindowConfig.h>

#include <SFML/Graphics.hpp>

class Player {
public:

	Player();
	~Player();

	int getPoints();
	int getArmor();
	bool getAmmo();

	std::vector<sf::RectangleShape>& getMissiles();
	void removeMissile(std::vector<sf::RectangleShape>::iterator missile);

	void setPoints();
	void setArmor(int& newArmor);

	sf::Vector2f getPlayerPosition();
	void setPlayerPosition(sf::Vector2f& newPosition);

	void setCenters(float& centerX, float& centerY);

	sf::RectangleShape getBody();

	sf::RectangleShape renderPlayer();

	void updatePlayerMovement();
	void updatePlayerShooting();

private:
	int points;

	int armor;

	int damage;

	float centerX;
	float centerY;

	bool spaceKeyPreviouslyPressed;
	bool haveAmmo;

	sf::Clock shootSpawnClock;
	float shootSpawnInterval;

	sf::Vector2i screenResolution;

	sf::FloatRect playerBounds;
	sf::FloatRect backgroundBounds;

	std::vector<sf::RectangleShape> missiles;

	sf::RectangleShape body;
	sf::Texture texture;
	sf::Sprite sprite;

	void initPlayer();
};

#endif // !Player_H