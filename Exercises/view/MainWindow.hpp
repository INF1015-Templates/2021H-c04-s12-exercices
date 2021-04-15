#pragma once


#include <memory>

#include <QMainWindow>

#include <combat/CombatManager.hpp>


namespace Ui { class MainWindow; };

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(combat::CombatManager* combatMngr, QWidget *parent = Q_NULLPTR);
	~MainWindow();

public slots:
	void updateUi();
	void updateTakeActionBtn(int index);
	void updateTakeBonusActionBtn(int index);
	void addMsgToCombatLog(const QString& msg);
	void scrollToBottomOfLog(int rangeMin, int rangeMax);
	void takeAction();
	void passAction();
	void takeBonusAction();
	void passBonusAction();
	void handleCharacterDeath(characters::AbstractCharacter* character);

private:
	std::unique_ptr<Ui::MainWindow> ui;
	combat::CombatManager* combatMngr_;
	combat::Turn* npcTurn_;
	combat::Turn* playerTurn_;
};
