#pragma once
#include "Character.h"

class Enemy : public Character {
private:
	sf::Text healthText;

public:

	Enemy(const std::string&, Stats&, const std::string&, sf::Vector2f);
	~Enemy() override{}

	void TakeDamage(int) override;
	void UseSkill() override;
	void Death() override;
	void Attack(int, Character*) override;
	void DrawHealth(const sf::Font&, sf::RenderWindow&);
};