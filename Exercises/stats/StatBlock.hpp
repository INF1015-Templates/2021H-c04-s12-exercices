#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>

#include <QString>

#include <stats/Ability.hpp>


namespace stats {

// Exemple d'utilisation légitime des macros : on génère du code à la précompilation.
#define DEFINE_ABILITY_ACCESSORS(accessor, id) \
	const Ability& accessor() const { return getAbility(id); } \
	Ability& accessor() { return getAbility(id); } \
	int accessor##Score() const { return accessor().getScore(); } \
	int accessor##Modifier() const { return accessor().getModifier(); }


class StatBlock {
public:
	const Ability& getAbility(AbilityId id) const;
	Ability& getAbility(AbilityId id);
	int getArmorClass() const;
	void setArmorClass(int ac);
	int getMaxHp() const;
	void setMaxHp(int hp);
	int getCurrentHp() const;
	void setCurrentHp(int hp);
	int getTemporaryHp() const;
	void setTemporaryHp(int hp);

	DEFINE_ABILITY_ACCESSORS(getStrength, STR)
	DEFINE_ABILITY_ACCESSORS(getDexterity, DEX)
	DEFINE_ABILITY_ACCESSORS(getConstitution, CON)
	DEFINE_ABILITY_ACCESSORS(getIntelligence, INT)
	DEFINE_ABILITY_ACCESSORS(getWisdom, WIS)
	DEFINE_ABILITY_ACCESSORS(getCharisma, CHA)

private:
	Ability abilities_[numAbilities] = {STR, DEX, CON, INT, WIS, CHA};
	int armorClass_ = 1;
	int maxHp_ = 1;
	int currentHp_ = 1;
	int tempHp_ = 0;
};


#undef DEFINE_ABILITY_ACCESSORS

}


