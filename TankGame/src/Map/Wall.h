#pragma once
#include <SFML/Graphics.hpp>

class Wall : public sf::Drawable
{
public:
	Wall(sf::Vector2f pos, float width, float height, bool fragile, sf::Texture& texture);
	~Wall();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool isFragile();
	sf::Sprite getSprite();

private:

	bool fragile;
	sf::Sprite body;
};

