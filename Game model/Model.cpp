#include "Model.h"
#include "FSM/States/UserMoving.h"
#include "FSM\States\OpponentMoving.h"
#include "FSM/Events/UnitSelection.h"
#include "FSM/Events/UserAttack.h"
#include "FSM\Events\UserMove.h"
#include "FSM/Events/UserPurchase.h"
#include "FSM/Events/OpponentAttack.h"
#include "FSM/Events/OpponentMove.h"
#include "FSM/Events/OpponentPurchase.h"

Model::Model(const char * map, player_t first, gui * g) : user(USER), opponent(OPPONENT), m(map, first), g(g)
{
	if (g != nullptr && m.isValid()) {
		user.setObserver(g->playerObserverFactory(&user));
		opponent.setObserver(g->playerObserverFactory(&opponent));
		
		for (unsigned int i = 0; i < B_H; i++) {
			for (unsigned int j = 0; j < B_W; j++) {
				m.board[i][j]->setObserver(g->tileObserverFactory(m.board[i][j]));
			}
		}

		GenericState * firstState = nullptr;
		if (first == USER) {
			firstState = new UserMoving();
		}
		else {
			firstState = new OpponentMoving();
		}
		fsm.setFirstState(firstState);
		active = nullptr;
		selected = nullptr;

		SkirmishEvent::setModel(this);
	}
}

Model::~Model()
{
	;
}

GenericEvent * Model::validateOpponentAttack(attack att)
{
	GenericEvent * e = nullptr;
	
	if (fsm.state() == OPP_MOVING && m.hasUnit(att.getOrigin()) && m.getUnit(att.getOrigin())->getPlayer() == OPPONENT
		&& m.getUnit(att.getOrigin())->isActionValid(&Attack(att.getOrigin(), att.getDestination()))) {
		e = new OpponentAttack(att.getOrigin(), att.getDestination(), att.getDice());
	}
	
	return e;
}

GenericEvent * Model::validateOpponentMove(move mov)
{
	GenericEvent * e = nullptr;
	
	if (fsm.state() == OPP_MOVING && m.hasUnit(mov.getOrigin()) && m.getUnit(mov.getOrigin())->getPlayer() == OPPONENT
		&& m.getUnit(mov.getOrigin())->isActionValid(&(Action(ACT_MOVE, mov.getDestination())))) {
		e = new OpponentMove(mov.getOrigin(), mov.getDestination());
	}

	return e;
}

GenericEvent * Model::validateOpponentPurchase(purchase purch)
{
	GenericEvent * e = nullptr;
	
	if (m.canPurchaseUnit(purch.getPossition(), OPPONENT)) {
		//aca ya se que el oponente tiene una fabrica vacia ahi, falta ver si le alcanza la plata
		unit_t type = parseUnitString(purch.getEjercitoId());
		if (Unit::getCost(type) <= opponent.getMoney()) {
			e = new OpponentPurchase(purch.getPossition(), type);
		}
	}

	return e;
}

GenericEvent * Model::getTileEvent(Point p)
{
	GenericEvent * e = nullptr;

	switch (fsm.state()) {

	case USER_MOVING: {
		if (m.hasUnit(p) && m.getUnit(p)->getPlayer() == USER && m.getUnit(p)->hasValidActions()) {
			e = new UnitSelection(p);
		}
	} break;

	case UNIT_SELECTED: {
		for (std::list<Action *>::iterator it = actions.begin(); it != actions.end(); it++) {
			if ((*it)->whereTo == p) {
				if ((*it)->type == ACT_ATTACK) {
					e = new UserAttack(selected->getPosition(), p);
				}
				else {
					e = new UserMove(selected->getPosition(), p);
				}
			}
			else {
				e = new SkirmishEvent(EV_UNSELECT);
			}
		}
	} break;

	case PURCHASE_SELECTED: {
		if (m.canPurchaseUnit(p, USER)) {
			e = new UserPurchase(p, active->getType());
		}
		else {
			e = new SkirmishEvent(EV_UNSELECT);
		}
	} break;

	}

	return e;
}
