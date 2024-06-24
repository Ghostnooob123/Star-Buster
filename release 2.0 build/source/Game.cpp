#include "Game.h"

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initText();

}

Game::~Game()
{
	this->clearEnemies();

	delete this->player;
	this->player = nullptr;

	delete this->window;
	this->window = nullptr;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::setHighestScore() {
	int score{ 0 };

	std::ifstream inputFile("source/Highest_Score.txt");
	std::string line;
	while (std::getline(inputFile, line)) {
		score = std::stoi(line);
	}
	inputFile.close();

	this->highestScore = score;

}

void Game::updateScore() {
	/*
	  @return void
	  - Set high score to all gained points and check if there is a new high score.
	*/
	this->highestScore = this->player->getPoints();

	std::ifstream inputFile("source/Highest_Score.txt");
	if (inputFile.is_open()) {
		std::string line;
		while (std::getline(inputFile, line)) {
			if (!line.empty()) {
				int scoreFromFile = std::stoi(line);
				if (this->highestScore > static_cast<int>(scoreFromFile)) {
					std::ofstream outputFile("source/Highest_Score.txt", std::ios::trunc);
					if (outputFile.is_open()) {
						outputFile << this->highestScore << '\n';
						outputFile.close();
					}
					else {
						std::cout << "[-] Error::Game::updateScore Failed to open output file\n";
					}
				}
			}
		}
		inputFile.close();
	}
	else {
		std::cout << "[-] Error::Game::updateScore Failed to open input file\n";
	}
}


void Game::renderMenu(sf::RenderTarget& target)
{

}

int Game::checkEnemiesCollideWithWindowBorders() {
	for (const auto& row : this->enemies) {
		for (const auto& enemy : row) {
			if (enemy != nullptr) {
				float enemyLeft = enemy->getBody().getGlobalBounds().left;
				float enemyRight = enemy->getBody().getGlobalBounds().left + enemy->getBody().getGlobalBounds().width;

				if (enemyLeft <= 80.0f) {
					return -1;
				}
				if (enemyRight >= monitorX - 80.0f) {
					return 1;
				}
			}
		}
	}
	return 0;
}
void Game::generateEnemies()
{
	int shapeType = rand() % 4;

	switch (shapeType) {
	case 0:
		this->rhombusShape();
		  break;
	case 1:
		this->triangleShape();
		break;
	case 2:
		this->circleShape();
		break;
	case 3:
		this->cubeShape();
		break;
	}
 }

void Game::rhombusShape()
{
	int n = 7;
	int mid = n / 2;

	float space = 5.0f;

	float centerX = monitorX / 2.0f;
	float centerY = monitorY / 2.0f;

	float startX = centerX - (mid * (50.0f + space)) + 132.0f;
	float startY = centerY - (mid * (50.0f + space)) - 180.0f;

	clearEnemies();

	// Upper half including the middle row
	for (int i = 0; i <= mid; ++i) {
		std::list<Enemy*> row;

		for (int j = -i; j <= i; ++j) {
			float posX = startX + j * (50.0f + space);
			float posY = startY + i * (50.0f + space);
			Enemy* newEnemy = new Enemy();
			newEnemy->setCenters(posX, posY);
			row.push_back(newEnemy);
		}

		enemies.push_back(row);
	}

	// Lower half
	for (int i = mid - 1; i >= 0; --i) {
		std::list<Enemy*> row;

		for (int j = -i; j <= i; ++j) {
			float posX = startX + j * (50.0f + space);
			float posY = startY + (2 * mid - i) * (50.0f + space);
			Enemy* newEnemy = new Enemy();
			newEnemy->setCenters(posX, posY);
			row.push_back(newEnemy);
		}

		this->enemies.push_back(row);
	}
}
void Game::triangleShape()
{
	int n = 7;
	int mid = n / 2;

	float space = 5.0f;

	float centerX = monitorX / 2.0f;
	float centerY = monitorY / 2.0f;

	float startX = centerX - (mid * (50.0f + space)) + 130.0f;
	float startY = centerY - (mid * (50.0f + space)) - 180.0f;

	clearEnemies();

	// Upper half
	for (int i = 0; i <= mid; ++i) {
		std::list<Enemy*> row;

		for (int j = -i; j <= i; ++j) {
			float posX = startX + j * (50.0f + space);
			float posY = startY + i * (50.0f + space);
			Enemy* newEnemy = new Enemy();
			newEnemy->setCenters(posX, posY);
			row.push_back(newEnemy);
		}

		this->enemies.push_back(row);
	}
}
void Game::circleShape()
{
	int n = 10;
	float radius = 120.0f;
	float centerX = monitorX / 2.0f;
	float centerY = monitorY / 2.0f;

	clearEnemies();

	float angleIncrement = static_cast<float>(2 * M_PI / n);
	float currentAngle = 0.0f;

	for (int i = 0; i < n; ++i) {
		std::list<Enemy*> row;
		float posX = centerX + radius * cos(currentAngle);
		float posY = centerY + radius * sin(currentAngle) - 200.0f;

		Enemy* newEnemy = new Enemy();
		newEnemy->setCenters(posX, posY);
		row.push_back(newEnemy);

		this->enemies.push_back(row);

		currentAngle += angleIncrement;
	}
}
void Game::cubeShape()
{
	int n = 5;
	float space = 5.0f;
	float centerX = monitorX / 2.0f;
	float centerY = monitorY / 2.0f;

	clearEnemies();

	float startX = centerX - (n / 2.0f) * (50.0f + space);
	float startY = centerY - (n / 2.0f) * (50.0f + space);

	for (int i = 0; i < n; ++i) {
		std::list<Enemy*> row;

		for (int j = 0; j < n; ++j) {
			float posX = startX + j * (50.0f + space);
			float posY = startY + i * (50.0f + space) - 200.0f;
			Enemy* newEnemy = new Enemy();
			newEnemy->setCenters(posX, posY);
			row.push_back(newEnemy);
		}

		this->enemies.push_back(row);
	}
}

void Game::updateEnemies()
{
	if (std::all_of(enemies.begin(), enemies.end(), [](const std::list<Enemy*>& row) {
		return row.empty();
		})) {
		this->nextLevel = true;
	}
	else
	{
		int collision = this->checkEnemiesCollideWithWindowBorders();
		if (collision != 0) {
			this->enemyVelocityX = -this->enemyVelocityX;
		}

		for (auto& row : this->enemies) {
			for (auto& enemy : row) {
				if (enemy != nullptr) {
					enemy->setCenters(enemy->getBody().getPosition().x + this->enemyVelocityX, enemy->getBody().getPosition().y);
				}
			}
		}
	}
}
void Game::clearEnemies()
{
	// Clear previous enemies if any
	for (auto& row : enemies) {
		for (auto& enemy : row) {
			delete enemy;
		}
	}
	this->enemies.clear();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type) {
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape) {
				this->updateScore();
				this->window->close();
			}
			break;
		}
	}
}
void Game::updateMousePos()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
	this->highestScoreText.setPosition(this->centerX - 98.0f, this->centerY - 455.0f);
	this->currentScoreText.setPosition(this->centerX - 380.0f, this->centerY - 420.0f);

	this->highestScoreText.setString("HIGH SCORE\n      " + std::to_string(this->highestScore));
	std::ostringstream ss;
	ss << std::setw(2) << std::setfill('0') << this->player->getPoints();
	this->currentScoreText.setString(ss.str());
	ss.clear();
}

