#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>
#include <span>
#include <cmath>
#include <memory>

#include <QString>

#include <characters/AbstractCharacter.hpp>
#include <weapons/melee/IMeleeWeapon.hpp>


namespace characters {

class MeleeWeaponUser : public virtual AbstractCharacter {
public:
	weapons::melee::IMeleeWeapon* getWeapon() const;
	std::unique_ptr<weapons::melee::IMeleeWeapon> equipWeapon(std::unique_ptr<weapons::melee::IMeleeWeapon> weapon);
	virtual bool canEquipWeapon(const weapons::melee::IMeleeWeapon& weapon) const = 0;
	virtual int getAttackAbilityModifier() const;
	virtual std::tuple<int, int, bool> rollMeleeWeaponAttack();
	virtual int rollMeleeWeaponDamage(bool crit);

protected:
	std::unique_ptr<weapons::melee::IMeleeWeapon> weapon_;
};

}


