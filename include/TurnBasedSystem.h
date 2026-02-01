#include "Player.h"
#include "Enemy.h"

class TurnBasedSystem {
private:
	std::vector<Character*> turnrOrder;
	std::vector<Player*> players;
	std::vector<Enemy*> enemies;

	Character* currentCharacterTurn = nullptr;

public:
	TurnBasedSystem(std::vector<Player*>, std::vector<Enemy*>);
	TurnBasedSystem() {}
	Character* WhoIsNext();
	void StartTurn();
	int CalculateAttackDamage(Character* , Character* );

	Character* GetCurrentCharTurn() { return currentCharacterTurn; }
};