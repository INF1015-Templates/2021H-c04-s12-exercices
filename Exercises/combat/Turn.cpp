#include <cstddef>
#include <cstdint>

#include <utility>

#include <QObject>
#include <QString>

#include <characters/AbstractCharacter.hpp>
#include <combat/IActivity.hpp>

#include "Turn.hpp"


namespace combat {

Turn::Turn(characters::AbstractCharacter* character, characters::AbstractCharacter* opponent)
: character_(character),
  opponent_(opponent) { }


std::span<IActivity*> Turn::getActions() {
	return actions_;
}

std::span<IActivity*> Turn::getBonusActions() {
	return bonusActions_;
}

bool Turn::isActionAvailable() const {
	return actionAvailable_;
}

bool Turn::isBonusActionAvailable() const {
	return bonusActionAvailable_;
}

characters::AbstractCharacter* Turn::getCharacter() const {
	return character_;
}

characters::AbstractCharacter* Turn::getOpponent() const {
	return opponent_;
}

void Turn::start() {
	actionAvailable_ = bonusActionAvailable_ = true;
	emit message(tr("Top of the turn for %1").arg(character_->getName()));
	emit started();
}

void Turn::takeAction(int index) {
	auto* activity = (index != skipActivity) ? actions_.at(index) : nullptr;
	if (activity != nullptr and activity->isAvailable())
		activity->apply(opponent_);
	actionAvailable_ = false;
	emit actionTaken();
	if (not actionAvailable_ and not bonusActionAvailable_)
		end();
}

void Turn::takeBonusAction(int index) {
	auto* activity = (index != skipActivity) ? bonusActions_.at(index) : nullptr;
	if (activity != nullptr and activity->isAvailable())
		activity->apply(opponent_);
	bonusActionAvailable_ = false;
	emit bonusActionTaken();
	if (not actionAvailable_ and not bonusActionAvailable_)
		end();
}

void Turn::end() {
	emit message(tr("End of turn" "\n"));
	emit ended();
}

}


