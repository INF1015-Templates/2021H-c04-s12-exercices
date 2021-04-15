
#include <cstddef>
#include <cstdint>

#include <utility>

#include <QObject>
#include <QString>

#include <cppitertools/itertools.hpp>

#include <characters/AbstractCharacter.hpp>
#include <combat/IActivity.hpp>

#include "UnarmedStrike.hpp"


namespace combat {

UnarmedStrike::UnarmedStrike(characters::AbstractCharacter* character, bool multi)
: Attack(character, "Unarmed Strike", "Punch, kick, head-butt, or similar forceful blow", multi) { }

bool UnarmedStrike::isAvailable() const {
	return true;
}

std::tuple<int, int, bool> UnarmedStrike::rollAttack() {
	return character_->rollUnarmedAttack();
}

int UnarmedStrike::rollDamage(bool crit) {
	return character_->rollUnarmedDamage(crit);
}

}


