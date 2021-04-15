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

class Monk : public virtual BasicCharacter<utils::dice::d8_t>, public MeleeWeaponUser {
public:
	Monk(const QString& name, std::span<stats::Ability, stats::numAbilities> abilities);

	void applyUnarmoredDefense();

	bool canEquipWeapon(const weapons::melee::IMeleeWeapon& weapon) const override;
	const QString& getClassName() const override { static QString name = "Monk"; return name; }
	int getNumAttacksPerAction() const override;
	std::tuple<int, int, bool> rollUnarmedAttack() override;
	int rollUnarmedDamage(bool crit) override;
	int getAttackAbilityModifier() const override;
};

}


