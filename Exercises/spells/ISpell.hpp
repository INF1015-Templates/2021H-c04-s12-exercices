#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>
#include <optional>

#include <QString>

#include <stats/Ability.hpp>


namespace spells {

class ISpell {
public:
	virtual ~ISpell() = default;

	/// @returns Name of the spell
	virtual const QString& getName() const = 0;

	/// @returns Spell level
	virtual int getLevel() const = 0;

	virtual bool requiresSpellAttack() const = 0;

	virtual std::optional<stats::AbilityId> getSavingThrowType() const = 0;

	/// Roll damage, with higher level casting if applicable.
	/// @returns {Spell damage dice roll, spell damage bonus}
	virtual std::pair<int, int> rollDamage() const = 0;
};

}


