#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>
#include <optional>

#include <QString>

#include <stats/Ability.hpp>
#include <spells/ISpell.hpp>
#include <utils/DiceRoller.hpp>


namespace spells {

template <int level, int numDmgDice, typename DmgDie, int dmgBonus, bool spellAttack, stats::AbilityId saveType = stats::numAbilities>
class GenericSpell : public ISpell {
public:
	GenericSpell(const QString& name)
	: name_(name) { }

	/// @returns Name of the spell
	const QString& getName() const override {
		return name_;
	}

	/// @returns Spell level (0 = cantrip)
	int getLevel() const override {
		return level;
	}

	bool requiresSpellAttack() const override {
		return spellAttack;
	}

	std::optional<stats::AbilityId> getSavingThrowType() const override {
		return (saveType == stats::numAbilities) ? {} : saveType;
	}

	/// @returns {Spell damage dice roll, spell damage bonus}
	std::pair<int, int> rollDamage() const override {
		return {(numDmgDice * damageDie_).roll(), dmgBonus};
	}

private:
	QString name_;
	DmgDie damageDie_;
};

}


