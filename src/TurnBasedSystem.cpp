#include "TurnBasedSystem.h"

TurnBasedSystem::TurnBasedSystem(std::vector<Player*> _players, std::vector<Enemy*> _enemies) 
	:players(_players), enemies(_enemies) {
	for (Character* c : players) {
		turnrOrder.push_back(c);
	}
	for (Character* c : enemies) {
		turnrOrder.push_back(c);
	}
}

Character* TurnBasedSystem::WhoIsNext() {
	std::sort(turnrOrder.begin(), turnrOrder.end(), [](const Character* c1, const Character* c2) {
		return c1->GetCurrentTurnMeter() > c2->GetCurrentTurnMeter();
	});
	if (turnrOrder[0]->CanAct()) {
		currentCharacterTurn = turnrOrder[0];
		return currentCharacterTurn;
	}
	return nullptr;
}

void TurnBasedSystem::StartTurn() {
	for (Character* c : turnrOrder) {
		c->AddAgilityToMeter();
	}
}

int TurnBasedSystem::CalculateAttackDamage(Character* from, Character* to) {
	int damage = static_cast<int>(((pow(from->GetCurrentStats().GetStrength(), 2) / 15) + 12) * (32 / 16));
	int defense = static_cast<int>(((pow(to->GetCurrentStats().GetDefense() - 150.4, 2)) / 75) + 15);
	int output = damage * defense / 580;
	return output;
}
