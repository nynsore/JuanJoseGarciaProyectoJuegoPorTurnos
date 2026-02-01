#include "Stats.h"

Stats::Stats(int hp, int mp, float _strength, float _defense, float _magic, float _magicDefense, float _agility, int _luck, float _evasion, float _accuracy) 
: health(hp), MP(mp), strength(_strength), defense(_defense), magic(_magic), magicDefense(_magicDefense), agility(_agility), luck(_luck), evasion(_evasion), accuracy(_accuracy){
	
}

Stats::Stats(const Stats& stats) 
: health(stats.Gethealth()), MP(stats.GetMP()), strength(stats.GetStrength()), defense(stats.GetDefense()), magic(stats.GetMagic()), magicDefense(stats.GetMagicDefense()), agility(stats.GetAgility()), luck(stats.GetLuck()), evasion(stats.GetEvasion()), accuracy(stats.GetAccuracy()){
	
}

Stats::Stats() {
    health = 0;
    MP = 0;
    strength = 0.0f;
    defense = 0.0f;
    magic = 0.0f;
    magicDefense = 0.0f;
    agility = 0.0;
    luck = 0;
    evasion = 0.0f;
    accuracy = 0.0f;
}