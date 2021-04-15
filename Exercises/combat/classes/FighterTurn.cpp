#include <cstddef>
#include <cstdint>

#include <utility>

#include <QObject>
#include <QString>

#include <characters/AbstractCharacter.hpp>
#include <combat/IActivity.hpp>

#include "FighterTurn.hpp"


namespace combat::classes {

FighterTurn::FighterTurn(characters::classes::Fighter* fighter, characters::AbstractCharacter* opponent)
: Turn(fighter, opponent),
  fighter_(fighter) {
	unarmedStrikeAcn_ = std::make_unique<UnarmedStrike>(fighter, true);
	meleeAttackAcn_ = std::make_unique<MeleeWeaponAttack>(fighter, true);
	secondWindBonusAcn_ = std::make_unique<FighterSecondWind>(fighter);

	actions_ = {
		unarmedStrikeAcn_.get(),
		meleeAttackAcn_.get()
	};
	bonusActions_ = {
		secondWindBonusAcn_.get()
	};
}

}


