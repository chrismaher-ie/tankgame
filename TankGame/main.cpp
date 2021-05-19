#include <SFML/Graphics.hpp>
#include <iostream>

static const float SCREENHEIGHT = 512.0f;
static const float SCREENWIDTH =  512.0f;

# define M_PI           3.14159265358979323846f

void ResizeView(const sf::RenderWindow& window, sf::View& view) {


}

float GetAngle(sf::Vector2f v1, sf::Vector2f v2) {
	//printf(" v1 : %f, %f :: v2 : %f, %f \n", v1.x, v1.y, v2.x, v2.y);

	float angle = std::atan2f(v2.y - v1.y, v2.x - v1.x) * 180 / M_PI;
	printf(" Angle : %f \n", angle);
	return angle;
	
}

void GoForward(sf::RectangleShape& thing) {
	float angle = thing.getRotation() / 180.f * M_PI;
	thing.move(0.05f * std::cosf(angle), 0.05f * std::sinf(angle));
}
void GoBackwards(sf::RectangleShape& thing) {
	float angle = thing.getRotation() / 180.f * M_PI;
	thing.move(-0.05f * std::cosf(angle), -0.05f * std::sinf(angle));
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(static_cast<int>(SCREENHEIGHT), static_cast<int>(SCREENWIDTH)), "SFML Tutorial", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(SCREENHEIGHT, SCREENHEIGHT));
	sf::RectangleShape player(sf::Vector2f(40.0f,40.0f));
	sf::RectangleShape turret(sf::Vector2f(40.0f,40.0f));
	sf::RectangleShape map(sf::Vector2f(1200.f, 2000.f));

	player.setPosition(100.0f, 100.0f);
	player.setOrigin(20.0f, 20.0f);

	turret.setPosition(50.f, 50.f);
	turret.setOrigin(20.0f, 20.0f);

	map.setPosition(0.f, 0.f);
	map.setOrigin(600.0f, 1200.0f);

	sf::Texture playerTexture;
	playerTexture.loadFromFile("Textures/tankBase.png");
	player.setTexture(&playerTexture);


	sf::Texture turretTexture;
	turretTexture.loadFromFile("Textures/tankTurret.png");
	turret.setTexture(&turretTexture);

	sf::Texture mapTexture;
	mapTexture.loadFromFile("Textures/road.jpg");
	map.setTexture(&mapTexture);

	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				view.setSize(evnt.size.width, evnt.size.height);
				break;
			case sf::Event::TextEntered:
				//do nothing
				break;

			default:
				break;
			}

				
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			player.rotate(-0.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			player.rotate(0.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			GoForward(player);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			GoBackwards(player);
		}

		/*
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			player.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
		}
		*/
		
		//GetAngle(turret.getPosition(), player.getPosition())
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
		turret.setRotation(GetAngle(turret.getPosition(), worldPos));
		
		turret.setPosition(player.getPosition());
		view.setCenter(player.getPosition());
		window.setView(view);
		window.clear();
		window.draw(map);
		window.draw(player);
		window.draw(turret);
		window.display();
	}

	return 0;
}