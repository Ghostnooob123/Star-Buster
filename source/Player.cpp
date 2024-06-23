#include "Player.h"

Player::Player()
{
	this->initPlayer();
}

Player::~Player()
{

}

int Player::getPoints() {
	return this->points;
}
int Player::getArmor() {
	return this->armor;
}
bool Player::getAmmo()
{
	return this->haveAmmo;
}

std::vector<sf::RectangleShape>& Player::getMissiles()
{
	return this->missiles;
}
void Player::removeMissile(std::vector<sf::RectangleShape>::iterator missile)
{
	this->missiles.erase(missile);
}

void Player::setPoints() {
	this->points += 10;
}
void Player::setArmor(int& newArmor) {
	this->armor = newArmor;
}

sf::Vector2f Player::getPlayerPosition()
{
	return this->body.getPosition();
}
void Player::setPlayerPosition(sf::Vector2f& newPosition)
{
	this->body.setPosition(newPosition);
}

void Player::setCenters(float& centerX, float& centerY)
{
	this->centerX = centerX;
	this->centerY = centerY;

	this->body.setPosition(sf::Vector2f(this->centerX - 30.0f, this->centerY + 300.0f));
}

sf::RectangleShape Player::getBody()
{
	return this->body;
}

sf::RectangleShape Player::renderPlayer()
{
	return this->body;
}

void Player::updatePlayerMovement()
{
	// A and D
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->body.move(sf::Vector2f(-5.5f, 0.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->body.move(sf::Vector2f(5.5f, 0.0f));
	}
	// LEFT and RIGHT arrows
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->body.move(sf::Vector2f(-5.5f, 0.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->body.move(sf::Vector2f(5.5f, 0.0f));
	}

	// Player bounds
	sf::FloatRect playerBounds = this->body.getGlobalBounds();
	if (playerBounds.left <= 0.0f)
	{
		this->body.setPosition(0.0f, playerBounds.top);
	}
	if (playerBounds.left + playerBounds.width >= monitorX)
	{
		this->body.setPosition(monitorX - playerBounds.width, playerBounds.top);
	}
}

void Player::updatePlayerShooting()
{
	if (this->shootSpawnClock.getElapsedTime().asSeconds() >= this->shootSpawnInterval)
	{
		this->haveAmmo = true;
	}

	// SPACE_BAR
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (!this->spaceKeyPreviouslyPressed && this->shootSpawnClock.getElapsedTime().asSeconds() >= this->shootSpawnInterval) {
			sf::RectangleShape newMissile;

			newMissile.setFillColor(sf::Color(237, 192, 9));
			newMissile.setSize(sf::Vector2f(5.0f, 20.0f));
			newMissile.setPosition(this->body.getPosition().x + this->body.getSize().x / 2 - 5.0f, this->body.getPosition().y);

			this->missiles.push_back(newMissile);

			this->spaceKeyPreviouslyPressed = true;

			this->haveAmmo = false;

			shootSpawnClock.restart();
		}
	}
	else {
		this->spaceKeyPreviouslyPressed = false;
	}

	for (size_t i = 0; i < this->missiles.size(); )
	{
		this->missiles[i].move(0.0f, -7.0f);
		if (this->missiles[i].getPosition().y + this->missiles[i].getSize().y < 0)
		{
			this->missiles.erase(this->missiles.begin() + i);
		}
		else
		{
			++i;
		}
	}
}

void Player::initPlayer()
{
	this->points = 00;

	this->armor = 0;

	this->damage = 5;

	this->centerX = 0.0f;
	this->centerY = 0.0f;

	this->shootSpawnInterval = 1.3f;

	this->spaceKeyPreviouslyPressed = false;
	this->haveAmmo = false;

	this->screenResolution = getScreenResolution();

	this->body.setFillColor(sf::Color::Green);
	this->body.setSize(sf::Vector2f(50.0f, 50.0f));

	/*if (!this->texture.loadFromFile("image.png"))
	{
		std::cout << "[-] Error loading the textures for Player!";
	}*/


	this->sprite.setTexture(this->texture);
}