
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


void mockFight() {
	view::Printer printer;

	stats::Ability abilities[] = {
		{stats::STR, 10},
		{stats::DEX, 18},
		{stats::CON, 14},
		{stats::INT, 12},
		{stats::WIS, 16},
		{stats::CHA, 8}
	};
	characters::classes::Monk char1("Ya boi", abilities);
	characters::classes::Monk char2("Ya other boi", abilities);
	combat::classes::MonkTurn turn1(&char1, &char2);
	combat::classes::MonkTurn turn2(&char2, &char1);

	QObject::connect(&turn1, SIGNAL(message(const QString&)), &printer, SLOT(printMsg(const QString&)));
	QObject::connect(&turn2, SIGNAL(message(const QString&)), &printer, SLOT(printMsg(const QString&)));

	auto&& actions = turn1.getActions();
	auto&& bonusAcn = turn1.getBonusActions();

	turn1.start();
	turn1.takeAction(0);
	turn1.takeBonusAction(-1);
	qInfo() << "hi";
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
	//mockFight();
	QApplication a(argc, argv);
	combat::CombatManager combatManager;
	MainWindow w(&combatManager);
	w.show();
	return a.exec();
}
