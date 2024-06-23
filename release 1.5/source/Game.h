#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <ctime>

#include <Player.h>
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

	void pollEvents();
	void updateMousePos();

	void updateText();
	void updateMeteors();

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

	int highestScore;
	bool gameLoading;

	sf::Clock meteorSpawnClock;
	float meteorSpawnInterval;

	sf::Vector2i screenResolution;

	Player* player;
	sf::FloatRect backgroundBounds;

	std::list<sf::RectangleShape> lifes;

	std::list<sf::RectangleShape> meteors;
	size_t meteorCount = 3;

	//Init
	void initVariables();
	void initWindow();
	void initText();

};
#endif // !GAME_H