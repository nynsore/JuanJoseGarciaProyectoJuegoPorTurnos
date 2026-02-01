#include "Player.h"

Player::Player(const std::string& _name, Stats& _stats, const std::string& texture, sf::Vector2f pos) : Character(_name, _stats, texture, pos) {
	level = 1;
	experience = 0;
}

void Player::TakeDamage(int damage) {
	currentHealth -= damage;
	if (currentHealth <= 0) Death();
}

void Player::Attack(int input, Character* target) {
	target->TakeDamage(input);
}

void Player::UseSkill() {

}

void Player::Death() {

}