void Game::updateMeteors()
{
	// SPAWN
	if (this->meteorSpawnClock.getElapsedTime().asSeconds() >= this->meteorSpawnInterval) {
		sf::RectangleShape meteor;
		meteor.setFillColor(sf::Color::Green);
		meteor.setSize(sf::Vector2f(70.0f, 70.0f));

		meteor.setPosition(this->getRandomPosition());

		bool validSpawn = true;

		for (const auto& existingMeteor : this->meteors) {
			if (meteor.getGlobalBounds().intersects(existingMeteor.getGlobalBounds())) {
				validSpawn = false;
				break;
			}
		}

		if (validSpawn) {
			this->meteors.push_back(meteor);
			this->meteorSpawnClock.restart();
		}
	}

	// BOUNDS
	for (auto meteor = this->meteors.begin(); meteor != this->meteors.end(); ++meteor) {

		meteor->move(0.0f, 2.0f);

		sf::FloatRect meteorBounds = meteor->getGlobalBounds();
		if (meteorBounds.left <= 0.0f)
		{
			meteor->setPosition(0.0f, meteorBounds.top);
		}
		if (meteorBounds.left + meteorBounds.width >= monitorX)
		{
			meteor->setPosition(monitorX - meteorBounds.width, meteorBounds.top);
		}
		if (meteorBounds.top + meteorBounds.height >= monitorY) {
			meteor = this->meteors.erase(meteor);
		}

		if (this->meteors.empty())
		{
			break;
		}
	}

	for (auto meteor = this->meteors.begin(); meteor != this->meteors.end(); ++meteor)
	{
		if (meteor->getGlobalBounds().intersects(this->player->getBody().getGlobalBounds()))
		{
			meteor = this->meteors.erase(meteor);
			this->lifes.pop_back();
		}
	}
}

