#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>

#include <QString>


namespace stats {

enum AbilityId {
	strength,
	dexterity,
	constitution,
	intelligence,
	wisdom,
	charisma,
	numAbilities,
	STR = strength,
	DEX = dexterity,
	CON = constitution,
	INT = intelligence,
	WIS = wisdom,
	CHA = charisma
};

struct Ability {
	Ability(AbilityId id, int score = 0);

	AbilityId getId() const;
	int getScore() const;
	void setScore(int score);
	int getModifier() const;

private:
	AbilityId id_;
	int score_;
};

}


