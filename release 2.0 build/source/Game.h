#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <ctime>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <Player.h>
#include <Enemy.h>
#include <WindowConfig.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

class Game final {
public:

	Game();
	~Game();

	const bool running() const;
	void setHighestScore();

	void renderMenu(sf::RenderTarget& target);

	int checkEnemiesCollideWithWindowBorders();
	void generateEnemies();
	void rhombusShape();
	void triangleShape();
	void circleShape();
	void cubeShape();

	void updateEnemies();
	void clearEnemies();

	void pollEvents();
	void updateMousePos();

	void updateText();
	void updateMeteors();

	void updateMeteor_Enemy();
	void updatePlayer_Enemy();

	void updateLifes();

	void update();
	void render();

	void updateScore();

	sf::Vector2f getRandomPosition();

private:
	//Variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	sf::Font gameFont;
	sf::Text highestScoreText;
	sf::Text currentScoreText;

	float centerX;
	float centerY;

	float enemyVelocityX;

	int highestScore;
	bool gameLoading;
	bool nextLevel;

	sf::Clock shootSpawnClock;
	float shootSpawnInterval = 5.0f;

	sf::Clock meteorSpawnClock;
	float meteorSpawnInterval;

	sf::Vector2i screenResolution;

	Player* player;

	std::list<sf::RectangleShape> lifes;

	std::list<sf::RectangleShape> meteors;
	size_t meteorCount;

	std::list<std::list<Enemy*> > enemies;

	//Init
	void initVariables();
	void initWindow();
	void initText();

};
#endif // !GAME_H