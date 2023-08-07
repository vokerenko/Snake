#pragma once
#include "stdafx.h"



namespace Constants
{
	constexpr int RectSize = 30;
	constexpr int WindowWidth = 900;
	constexpr int WindowHeight = 900;
	constexpr int SnakeSpeed = RectSize;
	constexpr int SnakeInitialLength = 3;
	constexpr float FrameTime = 0.3f; // in seconds
	const sf::Color WallColor = sf::Color(200, 0, 20, 255);
	const sf::Color SnakeColor = sf::Color(20, 200, 0, 255);
	const sf::Vector2f WindowCenter = sf::Vector2f(static_cast<float>(Constants::WindowWidth / 2),
		static_cast<float>(Constants::WindowHeight / 2));
}
enum class EDirection
{
	Right = 0, Down = 1, Left = 2, Up = 3
};
namespace Input
{
	const std::unordered_map<sf::Keyboard::Key, EDirection> keyToDirection =
	{
		{sf::Keyboard::W, EDirection::Up},
		{sf::Keyboard::D, EDirection::Right},
		{sf::Keyboard::S, EDirection::Down},
		{sf::Keyboard::A, EDirection::Left}
	};
}
enum class EMenuTypes
{
	Start = 0,
	Death = 1,
	NotPaused
};
enum class EMenuButtons
{
	Start = 0,
	Restart = 0,
	Exit = 1
};



template<typename T>
inline sf::Vector2<T> abs(sf::Vector2<T>& value) { return sf::Vector2<T>(abs(value.x), abs(value.y)); }

template<typename T>
inline std::ostream& operator<< (std::ostream& out, const sf::Vector2<T>& vec)
{
	out << "{ x:" << vec.x << " y:" << vec.y << " }";
	return out;
}

template<typename T>
inline std::ostream& operator<< (std::ostream& out, const sf::Rect<T>& r)
{
	out << "{ left:" << r.left << ", top:" << r.top << ", width:" << r.width << ", height:" << r.height;
	return out;
}