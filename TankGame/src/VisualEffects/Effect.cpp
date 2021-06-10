#include "Effect.h"

Effect::Effect()
{
}

Effect::~Effect()
{
}

void Effect::update()
{
	//To be implemented by child classes
}

void Effect::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(body);
}

bool Effect::shouldDelete()
{
	return expired;
}
