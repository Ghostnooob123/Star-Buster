#include "WindowConfig.h"

sf::Vector2i getScreenResolution() {
	sf::Vector2i resolution;
#ifdef _WIN32
	resolution.x = GetSystemMetrics(SM_CXSCREEN);
	resolution.y = GetSystemMetrics(SM_CYSCREEN);
#else
	// Default to some resolution if not on Windows, or retrieve it using X11
	resolution.x = 1920; // Default width
	resolution.y = 1080; // Default height
#endif
	return resolution;
}
