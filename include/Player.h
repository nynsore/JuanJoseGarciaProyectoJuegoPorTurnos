#include "Character.h"

class Player : public Character {
private:
	int level;
	int experience;

public:
	Player(const std::string&, Stats&, const std::string&, sf::Vector2f);
	~Player() override {}
	void TakeDamage(int) override;
	void UseSkill() override;
	void Death() override;
	void Attack(int, Character* ) override;
};