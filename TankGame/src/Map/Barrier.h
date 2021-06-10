#pragma once
#include <SFML/Graphics.hpp>

class Barrier : public sf::Drawable
{
public:
	Barrier(sf::Vector2f pos, float width, float height, bool fragile, sf::Texture& texture);
	~Barrier();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool isFragile();
	sf::RectangleShape getBody();

private:

	bool fragile;
	sf::RectangleShape body;

};

