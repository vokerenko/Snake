#include "stdafx.h"
#include "Menu.h"


Menu::Menu(EMenuTypes type, unsigned int score)
	: m_score(score)
	, m_type(type)
{
	if (!m_font.loadFromFile("Resourses/Fonts/arial.ttf"))
	{
		std::cout << "bad" << std::endl;
	}
	switch (type)
	{
	case EMenuTypes::Start:
	{
		m_strings.push_back("Snake");
		m_strings.push_back("Press Start to begin");
		sf::RectangleShape startButton = sf::RectangleShape(sf::Vector2f(300.0f, 120.0f));
		sf::RectangleShape exitButton = sf::RectangleShape(sf::Vector2f(300.0f, 120.0f));
		startButton.setFillColor(sf::Color(200.0f, 30.0f, 0.0f, 150.0f));
		startButton.setPosition(sf::Vector2f(300.0f, 300.0f));
		exitButton.setFillColor(sf::Color(200.0f, 30.0f, 0.0f, 150.0f));
		exitButton.setPosition(sf::Vector2f(300.0f, 500.0f));
		m_buttons.push_back(startButton);
		m_buttons.push_back(exitButton);

		m_buttonStrings.push_back("Start");
		m_buttonStrings.push_back("Exit");
		break;
	}
	case EMenuTypes::Death:
	{
		m_strings.push_back("You died :(");
		m_strings.push_back("Score: " + std::to_string(m_score));
		sf::RectangleShape restartButton = sf::RectangleShape(sf::Vector2f(300.0f, 120.0f));
		sf::RectangleShape exitButton = sf::RectangleShape(sf::Vector2f(300.0f, 120.0f));
		restartButton.setFillColor(sf::Color(200.0f, 30.0f, 0.0f, 150.0f));
		restartButton.setPosition(sf::Vector2f(300.0f, 300.0f));
		exitButton.setFillColor(sf::Color(200.0f, 30.0f, 0.0f, 150.0f));
		exitButton.setPosition(sf::Vector2f(300.0f, 500.0f));
		m_buttons.push_back(restartButton);
		m_buttons.push_back(exitButton);

		m_buttonStrings.push_back("Restart");
		m_buttonStrings.push_back("Exit");
		break;
	}
	case EMenuTypes::NotPaused:
	{
		m_strings.push_back("Score: " + std::to_string(m_score));
		break;
	}
	default:
		break;
	}
}

sf::FloatRect Menu::getButtonBounds(size_t index) const
{
	return m_buttons.at(index).getGlobalBounds();
}

size_t Menu::getButtonCount() const
{
	return m_buttons.size();
}

EMenuButtons Menu::getButtonType(size_t index) const
{
	return EMenuButtons(index);
}

void Menu::hoverOver(size_t index, bool status)
{
	if (status)
	{
		m_buttons.at(index).setFillColor(sf::Color(220.0f, 30.0f, 0.0f, 150.0f));
	}
	else
	{
		m_buttons.at(index).setFillColor(sf::Color(200.0f, 30.0f, 0.0f, 150.0f));
	}
}

EMenuTypes Menu::getType() const
{
	return m_type;
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	switch (m_type)
	{
	case EMenuTypes::Start:
	case EMenuTypes::Death:
	{
		for (size_t i = 0; i < m_strings.size(); i++)
		{
			sf::Text text(m_strings[i], m_font, 30.0f);
			text.setPosition(350.0f, 200.0f + i * 40.0f);
			target.draw(text);
		}
		if (m_buttonStrings.size() == m_buttons.size())
		{
			for (size_t i = 0; i < m_buttons.size(); i++)
			{
				target.draw(m_buttons[i]);
				sf::Text text(m_buttonStrings[i], m_font, 30.0f);
				text.setPosition(m_buttons[i].getPosition() + m_buttons[i].getSize() / 3.5f);
				target.draw(text);
			}
		}
		break;
	}
	case EMenuTypes::NotPaused:
	{
		for (const std::string& string : m_strings)
		{
			sf::Text text(string, m_font, 30.0f);
			target.draw(text);
		}
	}
	}
}