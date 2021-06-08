#pragma once
#include <SFML/Graphics.hpp>

class Wall : public sf::Drawable
{
public:
	Wall(sf::Vector2f pos, float height, float width, bool fragile, sf::Texture& texture);
	~Wall();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool isFragile();
	sf::RectangleShape getBody();

private:

	bool fragile;
	sf::RectangleShape body;
};

