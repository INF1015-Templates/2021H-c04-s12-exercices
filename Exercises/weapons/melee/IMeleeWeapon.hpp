#pragma once


#include <cstddef>
#include <cstdint>

#include <weapons/IWeapon.hpp>


namespace weapons::melee {

class IMeleeWeapon : public IWeapon {
public:
	virtual bool isMartial() const = 0;
	virtual bool isVersatile() const = 0;
	virtual bool isTwoHanded() const = 0;
	virtual void wieldOneHanded() = 0;
	virtual void wieldTwoHanded() = 0;
};

}


