#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "BaseShape.hpp"
#include "Common.hpp"

class Light : public BaseShape<sf::RectangleShape>
{
public:
	Light(sf::Vector2f postion, sf::Vector2f size, sf::Color colour, int id);
	float set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset);

	bool can_teleport() const { return teleport_; }
	void set_teleport(bool val) { teleport_ = val; }

	const int ID() const { return id_; }

	bool draw_shadow() const { return shadow_; }
	void set_shadow(bool val) { shadow_ = val; }

	bool get_shadow_text() const { return shadow_textdraw_; }
	void set_shadow_text(bool val) { shadow_textdraw_ = val; }

	bool get_In_Range() const { return in_range_; }
	void set_In_Range(bool ir) { in_range_ = ir; }

private:
	int id_;
	bool teleport_;
	bool in_range_;
	bool shadow_;
	bool shadow_textdraw_;
};

#endif