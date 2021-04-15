#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>
#include <span>
#include <cmath>

#include <QString>

#include <characters/BasicCharacter.hpp>
#include <characters/MeleeWeaponUser.hpp>
#include <utils/Die.hpp>


namespace characters::classes {

class Fighter : public BasicCharacter<utils::dice::d10_t>, public MeleeWeaponUser {
public:
	Fighter(const QString& name, std::span<stats::Ability, stats::numAbilities> abilities);

	const QString& getClassName() const override { static QString val = "Fighter"; return val; }
	int getNumAttacksPerAction() const override;
	bool canEquipWeapon(const weapons::melee::IMeleeWeapon& weapon) const override;
	std::tuple<int, int, bool> rollMeleeWeaponAttack() override;
};

}


