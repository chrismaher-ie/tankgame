#pragma once
#include <SFML/Graphics.hpp>

class Effect : public sf::Drawable
{
public:

	Effect();
	virtual ~Effect();

	virtual void update(); 
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool shouldDelete();

protected:

	sf::RectangleShape body;
	
	bool expired = false;
};

