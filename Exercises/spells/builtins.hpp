#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>
#include <optional>

#include <QString>

#include <utils/DiceRoller.hpp>
#include <spells/GenericSpell.hpp>


namespace spells {

using namespace utils::dice;


class MagicMissile : public GenericSpell<1, 3, d4_t, 3, false> {
public:
	MagicMissile() : GenericSpell("Magic Missile") { }
};

class BurningHands : public GenericSpell<1, 3, d6_t, 0, false, stats::DEX> {
public:
	BurningHands() : GenericSpell("Burning Hands") { }
};

class FireBall : public GenericSpell<3, 8, d6_t, 3, false, stats::DEX> {
public:
	FireBall() : GenericSpell("Fire Ball") { }
};

}


