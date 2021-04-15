#include <cstddef>
#include <cstdint>

#include <utility>
#include <span>
#include <cmath>

#include <QString>

#include <characters/BasicCharacter.hpp>
#include <characters/MeleeWeaponUser.hpp>
#include <utils/Die.hpp>

#include "Fighter.hpp"


namespace characters::classes {

Fighter::Fighter(const QString& name, std::span<stats::Ability, stats::numAbilities> abilities)
: BasicCharacter(name, abilities) {
	addSaveProficiency(stats::STR);
	addSaveProficiency(stats::CON);
}


int Fighter::getNumAttacksPerAction() const {
	if (getLevel() >= 20)
		return 4;
	else if (getLevel() >= 11)
		return 3;
	else if (getLevel() >= 5)
		return 2;
	else
		return 1;
}

bool Fighter::canEquipWeapon(const weapons::melee::IMeleeWeapon&) const {
	return true;
}

std::tuple<int, int, bool> Fighter::rollMeleeWeaponAttack() {
	int natRoll = utils::dice::d20.roll();
	int totalRoll = natRoll + getProficiencyBonus() + weapon_->getAttackBonus() + getStrengthModifier();
	bool isCrit = natRoll == 20;
	bool isCritMiss = natRoll == 1;
	if (isCritMiss)
		return {natRoll, 0, false};
	if (getLevel() >= 15)
		isCrit = natRoll >= 18;
	else if (getLevel() >= 3)
		isCrit = natRoll >= 19;
	return {natRoll, totalRoll, isCrit};
}

}

