#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Map/Wall.h"
#include "Map/Barrier.h"


class Map : public sf::Drawable
{
	public:
		Map();
		~Map();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		sf::FloatRect getBoundingBox();

		void addWall(sf::Vector2f pos, float height, float width, bool fragile);
		void addBarrier(sf::Vector2f pos, float height, float width, bool fragile);

		std::list<Wall> *getWallList();
		std::list<Barrier> *getBarrierList();
	private:
		
		sf::RectangleShape background;

		sf::Texture backgroundTexture;
		sf::Texture wallTexture;
		sf::Texture fragileWallTexture;
		sf::Texture barrierTexture;
		sf::Texture fragileBarrierTexture;

		std::list<Wall> wallList;
		std::list<Barrier> barrierList;
};

