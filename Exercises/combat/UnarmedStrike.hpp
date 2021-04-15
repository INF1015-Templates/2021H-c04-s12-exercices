#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>

#include <QObject>
#include <QString>

#include <characters/AbstractCharacter.hpp>
#include <combat/Attack.hpp>


namespace combat {

class UnarmedStrike : public Attack {
	Q_OBJECT

public:
	UnarmedStrike(characters::AbstractCharacter* character, bool multi);

	bool isAvailable() const override;

protected:
	std::tuple<int, int, bool> rollAttack() override;
	int rollDamage(bool crit) override;
};

}


