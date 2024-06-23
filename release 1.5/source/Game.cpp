#include "Game.h"

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initText();

}

Game::~Game()
{
	delete this->window;
	this->window = nullptr;

	delete this->player;
	this->player = nullptr;
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
		meteor.setSize(sf::Vector2f(80.0f, 80.0f));

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

	std::vector<sf::RectangleShape>& missiles = this->player->getMissiles();
	for (auto meteor = this->meteors.begin(); meteor != this->meteors.end(); ++meteor)
	{
		for (auto missile = missiles.begin(); missile != missiles.end(); ++missile)
		{
			if (missile->getGlobalBounds().intersects(meteor->getGlobalBounds())) {
				meteor = this->meteors.erase(meteor);
				this->player->removeMissile(missile);

				this->player->setPoints();
				break;
			}
		}

		if (this->meteors.empty() && missiles.empty())
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

void Game::update()
{
	if (this->lifes.empty())
	{
		this->window->close();
	}

	if (this->gameLoading)
	{
		this->setHighestScore();
		this->gameLoading = false;
	}

	this->pollEvents();
	this->updateText();

	this->updateMeteors();

	this->player->updatePlayerShooting();
	this->player->updatePlayerMovement();

	float space = 0.0f;

	for (auto it = lifes.begin(); it != lifes.end(); ++it) {

		it->setPosition(sf::Vector2f((this->centerX - 430.0f) + space, this->centerY + 380.0f));

		space += 75.0f;
	}

	space = 0.0f;

	this->updateMousePos();
}

void Game::render()
{
	this->window->clear(sf::Color(1, 14, 36));

	//this->window->draw(this->background.getBackground());

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

	for (auto it = this->meteors.begin(); it != this->meteors.end(); ++it) {

		this->window->draw(*it);
	}

	std::vector<sf::RectangleShape> missiles = this->player->getMissiles();
	for (auto it = missiles.begin(); it != missiles.end(); ++it) {

		this->window->draw(*it);
	}

	for (auto it = lifes.begin(); it != lifes.end(); ++it) {

		this->window->draw(*it);
	}

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

	this->meteorSpawnInterval = 3.0f;

	srand(static_cast<unsigned>(time(nullptr)));

	this->player = new Player();
	this->lifes = { player->getBody(), player->getBody(), player->getBody() };
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
	this->highestScoreText.setPosition(this->centerX - 100.0f, this->centerY - 460.0f);

	this->currentScoreText.setFont(this->gameFont);
	this->currentScoreText.setCharacterSize(40);
	this->currentScoreText.setFillColor(sf::Color(199, 198, 197));
	this->currentScoreText.setPosition(this->centerX - 380.0f, this->centerY - 425.0f);
}