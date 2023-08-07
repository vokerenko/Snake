#pragma once
#include "Snake.h"
#include "Menu.h"

class Game
{
public:
	// Constructors
	Game();

public:
	void update();
	void render();

public:
	bool isRunning() const { return m_window.isOpen(); };

private:
	void restart();
	void showDeathMenu();
private:
	sf::VideoMode m_videoMode;
	sf::RenderWindow m_window;
	sf::Event m_event;
	sf::Clock m_clock;
	sf::RectangleShape m_wall;
	sf::RectangleShape m_food;
	int m_score;

	Snake m_snake;
	bool m_bPaused;
	float m_dt;
	Menu m_menu;

private:
	void handleEvents();
	void initWall(const sf::Color color, float thickness);
	void spawnFood();
	void checkFood();
	void checkSnakeDeath();
};


