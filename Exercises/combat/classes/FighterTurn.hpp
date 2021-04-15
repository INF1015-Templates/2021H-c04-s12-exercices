#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>
#include <vector>

#include <QObject>
#include <QString>

#include <characters/classes/Fighter.hpp>
#include <combat/Turn.hpp>
#include <combat/UnarmedStrike.hpp>
#include <combat/MeleeWeaponAttack.hpp>


namespace combat::classes {

class FighterSecondWind : public BaseActivity<characters::classes::Fighter> {
	Q_OBJECT

public:
	FighterSecondWind(characters::classes::Fighter* fighter) : BaseActivity(fighter, "Second Wind") { };

	bool isAvailable() const override { return available_; }
	void apply(characters::AbstractCharacter*) override {
		int healedHp = utils::dice::d10.roll() + character_->getLevel();
		character_->setCurrentHp(character_->getCurrentHp() + healedHp);
		emit message(tr("%1 healed %2 HP").arg(getName()).arg(healedHp));
		available_ = false;
	}

private:
	bool available_ = true;
};


class FighterTurn : public Turn {
	Q_OBJECT

public:
	FighterTurn(characters::classes::Fighter* fighter, characters::AbstractCharacter* opponent);

private:
	characters::classes::Fighter* fighter_;
	std::unique_ptr<UnarmedStrike> unarmedStrikeAcn_;
	std::unique_ptr<MeleeWeaponAttack> meleeAttackAcn_;
	std::unique_ptr<FighterSecondWind> secondWindBonusAcn_;
};

}


