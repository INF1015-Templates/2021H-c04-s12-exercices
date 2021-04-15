#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>

#include <QString>


namespace weapons {

class IWeapon {
public:
	virtual ~IWeapon() = default;

	/// @returns Name of the weapon
	virtual const QString& getName() const = 0;

	/// @returns Bonus to hit
	virtual int getAttackBonus() const = 0;

	/// @returns Bonus to damage roll
	virtual int getDamageBonus() const = 0;

	/// @returns {Weapon damage dice roll, weapon damage bonus}
	virtual std::pair<int, int> rollDamage() = 0;
};

}


