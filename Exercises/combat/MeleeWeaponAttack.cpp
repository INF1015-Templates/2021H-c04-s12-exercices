
#include <cstddef>
#include <cstdint>

#include <utility>

#include <QObject>
#include <QString>

#include <cppitertools/itertools.hpp>

#include <characters/MeleeWeaponUser.hpp>

#include "MeleeWeaponAttack.hpp"


namespace combat {

MeleeWeaponAttack::MeleeWeaponAttack(characters::MeleeWeaponUser* weaponUser, bool multi)
: Attack(weaponUser, "Melee Weapon Attack", "Attack with a weapon", multi),
  weaponUser_(weaponUser) { }

bool MeleeWeaponAttack::isAvailable() const {
	return weaponUser_->getWeapon() != nullptr;
}

std::tuple<int, int, bool> MeleeWeaponAttack::rollAttack() {
	return weaponUser_->rollMeleeWeaponAttack();
}

int MeleeWeaponAttack::rollDamage(bool crit) {
	return weaponUser_->rollMeleeWeaponDamage(crit);
}

}


