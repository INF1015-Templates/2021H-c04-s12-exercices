#include <cstddef>
#include <cstdint>

#include <utility>
#include <span>
#include <cmath>

#include <QString>

#include <characters/BasicCharacter.hpp>
#include <characters/MeleeWeaponUser.hpp>
#include <weapons/melee/GenericMeleeWeapon.hpp>
#include <utils/Die.hpp>

#include "Monk.hpp"


namespace characters::classes {

Monk::Monk(const QString& name, std::span<stats::Ability, stats::numAbilities> abilities)
: BasicCharacter(name, abilities) {
	addSaveProficiency(stats::STR);
	addSaveProficiency(stats::DEX);
	applyUnarmoredDefense();
}

void Monk::applyUnarmoredDefense() {
	setArmorClass(10 + getDexterityModifier() + getWisdomModifier());
}

bool Monk::canEquipWeapon(const weapons::melee::IMeleeWeapon& weapon) const {
	bool isShortsword = dynamic_cast<const weapons::melee::Shortsword*>(&weapon) != nullptr;
	bool isSimple = not weapon.isMartial();
	bool isTwoHanded = weapon.isTwoHanded();
	return isShortsword or (isSimple and not isTwoHanded);
}

int Monk::getNumAttacksPerAction() const {
	if (getLevel() >= 5)
		return 2;
	else
		return 1;
}

std::tuple<int, int, bool> Monk::rollUnarmedAttack() {
	using namespace utils::dice;
	int natRoll = d20.roll();
	int totalRoll = natRoll + getProficiencyBonus() + getDexterityModifier();
	bool isCritHit = natRoll == 20;
	bool isCritMiss = natRoll == 1;
	if (isCritMiss)
		return {natRoll, 0, false};
	return {natRoll, totalRoll, isCrit};
}

int Monk::rollUnarmedDamage(bool crit) {
	using namespace utils::dice;
	int damageRoll = 0;
	if (getLevel() >= 17)
		damageRoll = d10.roll();
	else if (getLevel() >= 11)
		damageRoll = d8.roll();
	else if (getLevel() >= 5)
		damageRoll = d6.roll();
	else
		damageRoll = d4.roll();
	if (crit)
		damageRoll *= 2;
	return damageRoll + getDexterityModifier();
}

int Monk::getAttackAbilityModifier() const {
	return getDexterityModifier();
}

}

