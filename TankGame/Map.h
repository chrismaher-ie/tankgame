#pragma once
#include <SFML/Graphics.hpp>

class Map : public sf::Drawable
{
	public:
		Map();
		~Map();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		sf::FloatRect getBoundingBox();
	private:
		sf::RectangleShape map;
		sf::Texture mapTexture;
};

