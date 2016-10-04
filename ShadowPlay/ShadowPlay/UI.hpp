#ifndef UI_HPP
#define UI_HPP

#include "Common.hpp"
#include "Player.hpp"
#include "KeyPickup.hpp"
#include "Light.hpp"

class UI
{
public:

	int getPositionX() const { return pos.x; }
	void setPositionX(int pos_x_) { pos.x = pos_x_; }

	int getPositionY() const { return pos.y; }
	void setPositionY(int pos_y_){ pos.y = pos_y_; }


	void init(sf::View view_main);
	void updatePlayerPos(Player& player, sf::View view_main);
	void updateKey(KeyPickup& key, Player& player, sf::View view_main);
	void Draw(sf::RenderWindow& window, Player& player);
	void TextSetup(std::vector <sf::Text> &UI_Text, sf::Vector2i position);
	void updateLight(Light& lights, sf::View view_main);

	std::vector<std::string> ui_lights_;
private:

	std::vector <sf::Text> UI_Text;

	sf::Font font;
	sf::Vector2i pos;

};


#endif