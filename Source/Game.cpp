#include "stdafx.h"
#include "Utility.h"
#include "Snake.h"
#include "Menu.h"
#include "Game.h"


Game::Game()
	: m_videoMode{ Constants::WindowWidth, Constants::WindowHeight }
	, m_window{ m_videoMode, "Snake" }
	, m_dt{ m_clock.restart().asSeconds() }
	, m_wall{ sf::RectangleShape(sf::Vector2f(m_window.getSize())) }
	, m_snake{ Constants::SnakeInitialLength }
	, m_score{ 0 }
	, m_bPaused{ true }
	, m_menu{ EMenuTypes::Start, m_score }

{
	initWall(Constants::WallColor, Constants::RectSize);
	spawnFood();
}


void Game::initWall(const sf::Color color, float thickness)
{
	m_wall.setFillColor(sf::Color::Transparent);
	m_wall.setOutlineColor(color);
	m_wall.setOutlineThickness(-thickness);
}

void Game::spawnFood()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	int minNumber = 1;
	int maxNumber = (Constants::WindowWidth - Constants::RectSize * 2) / Constants::RectSize;
	std::uniform_int_distribution<> dis(minNumber, maxNumber);
	int randomX = dis(gen);
	int randomY = dis(gen);
	std::vector<sf::Vector2f> snakePositions;
	for (const sf::RectangleShape& bodyPart : m_snake.getBody())
	{
		snakePositions.push_back(bodyPart.getPosition() / static_cast<float>(Constants::RectSize));
	}
	std::vector<sf::Vector2f>::iterator it;
	do
	{
		it = std::find(snakePositions.begin(), snakePositions.end(), sf::Vector2f(randomX, randomY));
		if (it != snakePositions.end())
		{
			randomX = dis(gen);
			randomY = dis(gen);
		}
	} while (it != snakePositions.end());
	m_food = sf::RectangleShape(sf::Vector2f(Constants::RectSize, Constants::RectSize));
	m_food.setFillColor(sf::Color::Yellow);
	m_food.setPosition(sf::Vector2f(randomX, randomY) * static_cast<float>(Constants::RectSize));

}

void Game::checkFood()
{
	if (m_snake.getHead().getPosition() == m_food.getPosition())
	{
		spawnFood();
		m_snake.bHasEatenFood = true;
		m_snake.increaseSpeed();
		m_score++;
	}
}

void Game::checkSnakeDeath()
{
	for (size_t i = 1; i < m_snake.getBody().size(); i++)
	{
		if (m_snake.getHead().getPosition() == m_snake.getBodyPart(i).getPosition())
		{
			showDeathMenu();
		}
	}
	if (m_snake.getHead().getPosition().x <= 0.0f || m_snake.getHead().getPosition().y <= 0.0f
		|| m_snake.getHead().getPosition().x >= Constants::WindowWidth - Constants::RectSize
		|| m_snake.getHead().getPosition().y >= Constants::WindowHeight - Constants::RectSize)
	{
		showDeathMenu();
	}


}

void Game::update()
{
	m_dt = m_clock.restart().asSeconds();
	handleEvents();
	sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
	sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
	for (size_t i = 0; i < m_menu.getButtonCount(); i++)
	{
		if (m_menu.getButtonBounds(i).contains(mousePositionF))
		{
			switch (m_menu.getButtonType(i))
			{
			case EMenuButtons::Start:
			{
				m_menu.hoverOver(i, true);
				break;
			}
			case EMenuButtons::Exit:
			{
				m_menu.hoverOver(i, true);
				break;
			}
			default:
				continue;
			}
		}
		else
		{
			m_menu.hoverOver(i, false);
		}
	}
	if (!m_bPaused)
	{
		m_snake.move();
		checkFood();
		m_menu = Menu(EMenuTypes::NotPaused, m_score);
		checkSnakeDeath();


	}

}

void Game::render()
{

	m_window.clear();

	m_window.draw(m_snake);
	m_window.draw(m_wall);
	m_window.draw(m_food);
	m_window.draw(m_menu);
	m_window.display();
}

void Game::restart()
{
	m_snake = Snake(Constants::SnakeInitialLength);
	m_bPaused = false;
	if (m_menu.getType() != EMenuTypes::Start)
	{
		spawnFood();
	}
	m_score = 0;
}

void Game::showDeathMenu()
{
	m_bPaused = true;
	m_menu = Menu(EMenuTypes::Death, m_score);
}

void Game::handleEvents() {
	while (m_window.pollEvent(m_event))
	{
		switch (m_event.type)
		{
		case sf::Event::Closed:
		{
			m_window.close();
			break;
		}
		case sf::Event::MouseButtonReleased:
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
			sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
			for (size_t i = 0; i < m_menu.getButtonCount(); i++)
			{
				if (m_menu.getButtonBounds(i).contains(mousePositionF))
				{
					switch (m_menu.getButtonType(i))
					{
					case EMenuButtons::Start:
					{
						restart();
						break;
					}
					case EMenuButtons::Exit:
					{
						m_window.close();
						break;
					}
					default:
						continue;
					}
				}
			}
			break;
		}
		default:
			continue;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_window.close();
	}
	for (const auto& [key, direction] : Input::keyToDirection) {
		if (sf::Keyboard::isKeyPressed(key)) {
			m_snake.changeDirection(direction);
			break;
		}
	}


}
