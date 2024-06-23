#include <background.h>

Background::Background()
{
	this->initBackground();
}

Background::~Background()
{
}

sf::RectangleShape Background::getBackground()
{
	return this->background;
}

void Background::initBackground()
{
	this->screenResolution = getScreenResolution();

	this->background.setFillColor(sf::Color::Black);
	this->background.setSize(sf::Vector2f(static_cast<float>(this->screenResolution.x / 2), static_cast<float>(this->screenResolution.y)));
	this->background.setPosition(sf::Vector2f(static_cast<float>(this->screenResolution.x / 2) / 2, 0.0f));
}