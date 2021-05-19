#pragma once
#include <SFML/Graphics.hpp>

class Map
{
	public:
		Map();
		~Map();
		void draw(sf::RenderWindow& window);

	private:
		sf::RectangleShape map;
		sf::Texture mapTexture;
};

