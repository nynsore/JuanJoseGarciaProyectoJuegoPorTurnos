#pragma once

struct Stats{

private:
	int health;
	int MP;
	float strength, defense;
	float magic, magicDefense;
	float agility;
	int luck;
	float evasion, accuracy;

public:
	Stats(int,int,float,float,float,float,float, int, float, float);
	Stats(const Stats&);
	Stats();
	
	int Gethealth() const { return health; }
	int GetMP() const { return MP; }
	float GetStrength() const { return strength; }
	float GetDefense() const { return defense; }
	float GetMagic() const { return magic; }
	float GetMagicDefense() const { return magicDefense; }
	float GetAgility() const { return agility; }
	int GetLuck() const { return luck; }
	float GetEvasion() const { return evasion; }
	float GetAccuracy() const { return accuracy; }

	void Sethealth(int newHealth) { health = newHealth; }
	void SetMP(int newMP) { MP = newMP; }
	void SetStrength(float newStrength) { strength = newStrength; }
	void SetDefense(float newDefense) { defense = newDefense; }
	void SetMagic(float newMagic) {  magic = newMagic; }
	void SetMagicDefense(float newMagicDefense) { magicDefense = newMagicDefense; }
	void SetAgility(float newAgility) { agility = newAgility; }
	void SetLuck(int newLuck) { luck = newLuck; }
	void SetEvasion(float newEvasion) { evasion = newEvasion; }
	void SetAccuracy(float newAccuracy) { accuracy = newAccuracy; }
};