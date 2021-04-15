#include <cstddef>
#include <cstdint>

#include <utility>
#include <span>
#include <cmath>
#include <memory>

#include <QString>

#include <characters/AbstractCharacter.hpp>
#include <weapons/melee/IMeleeWeapon.hpp>
#include <utils/DiceRoller.hpp>

#include "MeleeWeaponUser.hpp"


namespace characters {

weapons::melee::IMeleeWeapon* MeleeWeaponUser::getWeapon() const {
	return weapon_.get();
}

std::unique_ptr<weapons::melee::IMeleeWeapon> MeleeWeaponUser::equipWeapon(std::unique_ptr<weapons::melee::IMeleeWeapon> weapon) {
	if (weapon == nullptr or canEquipWeapon(*weapon)) {
		auto old = std::move(weapon_);
		weapon_ = std::move(weapon);
		return std::move(old);
	}
	return {};
}

int MeleeWeaponUser::getAttackAbilityModifier() const {
	return stats::STR;
}

std::tuple<int, int, bool> MeleeWeaponUser::rollMeleeWeaponAttack() {
	int natRoll = utils::dice::d20.roll();
	int attackRoll = natRoll + getProficiencyBonus() + weapon_->getAttackBonus() + getAttackAbilityModifier();
	bool isCritHit = natRoll == 20;
	bool isCritMiss = natRoll == 1;
	if (isCritMiss)
		return {natRoll, 0, false};
	return {natRoll, attackRoll, isCritHit};
}

int MeleeWeaponUser::rollMeleeWeaponDamage(bool crit) {
	auto&&[diceRoll, wpnBonus] = weapon_->rollDamage();
	if (crit)
		diceRoll *= 2;
	return diceRoll + wpnBonus + getAttackAbilityModifier();
}

}


