#include "stdafx.h"
#include "Snake.h"

Snake::Snake(unsigned int initialSize)
	: m_direction{ EDirection::Right }
	, m_nextFrameDirection{ m_direction }
	, m_accumulatedTime{ 0.0f }
	, bCanMove{ true }
	, bHasEatenFood{ false }
	, m_frameDuration{ Constants::FrameTime }
{
	for (unsigned int i = 0; i < initialSize; i++)
	{
		sf::RectangleShape bodyPart = sf::RectangleShape(sf::Vector2f(Constants::RectSize, Constants::RectSize));
		bodyPart.setFillColor(Constants::SnakeColor);
		bodyPart.setPosition(Constants::WindowCenter - sf::Vector2f(Constants::RectSize * i, 0.0f));
		m_body.push_back(bodyPart);
	}
}

void Snake::move()
{
	m_elapsed = m_moveClock.restart();
	m_accumulatedTime += m_elapsed.asSeconds();
	if (m_accumulatedTime >= m_frameDuration) {
		bCanMove = true;
		m_accumulatedTime = 0.0f;
	}

	if (bCanMove)
	{
		m_direction = m_nextFrameDirection;
		if (!bHasEatenFood)
		{
			m_body.pop_back();
		}
		bHasEatenFood = false;
		sf::RectangleShape newHead = sf::RectangleShape(sf::Vector2f(Constants::RectSize, Constants::RectSize));
		newHead.setFillColor(Constants::SnakeColor);
		switch (m_direction)
		{
		case EDirection::Right:
			newHead.setPosition(m_body.front().getPosition() + sf::Vector2f(Constants::SnakeSpeed, 0.0f));
			break;
		case EDirection::Down:
			newHead.setPosition(m_body.front().getPosition() + sf::Vector2f(0.0f, Constants::SnakeSpeed));
			break;
		case EDirection::Left:
			newHead.setPosition(m_body.front().getPosition() - sf::Vector2f(Constants::SnakeSpeed, 0.0f));
			break;
		case EDirection::Up:
			newHead.setPosition(m_body.front().getPosition() - sf::Vector2f(0.0f, Constants::SnakeSpeed));
			break;
		default:
			break;
		}

		m_body.insert(m_body.begin(), newHead);
		bCanMove = false;
	}
}

void Snake::changeDirection(EDirection newDirection)
{
	if (static_cast<int>(m_direction) != static_cast<int>(newDirection) + 2
		&& static_cast<int>(m_direction) != static_cast<int>(newDirection) - 2)
	{
		m_nextFrameDirection = newDirection;
	}
}

void Snake::increaseSpeed()
{
	m_frameDuration *= 0.99f;
}


sf::RectangleShape Snake::getHead() const
{
	return m_body.front();
}

sf::RectangleShape Snake::getBodyPart(int index) const
{
	return m_body.at(index);
}

std::vector<sf::RectangleShape> Snake::getBody() const
{
	return m_body;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const sf::RectangleShape& bodyPart : m_body)
	{
		target.draw(bodyPart, states);
	}

}