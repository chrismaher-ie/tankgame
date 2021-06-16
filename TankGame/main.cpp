#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tanks/Player.h"
#include "Map/Map.h"
#include "Projectiles/ProjectileHandler.h"
#include "Utils/Framerate.h"
#include "Tanks/TankHandler.h"
#include "VisualEffects/VisualEffectsHandler.h"

static const float SCREENHEIGHT = 600.0f;
static const float SCREENWIDTH =  1200.0f;

void windowEventHandler(sf::RenderWindow& window, sf::View* view);

void Draw(sf::RenderWindow& window, sf::View& view, Player& player, Map& map, TankHandler& tankHandler, Framerate& framerate, ProjectileHandler& projectileHandler, VisualEffectsHandler& vfxHandler);

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(static_cast<int>(SCREENWIDTH), static_cast<int>(SCREENHEIGHT)), "SFML Tutorial", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize, settings);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(SCREENWIDTH, SCREENHEIGHT));
	window.setFramerateLimit(144);

	VisualEffectsHandler vfxHandler = VisualEffectsHandler();

	Framerate framerate = Framerate();

	Map map = Map();

	ProjectileHandler projectileHandler = ProjectileHandler(map, vfxHandler);
	
	Player player = Player(sf::Vector2f(0.0f, 0.0f), 225.f, 0, projectileHandler, vfxHandler, window);
	
	TankHandler tankHandler = TankHandler(player, projectileHandler, vfxHandler);
	tankHandler.addTank(sf::Vector2f(130.0f, -130.0f), 0.f, GREENTANK);
	tankHandler.addTank(sf::Vector2f(-150.0f, -100.0f), 0.f, BROWNTANKTYPE);
	tankHandler.addTank(sf::Vector2f(-100.0f, -150.0f), 0.f, GREYTANK);
	tankHandler.addTank(sf::Vector2f( -75.0f,  -75.0f), 0.f, GREYTANK);
	
	sf::FloatRect boundingBox = map.getBoundingBox();
	sf::Clock clock;

	float count = 0;
	while (window.isOpen())
	{
		framerate.timer();


		windowEventHandler(window, &view);
		projectileHandler.update();
		projectileHandler.hitDetection(&player, tankHandler.getTankList());
		tankHandler.update(&player);
		player.update();
		vfxHandler.update();

		Draw(window, view, player, map, tankHandler, framerate, projectileHandler, vfxHandler);
	}

	return 0;
}

void windowEventHandler(sf::RenderWindow& window, sf::View* view) {
	sf::Event evnt;
	while (window.pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::Resized:
			view->setSize(static_cast<float>(evnt.size.width), static_cast<float>(evnt.size.height));
			break;
		case sf::Event::TextEntered:
			//do nothing
			break;
		default:
			break;
		}
	}
}

void Draw(sf::RenderWindow& window, sf::View& view, Player& player, Map& map, TankHandler& tankHandler, Framerate& framerate, ProjectileHandler& projectileHandler, VisualEffectsHandler& vfxHandler)
{
	view.setCenter(player.getPosition());
	window.setView(view);
	window.clear();

	window.draw(map);
	vfxHandler.drawBottomEffects(window);

	window.draw(player);
	window.draw(projectileHandler);
	window.draw(tankHandler);
	vfxHandler.drawTopEffects(window);

	framerate.setTextPos(window);
	window.draw(framerate);
	window.display();
}


