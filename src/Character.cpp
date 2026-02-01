#include "Character.h"

void Character::SetPosition(sf::Vector2f newPos) {
	position = newPos;
	spriteCharacter.setPosition(newPos);
}

Character::Character(const std::string& _name, Stats& _stats, const std::string& texture, sf::Vector2f pos) 
	: name(_name), characterStats(_stats), position(pos), currentHealth(_stats.Gethealth()), currentMP(_stats.GetMP()){
	textureCharacter.loadFromFile(texture);
	spriteCharacter.setTexture(textureCharacter);
	spriteCharacter.setPosition(pos);
}

void Character::DrawCharacter(sf::RenderWindow& window) {
	window.draw(spriteCharacter);
}

void Character::SetSpriteScale(float width, float height) {
	sf::FloatRect size = spriteCharacter.getLocalBounds();
	spriteCharacter.setScale(width / size.width, height / size.height);
}

void Character::AddAgilityToMeter() {
	currentTurnMeter += characterStats.GetAgility();
}

void Character::ConsumeTurn() {
	currentTurnMeter -= maxTurnMeter;
}

bool Character::CanAct() {
	if (currentTurnMeter >= maxTurnMeter) return true;
	return false;
}