void Game::updateMeteor_Enemy()
{
	std::vector<sf::RectangleShape>& missiles = this->player->getMissiles();

	for (auto meteor = this->meteors.begin(); meteor != this->meteors.end(); ) {
		bool meteorRemoved = false;

		for (auto missile = missiles.begin(); missile != missiles.end();) {
			if (missile->getGlobalBounds().intersects(meteor->getGlobalBounds())) {
				missile = missiles.erase(missile);
				this->player->setPoints(10);
				meteorRemoved = true;
			}
			else {
				++missile;
			}
		}

		if (meteorRemoved) {
			meteor = this->meteors.erase(meteor);
		}
		else {
			++meteor;
		}
	}

	for (auto row = enemies.begin(); row != enemies.end(); ) {
		bool enemyRemoved = false;

		for (auto enemy = row->begin(); enemy != row->end(); ) {
			if (*enemy != nullptr) {
				bool missileHit = false;
				for (auto missile = missiles.begin(); missile != missiles.end(); ) {
					if (missile->getGlobalBounds().intersects((*enemy)->getBody().getGlobalBounds())) {
						missile = missiles.erase(missile);
						this->player->setPoints(50);
						missileHit = true;
					}
					else {
						++missile;
					}
				}

				if (missileHit) {
					delete* enemy;
					*enemy = nullptr;
					enemy = row->erase(enemy);
					enemyRemoved = true;
				}
				else {
					++enemy;
				}
			}
			else {
				++enemy;
			}
		}

		if (enemyRemoved && row->empty()) {
			row = enemies.erase(row);
		}
		else {
			++row;
		}
	}
}
void Game::updatePlayer_Enemy()
{
	this->updateEnemies();

	this->player->updatePlayerShooting();
	this->player->updatePlayerMovement();

	std::list<Enemy*> allEnemies;
	std::list<Enemy*> selectedEnemies;

	for (auto& row : enemies) {
		for (auto& enemy : row) {
			if (enemy != nullptr) {
				allEnemies.push_back(enemy);
			}
		}
	}

	if (allEnemies.empty()) {
		return;
	}

	int numEnemiesToSelect = rand() % 2 + 2;

	std::srand(static_cast<unsigned>(std::time(nullptr)));

	while (selectedEnemies.size() < numEnemiesToSelect && !allEnemies.empty()) {
		auto it = allEnemies.begin();
		std::advance(it, rand() % allEnemies.size());

		selectedEnemies.push_back(*it);
		allEnemies.erase(it);
	}
	for (auto& enemy : selectedEnemies) {
		
	}
}

