#pragma once
#include "Utility.h"

class Snake : public sf::Drawable
{
public:
	Snake(unsigned int initialSize);
public:
	bool bHasEatenFood;
public:
	void move();
	void changeDirection(EDirection newDirection);
	void increaseSpeed();
public:
	sf::RectangleShape getHead() const;
	sf::RectangleShape getBodyPart(int index) const;
	std::vector<sf::RectangleShape> getBody() const;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<sf::RectangleShape> m_body;
	EDirection m_direction;
	EDirection m_nextFrameDirection;
	sf::Clock m_moveClock;
	sf::Time m_elapsed;
	float m_frameDuration;
	float m_accumulatedTime;
	bool bCanMove;
};

