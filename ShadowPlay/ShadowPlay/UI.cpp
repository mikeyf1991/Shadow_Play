#include "UI.hpp"


void UI::init(sf::View view_main)
{

	if (!font.loadFromFile("vahikai.ttf"))
	{
		// error...
	}
	font.getLineSpacing(5);
	UI_Text.resize(10);
	for (auto& ui_t : UI_Text)
	{
		ui_t.setFont(font);
		ui_t.setCharacterSize(32);
		ui_t.setColor(sf::Color::Cyan);
		ui_t.setStyle(sf::Text::Regular);
	}
	pos.x = 50; pos.y = 50;
	UI_Text[0].setPosition(view_main.getCenter().x - (view_main.getSize().x / 2) + 50, pos.y);
	UI_Text[1].setPosition(view_main.getCenter().x - 40, pos.y);
	UI_Text[2].setPosition(view_main.getCenter().x + 400, pos.y);
	UI_Text[3].setPosition(view_main.getCenter().x + 400, view_main.getCenter().y - view_main.getSize().y / 2 + 600);

}

void UI::TextSetup(std::vector <sf::Text> &UI_Text, sf::Vector2i position)
{

}

void UI::updatePlayerPos(Player& player, sf::View view_main)
{

	std::string plyr_x = std::to_string(player.Shape().getPosition().x);
	std::string plyr_y = std::to_string(player.Shape().getPosition().y);

	plyr_x = plyr_x.substr(0, plyr_x.length() - 5);
	plyr_y = plyr_y.substr(0, plyr_y.length() - 5);

	UI_Text[0].setString("Player Pos X: " + plyr_x);
	UI_Text[1].setString("Player Pos Y: " + plyr_y);

	UI_Text[0].setPosition(view_main.getCenter().x - (view_main.getSize().x / 2.0f) + 50, view_main.getCenter().y - view_main.getSize().y / 2 + 10);
	UI_Text[1].setPosition(view_main.getCenter().x - (view_main.getSize().x / 2.0f) + 275, view_main.getCenter().y - view_main.getSize().y / 2 + 10);

}

void UI::updateKey(KeyPickup& key, Player& player, sf::View view_main)
{
	std::string pick_up = std::to_string(key.getPickupedUpState());
	UI_Text[2].setPosition(view_main.getCenter().x + 300, view_main.getCenter().y - view_main.getSize().y / 2 + 925);
	if (pick_up == "0")
		UI_Text[2].setString("Key picked up: No");
	else
	{
		UI_Text[2].setPosition(view_main.getCenter().x + 200, view_main.getCenter().y - view_main.getSize().y / 2 + 925);
		UI_Text[2].setString("Key picked up: Yes(Can exit now)");
	}

}

void UI::updateLight(Light& lights, sf::View view_main)
{
	UI_Text[3].setPosition(view_main.getCenter().x - 600, view_main.getCenter().y - view_main.getSize().y / 2 + 925);
	//UI_Text[3].setString("Teleport available to Light(s) : ");

	std::string str = "";

	for (auto& s : ui_lights_)
	{
		str += s + ", ";
	}

	UI_Text[3].setString("Teleport available to Light(s) : " + str);
}

void UI::Draw(sf::RenderWindow& window, Player& player)
{
	if (player.getPlayerTextState() == true)
	{
		window.draw(UI_Text[0]);
		window.draw(UI_Text[1]);
	}
	window.draw(UI_Text[2]);
	window.draw(UI_Text[3]);
}