void Game::updateLifes()
{
	float space = 0.0f;

	for (auto it = lifes.begin(); it != lifes.end(); ++it) {

		it->setPosition(sf::Vector2f((this->centerX - 430.0f) + space, this->centerY + 380.0f));

		space += 60.0f;
	}

	space = 0.0f;
}

void Game::update()
{
	if (this->gameLoading)
	{
		this->setHighestScore();
		this->gameLoading = false;
	}

	if (!this->lifes.empty()) {
		this->pollEvents();
		this->updateText();
		this->updateMeteors();
		this->updateMeteor_Enemy();
		this->updatePlayer_Enemy();
		this->updateLifes();
		this->updateMousePos();
	}
	else {
		this->updateScore();
		this->window->close();
	}

	if (this->nextLevel) {
		this->generateEnemies();
		this->nextLevel = false;
	}
}
void Game::render()
{
	// Clear the window
	this->window->clear(sf::Color(1, 14, 36));

	this->window->draw(this->currentScoreText);
	this->window->draw(this->highestScoreText);
	this->window->draw(this->player->renderPlayer());

	if (this->player->getAmmo())
	{
		sf::RectangleShape ammo;

		ammo.setFillColor(sf::Color(237, 192, 9));
		ammo.setSize(sf::Vector2f(15.0f, 40.0f));
		ammo.setPosition(this->centerX + 330.0f, this->centerY + 390);

		this->window->draw(ammo);
	}

	for (const auto& row : this->enemies) {
		for (const auto& elem : row) {
			if (elem != nullptr) {
				this->window->draw(elem->getBody());
			}
		}
	}

	for (const auto& meteor : this->meteors) {
		this->window->draw(meteor);
	}

	for (const auto& missile : this->player->getMissiles()) {
		this->window->draw(missile);
	}

	for (const auto& row : enemies) {
		for (const auto& enemy : row) {
			if (enemy != nullptr) {
				const std::vector<sf::RectangleShape>& missiles = enemy->getMissiles();
				for (const auto& missile : missiles) {
					this->window->draw(missile);
				}
			}
		}
	}

	for (const auto& life : lifes) {
		this->window->draw(life);
	}

	// Display everything
	this->window->display();
}

sf::Vector2f Game::getRandomPosition()
{
	float x = static_cast<float>(rand() % (this->window->getSize().x));
	float y = 0.0f;

	return sf::Vector2f(x, y);
}

void Game::initVariables()
{
	this->window = nullptr;

	this->centerX = 0.0f;
	this->centerY = 0.0f;

	this->highestScore = 0;
	this->gameLoading = true;

	this->meteorCount = 3;
	this->meteorSpawnInterval = 5.0f;

	this->enemyVelocityX = 1.5f;

	this->nextLevel = true;

	srand(static_cast<unsigned>(time(nullptr)));

	this->player = new Player();
	this->lifes = { player->getBody(), player->getBody(), player->getBody() };

	for (auto& row : this->enemies) {
		for (auto& elem : row) {
			delete elem;
		}
	}
	this->enemies.clear();
}
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(monitorX, monitorY), "Star Buster", sf::Style::Titlebar);

	this->window->setFramerateLimit(60);

	//Center of the screen
	this->centerX = static_cast<float> (monitorX / 2);
	this->centerY = static_cast<float> (monitorY / 2);

	this->player->setCenters(this->centerX, this->centerY);
}
void Game::initText()
{
	if (!this->gameFont.loadFromFile("source/PixellettersFull.ttf")) {
		std::cout << "[-] Error::Game::initFonts Failed to load the font\n";
	}

	this->highestScoreText.setFont(this->gameFont);
	this->highestScoreText.setCharacterSize(40);
	this->highestScoreText.setFillColor(sf::Color(199, 198, 197));

	this->currentScoreText.setFont(this->gameFont);
	this->currentScoreText.setCharacterSize(40);
	this->currentScoreText.setFillColor(sf::Color(199, 198, 197));

}