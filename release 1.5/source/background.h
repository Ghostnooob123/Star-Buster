#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

#include <WindowConfig.h>

class Background {
public:
	Background();
	~Background();

	sf::RectangleShape getBackground();
private:

	sf::RectangleShape background;
	sf::Vector2i screenResolution;

	void initBackground();

};
#endif // !BACKGROUND_H
