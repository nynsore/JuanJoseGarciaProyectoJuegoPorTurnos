#pragma once

#include <string>
#include <Stats.h>
#include <SFML/Graphics.hpp>

class Character {

protected:
	std::string name;
	int currentHealth;
	int currentMP;
	Stats characterStats;

	sf::Texture textureCharacter;
	sf::Sprite spriteCharacter;
	sf::Vector2f position;

	float currentTurnMeter = 0.0f;
	const float maxTurnMeter = 100.0f;

	Character(const std::string&, Stats&, const std::string&, sf::Vector2f);

public:
	virtual ~Character() {}
	virtual void TakeDamage(int) = 0;
	virtual void UseSkill() = 0;
	virtual void Death() = 0;
	virtual void Attack(int, Character* ) = 0;
	void DrawCharacter(sf::RenderWindow&);

	int GetCurrenthealth() { return currentHealth; }
	int GetCurrentMP() { return currentMP; }
	float GetCurrentTurnMeter() const { return currentTurnMeter; }
	Stats& GetCurrentStats() { return characterStats; }
	const Stats& GetCurrentStats() const { return characterStats; }
	void SetPosition(sf::Vector2f);
	void SetSpriteScale(float, float);

	void AddAgilityToMeter();
	void ConsumeTurn();
	bool CanAct();
};