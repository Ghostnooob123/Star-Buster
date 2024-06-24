#ifndef WINDOW_CONFIG_H
#define WINDOW_CONFIG_H

#include <SFML/Graphics.hpp>

#ifdef _WIN32
#include <windows.h>

const int monitorX = 900;
const int monitorY = 900;

sf::Vector2i getScreenResolution();
#endif //_WIN32

#endif // !WINDOW_CONFIG_H
