#include <cstddef>
#include <cstdint>

#include <utility>

#include <QObject>
#include <QString>

#include <characters/AbstractCharacter.hpp>
#include <combat/IActivity.hpp>

#include "MonkTurn.hpp"


namespace combat::classes {

MonkTurn::MonkTurn(characters::classes::Monk* monk, characters::AbstractCharacter* opponent)
: Turn(monk, opponent),
  monk_(monk) {
	unarmedStrikeAcn_ = std::make_unique<UnarmedStrike>(monk, true);
	meleeAttackAcn_ = std::make_unique<MeleeWeaponAttack>(monk, true);
	offhandStrikeBonusAcn_ = std::make_unique<MonkOffHandAttack>(monk);

	connect(this, SIGNAL(started()), offhandStrikeBonusAcn_.get(), SLOT(setUnavailable()));
	connect(unarmedStrikeAcn_.get(), SIGNAL(done()), offhandStrikeBonusAcn_.get(), SLOT(setAvailable()));
	connect(meleeAttackAcn_.get(), SIGNAL(done()), offhandStrikeBonusAcn_.get(), SLOT(setAvailable()));

	actions_ = {
		unarmedStrikeAcn_.get(),
		meleeAttackAcn_.get()
	};
	bonusActions_ = {
		offhandStrikeBonusAcn_.get()
	};
}

}


