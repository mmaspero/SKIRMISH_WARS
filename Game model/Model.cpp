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

Model::Model(const char * map, player_t first, std::list<GenericEvent *> * softwareEvents, gui * g) : 
	user(USER), opponent(OPPONENT), m(map, first), g(g), softwareEvents(softwareEvents)
{
	valid = false;
#ifndef DEBUG_NOVIEW
	if (g != nullptr && softwareEvents != nullptr && m.isValid()) {
		user.setObserver(g->playerObserverFactory(&user));
		opponent.setObserver(g->playerObserverFactory(&opponent));
		for (unsigned int i = 0; i < B_H; i++) {
			for (unsigned int j = 0; j < B_W; j++) {
				m.board[i][j]->setObserver(g->tileObserverFactory(m.board[i][j]));
			}
		}

#else
	if (softwareEvents != nullptr && m.isValid()) {
#endif
		Unit::init(&m);
		unsigned int cities, factories, hqHp, units;
		m.playerInfo(USER, hqHp, factories, cities, units);
		user.updateStats(hqHp, factories, cities, units);
		m.playerInfo(OPPONENT, hqHp, factories, cities, units);
		opponent.updateStats(hqHp, factories, cities, units);

		GenericState * firstState = nullptr;
		if (first == USER) {
			firstState = new UserMoving();
			turn = USER;
		}
		else {
			firstState = new OpponentMoving();
			turn = OPPONENT;
		}
		fsm.setFirstState(firstState);
		active = nullptr;
		selected = nullptr;

		SkirmishEvent::setModel(this);
		valid = true;
	}
}

Model::~Model()
{
	;
}

bool Model::isValid()
{
	return valid;
}

GenericEvent * Model::validateOpponentAttack(attack att)
{
	GenericEvent * e = nullptr;
	
	if (fsm.state() == OPP_MOVING && m.hasUnit(att.getOrigin()) && m.getUnit(att.getOrigin())->getPlayer() == OPPONENT
		&& m.getUnit(att.getOrigin())->isActionValid(Action(ACT_ATTACK, att.getDestination()))) {
		e = new OpponentAttack(att.getOrigin(), att.getDestination(), att.getDice());
	}
	
	return e;
}

GenericEvent * Model::validateOpponentMove(move mov)
{
	GenericEvent * e = nullptr;
	
	if (fsm.state() == OPP_MOVING && m.hasUnit(mov.getOrigin()) && m.getUnit(mov.getOrigin())->getPlayer() == OPPONENT
		&& m.getUnit(mov.getOrigin())->isActionValid(Action(ACT_MOVE, mov.getDestination()))) {
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
		for (std::list<Action>::iterator it = actions.begin(); it != actions.end(); it++) {
			if (it->whereTo == p) {
				if (it->type == ACT_ATTACK) {
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

bool Model::nextTurn()
{
	bool valid = true;
	Player * prev = currPlayer();	//esto nunca va a devolver null si model existe!
	turn = (turn == USER ? OPPONENT : USER);
	Player * curr = currPlayer();	
	curr->collectIncome();

	std::list<std::pair<player_t, building_t>> captures;
	m.update(curr->id(), captures);
	while (captures.size()) {
		valid &= curr->registerCapture(true, captures.front().second);
		//es valido el update si cada paso es valido
		if (captures.front().first != NEUTRAL) {
			if (!prev->registerCapture(false, captures.front().second))
				softwareEvents->push_back(new SkirmishEvent((curr->id() == USER? EV_USER_WON : EV_OPPONENT_WON)));
		}
		captures.pop_front();
	}
	
	return valid;
}

Player * Model::currPlayer()
{
	return (turn == USER? &user : &opponent);
}
