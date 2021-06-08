#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Wall.h"


class Map : public sf::Drawable
{
	public:
		Map();
		~Map();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		sf::FloatRect getBoundingBox();

		void addWall(sf::Vector2f pos, float height, float width, bool fragile);
		std::list<Wall> *getWallList();
	private:
		sf::RectangleShape background;
		sf::Texture backgroundTexture;

		sf::Texture wallTexture;
		sf::Texture fragileWallTexture;


		std::list<Wall> wallList;
};

