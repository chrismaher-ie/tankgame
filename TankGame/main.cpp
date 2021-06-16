#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map/Map.h"
#include "Projectiles/ProjectileHandler.h"
#include "Utils/Framerate.h"
#include "Tanks/TankHandler.h"
#include "VisualEffects/VisualEffectsHandler.h"

static const unsigned int SCREENHEIGHT = 640;
static const unsigned int SCREENWIDTH =  1040;

void windowEventHandler(sf::RenderWindow& window, sf::View& view);

void Draw(sf::RenderWindow& window, sf::View& view, Map& map, TankHandler& tankHandler, Framerate& framerate, ProjectileHandler& projectileHandler, VisualEffectsHandler& vfxHandler);

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "SFML Tutorial", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize, settings);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(static_cast<float>(SCREENWIDTH), static_cast<float>(SCREENHEIGHT)));
	window.setFramerateLimit(144);

	VisualEffectsHandler vfxHandler = VisualEffectsHandler();

	Framerate framerate = Framerate();
	framerate.setTextPos(window);

	Map map = Map();

	ProjectileHandler projectileHandler = ProjectileHandler(map, vfxHandler);
	
	TankHandler tankHandler = TankHandler(projectileHandler, vfxHandler, window);
	projectileHandler.setTankHandler(tankHandler);
	
	tankHandler.addTank(sf::Vector2f(130.0f, -130.0f), 0.f, GREENTANK);
	tankHandler.addTank(sf::Vector2f(-150.0f, -100.0f), 0.f, BROWNTANK);
	tankHandler.addTank(sf::Vector2f(-100.0f, -150.0f), 0.f, GREYTANK);
	tankHandler.addTank(sf::Vector2f( -75.0f,  -75.0f), 0.f, GREYTANK);
	
	sf::FloatRect boundingBox = map.getBoundingBox();
	sf::Clock clock;

	float count = 0;
	while (window.isOpen())
	{
		framerate.timer();


		windowEventHandler(window, view);
		projectileHandler.update();
		projectileHandler.hitDetection();
		tankHandler.update();
		vfxHandler.update();

		Draw(window, view, map, tankHandler, framerate, projectileHandler, vfxHandler);
	}

	return 0;
}

void windowEventHandler(sf::RenderWindow& window, sf::View& view) {
	sf::Event evnt;
	unsigned int xSize, ySize;
	while (window.pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::Resized:
			xSize = evnt.size.width > SCREENWIDTH ? evnt.size.width : SCREENWIDTH;
			ySize = evnt.size.height > SCREENHEIGHT ? evnt.size.height : SCREENHEIGHT;
			window.setSize(sf::Vector2u(xSize, ySize));
			view.setSize(static_cast<float>(xSize), static_cast<float>(ySize));
			break;
		case sf::Event::TextEntered:
			//do nothing
			break;
		default:
			break;
		}
	}
}

void Draw(sf::RenderWindow& window, sf::View& view, Map& map, TankHandler& tankHandler, Framerate& framerate, ProjectileHandler& projectileHandler, VisualEffectsHandler& vfxHandler)
{
	window.setView(view);
	window.clear();

	window.draw(map);
	vfxHandler.drawBottomEffects(window);

	window.draw(projectileHandler);
	window.draw(tankHandler);
	vfxHandler.drawTopEffects(window);

	window.draw(framerate);
	window.display();
}


