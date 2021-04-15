
#include <cstddef>
#include <cstdint>

#include <cstdio>
#include <cmath>
#include <span>
#include <unordered_map>
#include <array>
#include <iostream>

#include <QObject>
#include <QApplication>
#include <QDebug>
#include <QTextStream>
#include <QString>

#include <utils/Die.hpp>
#include <utils/DiceRoller.hpp>
#include <weapons/melee/GenericMeleeWeapon.hpp>
#include <stats/Ability.hpp>
#include <stats/StatBlock.hpp>
#include <characters/classes/Monk.hpp>
#include <characters/classes/Fighter.hpp>
#include <combat/classes/MonkTurn.hpp>
#include <view/InfoPrinter.hpp>
#include <combat/CombatManager.hpp>
#include <view/MainWindow.hpp>


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
	QApplication a(argc, argv);
	combat::CombatManager combatManager;
	MainWindow w(&combatManager);
	w.show();
	return a.exec();
}
