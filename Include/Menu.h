#pragma once
#include "Utility.h"

class Menu : public sf::Drawable
{
public:
	Menu(EMenuTypes type, unsigned int score);
public:
	sf::FloatRect getButtonBounds(size_t index) const;
	size_t getButtonCount() const;
	EMenuButtons getButtonType(size_t index) const;
	void hoverOver(size_t index, bool status);
	EMenuTypes getType() const;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	EMenuTypes m_type;
	std::vector<sf::RectangleShape> m_buttons;
	std::vector<std::string> m_strings;
	std::vector<std::string> m_buttonStrings;
	sf::Font m_font;
	unsigned int m_score;
};

