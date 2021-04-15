
#include <QScrollBar>
#include <QMessageBox>

#include "MainWindow.hpp"
#include "ui_MainWindow.h"


MainWindow::MainWindow(combat::CombatManager* combatMngr, QWidget* parent)
: QMainWindow(parent),
  combatMngr_(combatMngr) {
	ui.reset(new Ui::MainWindow());
	ui->setupUi(this);

	combatMngr_->init();

	connect(combatMngr_->getPlayerTurn(), SIGNAL(started()), this, SLOT(updateUi()));
	connect(combatMngr_->getPlayerTurn(), SIGNAL(actionTaken()), this, SLOT(updateUi()));
	connect(combatMngr_->getPlayerTurn(), SIGNAL(bonusActionTaken()), this, SLOT(updateUi()));
	connect(combatMngr_->getPlayerTurn(), SIGNAL(ended()), this, SLOT(updateUi()));
	connect(combatMngr_->getNpcTurn(), SIGNAL(ended()), this, SLOT(updateUi()));
	connect(ui->scrollArea->verticalScrollBar(), SIGNAL(rangeChanged(int, int)), this, SLOT(scrollToBottomOfLog(int, int)));

	connect(ui->takeActionBtn, SIGNAL(clicked()), this, SLOT(takeAction()));
	connect(ui->passActionBtn, SIGNAL(clicked()), this, SLOT(passAction()));
	connect(ui->takeBonusActionBtn, SIGNAL(clicked()), this, SLOT(takeBonusAction()));
	connect(ui->passBonusActionBtn, SIGNAL(clicked()), this, SLOT(passBonusAction()));
	connect(ui->actionSelect, SIGNAL(activated(int)), this, SLOT(updateTakeActionBtn(int)));
	connect(ui->bonusActionSelect, SIGNAL(activated(int)), this, SLOT(updateTakeBonusActionBtn(int)));

	connect(combatMngr_, SIGNAL(message(const QString&)), this, SLOT(addMsgToCombatLog(const QString&)));
	connect(combatMngr_->getNpcTurn(), SIGNAL(message(const QString&)), this, SLOT(addMsgToCombatLog(const QString&)));
	connect(combatMngr_->getPlayerTurn(), SIGNAL(message(const QString&)), this, SLOT(addMsgToCombatLog(const QString&)));
	for (auto&& act : combatMngr_->getPlayerTurn()->getActions())
		connect((QObject*)act, SIGNAL(message(const QString&)), this, SLOT(addMsgToCombatLog(const QString&)));
	for (auto&& act : combatMngr_->getPlayerTurn()->getBonusActions())
		connect((QObject*)act, SIGNAL(message(const QString&)), this, SLOT(addMsgToCombatLog(const QString&)));
	for (auto&& act : combatMngr_->getNpcTurn()->getActions())
		connect((QObject*)act, SIGNAL(message(const QString&)), this, SLOT(addMsgToCombatLog(const QString&)));
	for (auto&& act : combatMngr_->getNpcTurn()->getBonusActions())
		connect((QObject*)act, SIGNAL(message(const QString&)), this, SLOT(addMsgToCombatLog(const QString&)));
	connect(combatMngr_, SIGNAL(characterDied(characters::AbstractCharacter*)), this, SLOT(handleCharacterDeath(characters::AbstractCharacter*)));

	auto&& name = combatMngr_->getPlayerCharacter()->getName();
	auto&& className = combatMngr_->getPlayerCharacter()->getClassName();
	auto&& level = combatMngr_->getPlayerCharacter()->getLevel();
	ui->playerCharLabel->setText(tr("%1, %2 (Lvl %3)").arg(name).arg(className).arg(level));

	updateUi();

	combatMngr->startCurrentTurn();
}

MainWindow::~MainWindow() {
	
}

void MainWindow::updateUi() {
	int hp = combatMngr_->getPlayerCharacter()->getCurrentHp();
	int maxHp = combatMngr_->getPlayerCharacter()->getMaxHp();
	ui->hpLabel->setText(tr("%1 / %2").arg(hp).arg(maxHp));

	bool actionAvailable = combatMngr_->getPlayerTurn()->isActionAvailable();
	QWidget* actionWidgets[] = {ui->actionSelect, ui->takeActionBtn, ui->passActionBtn};
	for (QWidget* wid : actionWidgets)
		wid->setEnabled(actionAvailable);
	bool bonusActionAvailable = combatMngr_->getPlayerTurn()->isBonusActionAvailable();
	QWidget* bonusActionWidgets[] = {ui->bonusActionSelect, ui->takeBonusActionBtn, ui->passBonusActionBtn};
	for (QWidget* wid : bonusActionWidgets)
		wid->setEnabled(bonusActionAvailable);

	if (combatMngr_->getCurrentTurn() == combatMngr_->getPlayerTurn()) {
		ui->actionSelect->clear();
		ui->bonusActionSelect->clear();
		for (auto&& elem : combatMngr_->getPlayerTurn()->getActions())
			ui->actionSelect->addItem(elem->getName());
		for (auto&& elem : combatMngr_->getPlayerTurn()->getBonusActions())
			ui->bonusActionSelect->addItem(elem->getName());
		updateTakeActionBtn(0);
		updateTakeBonusActionBtn(0);
	}
}

void MainWindow::updateTakeActionBtn(int index) {
	bool actionAvailable = combatMngr_->getPlayerTurn()->isActionAvailable();
	bool bonusActionAvailable = combatMngr_->getPlayerTurn()->isBonusActionAvailable();
	bool selectedActionAvailable = combatMngr_->getPlayerTurn()->getActions()[ui->actionSelect->currentIndex()]->isAvailable();
	bool selectedBonusActionAvailable = combatMngr_->getPlayerTurn()->getBonusActions()[ui->bonusActionSelect->currentIndex()]->isAvailable();
	ui->takeActionBtn->setEnabled(actionAvailable and selectedActionAvailable);
	ui->takeBonusActionBtn->setEnabled(bonusActionAvailable and selectedBonusActionAvailable);
}

void MainWindow::updateTakeBonusActionBtn(int index) {
	updateTakeActionBtn(index);
}

void MainWindow::addMsgToCombatLog(const QString& msg) {
	ui->combatLog->setText(ui->combatLog->text() + "\n" + msg);
}

void MainWindow::scrollToBottomOfLog(int rangeMin, int rangeMax) {
	ui->scrollArea->verticalScrollBar()->setValue(rangeMax);
}

void MainWindow::takeAction() {
	int index = ui->actionSelect->currentIndex();
	combatMngr_->getPlayerTurn()->takeAction(index);
}

void MainWindow::passAction() {
	combatMngr_->getPlayerTurn()->takeAction(-1);
}

void MainWindow::takeBonusAction() {
	int index = ui->bonusActionSelect->currentIndex();
	combatMngr_->getPlayerTurn()->takeBonusAction(index);
}

void MainWindow::passBonusAction() {
	combatMngr_->getPlayerTurn()->takeBonusAction(-1);
}

void MainWindow::handleCharacterDeath(characters::AbstractCharacter* character) {
	bool isPlayer = character == combatMngr_->getPlayerCharacter();
	QMessageBox::information(
		this,
		tr("GAME OVER"),
		tr("%1 character %2 has died").arg(isPlayer ? tr("Player") : tr("Non-player")).arg(character->getName())
	);
	close();
}
