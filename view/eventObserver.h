#pragma once
#include "observer.h"

#include "../Game model/FSM/GenericEvent.h"
#include "gui.h"

class gui;

class eventObserver : public obs
{
public:
	eventObserver(GenericEvent ** events, gui * g);
	~eventObserver();

	virtual void update();

private:
	GenericEvent ** event;
	gui * g;

	void onTimeout();
	void onAck();
	void onGoToPurchase();
	void onUserPass();
	void onUserAttack();
	void onUserMove();
	void onUserPurchase();
	void onOppPass();
	void onOppAttack();
	void onOppMove();
	void onOppPurchase();
	void onUnitSelection();
	void onUnselect();
	void onWaitForYouWon();
	void onYouWon();
	void onError();
	void onQuit();
	void onUserWon();
	void onOpponentWon();
	void onButtonHover();
	void onButtonUnhover();
	void onButtonPress();
	void onButtonRelease();
	void onButtonSelect();
	void onButtonUnselect();
	void onTimeLeft();
	void onDisplayResize();
};

