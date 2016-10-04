#ifndef SWITCH_HPP
#define SWITCH_HPP

#include "BaseShape.hpp"
#include "Common.hpp"

class Switch : public BaseShape<sf::RectangleShape>
{
public:
	Switch(sf::Vector2f postion, sf::Vector2f size, sf::Color colour, int id);
	float set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset);

	bool has_Pulled() const { return pulled_; }
	void set_Pulled(bool pul) { pulled_ = pul; }

	bool in_Range() const { return in_range_; }
	void set_inRange(bool iR) { in_range_ = iR; }

	const int ID() const { return id_; }
	sf::Vector2i isource;
	sf::Texture spriteTexture;
	sf::Texture spriteTexture2;
	sf::Sprite spriteImage;
	sf::Sprite spriteImage2;
private:
	int id_;
	bool pulled_;
	bool in_range_;
};

#endif