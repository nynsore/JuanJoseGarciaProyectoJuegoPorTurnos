#include "Enemy.h"

Enemy::Enemy(const std::string& _name, Stats& _stats, const std::string& texture, sf::Vector2f pos) : Character(_name, _stats, texture, pos){

}

void Enemy::TakeDamage(int damage) {
	currentHealth -= damage;
	healthText.setString(std::to_string(currentHealth) + " / " + std::to_string(characterStats.Gethealth()));
	if (currentHealth <= 0) Death();
}

void Enemy::Attack(int input, Character* target) {

}

void Enemy::UseSkill() {
	
}

void Enemy::Death() {
	
}

void Enemy::DrawHealth(const sf::Font& font, sf::RenderWindow& window) {
	healthText.setFont(font);
	healthText.setCharacterSize(18);
	healthText.setFillColor(sf::Color::Red);
	healthText.setString(std::to_string(currentHealth) + " / " + std::to_string(characterStats.Gethealth()));
	healthText.setPosition(sf::Vector2f(spriteCharacter.getGlobalBounds().left + spriteCharacter.getGlobalBounds().width / 2 - healthText.getLocalBounds().width / 2,
		spriteCharacter.getGlobalBounds().top + spriteCharacter.getGlobalBounds().height + 10.0f));
	window.draw(healthText);
}
