#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>
#include <vector>

#include <QObject>
#include <QString>

#include <characters/classes/Monk.hpp>
#include <combat/Turn.hpp>
#include <combat/UnarmedStrike.hpp>
#include <combat/MeleeWeaponAttack.hpp>


namespace combat::classes {

class MonkOffHandAttack : public UnarmedStrike {
	Q_OBJECT

public:
	MonkOffHandAttack(characters::classes::Monk* monk) : UnarmedStrike(monk, false) { };

	bool isAvailable() const override { return available_; }

public slots:
	void setAvailable() { available_ = true; }
	void setUnavailable() { available_ = false; }

private:
	bool available_ = false;
};


class MonkTurn : public Turn {
	Q_OBJECT

public:
	MonkTurn(characters::classes::Monk* monk, characters::AbstractCharacter* opponent);

private:
	characters::classes::Monk* monk_;
	std::unique_ptr<UnarmedStrike> unarmedStrikeAcn_;
	std::unique_ptr<MeleeWeaponAttack> meleeAttackAcn_;
	std::unique_ptr<MonkOffHandAttack> offhandStrikeBonusAcn_;
};

}


