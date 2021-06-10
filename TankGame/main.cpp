#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tanks/Player.h"
#include "Map/Map.h"
#include "Projectiles/ProjectileHandler.h"
#include "Utils/Framerate.h"
#include "Tanks/EnemyHandler.h"

static const float SCREENHEIGHT = 600.0f;
static const float SCREENWIDTH =  1200.0f;

void windowEventHandler(sf::RenderWindow& window, sf::View* view);

void Draw(sf::RenderWindow& window, sf::View& view, Player& player, Map& map, EnemyHandler& enemyHandler, Framerate& framerate, ProjectileHandler& projectileHandler);

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(static_cast<int>(SCREENWIDTH), static_cast<int>(SCREENHEIGHT)), "SFML Tutorial", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize, settings);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(SCREENWIDTH, SCREENHEIGHT));
	window.setFramerateLimit(144);
	Framerate framerate = Framerate();

	Map map = Map();

	ProjectileHandler projectileHandler = ProjectileHandler(map);

	Player player = Player(sf::Vector2f(0.0f, 0.0f), 225.f, 0, projectileHandler, window);
	
	EnemyHandler eHandler = EnemyHandler(player, projectileHandler);
	eHandler.addEnemy(sf::Vector2f(130.0f, -130.0f), 0.f, GREENTANK);
	eHandler.addEnemy(sf::Vector2f(-150.0f, -100.0f), 0.f, BROWNTANKTYPE);
	eHandler.addEnemy(sf::Vector2f(-100.0f, -150.0f), 0.f, GREYTANK);
	eHandler.addEnemy(sf::Vector2f( -75.0f,  -75.0f), 0.f, GREYTANK);
	
	sf::FloatRect boundingBox = map.getBoundingBox();
	sf::Clock clock;

	float count = 0;
	while (window.isOpen())
	{
		framerate.timer();


		windowEventHandler(window, &view);
		projectileHandler.update();
		projectileHandler.hitDetection(&player, eHandler.getTankList());
		eHandler.update(&player);
		player.update();

		Draw(window, view, player, map, eHandler, framerate, projectileHandler);
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

void Draw(sf::RenderWindow& window, sf::View& view, Player& player, Map& map, EnemyHandler& enemyHandler, Framerate& framerate, ProjectileHandler& projectileHandler)
{
	view.setCenter(player.getPosition());
	window.setView(view);
	window.clear();

	window.draw(map);
	window.draw(player);
	window.draw(projectileHandler);
	window.draw(enemyHandler);

	framerate.setTextPos(window);
	window.draw(framerate);
	window.display();
}


