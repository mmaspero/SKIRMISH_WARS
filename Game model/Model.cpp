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
#include "FSM/States/UserAttacking.h"
#include "Units\Apc.h"

Model::Model(const char * map, player_t first, std::list<GenericEvent *> * softwareEvents, gui * g) : 
	user(USER, first == USER), opponent(OPPONENT, first != USER), m(map, first), softwareEvents(softwareEvents)
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
		//target = selected = Point(B_H, B_W);
		activeUnit = nullptr;

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

GenericEvent * Model::validateOpponentAttack(attack * att)
{
	GenericEvent * e = nullptr;
	
	if ( att != nullptr &&
		( (fsm.state() == OPP_MOVING && m.hasUnit(att->getOrigin()) && m.getUnit(att->getOrigin())->getPlayer() == OPPONENT
			&& m.getUnit(att->getOrigin())->isActionValid(Action(ACT_ATTACK, att->getDestination())) ) || //ataque del oponente
			( (fsm.state() == WAITING_ATTACK_TURN_OVER || fsm.state() == USER_ATTACKING) && //contraataque
			((UserAttacking *)fsm.getState())->isWaitingFor(att->getOrigin(), att->getDestination())) ) ) {
		e = new OpponentAttack(att->getOrigin(), att->getDestination(), att->getDice());
	}
	
	return e;
}

GenericEvent * Model::validateOpponentMove(move * mov)
{
	GenericEvent * e = nullptr;
	
	if (mov != nullptr && fsm.state() == OPP_MOVING && m.hasUnit(mov->getOrigin()) && m.getUnit(mov->getOrigin())->getPlayer() == OPPONENT
		&& m.getUnit(mov->getOrigin())->isActionValid(Action(ACT_MOVE, mov->getDestination()))) {
		e = new OpponentMove(mov->getOrigin(), mov->getDestination());
	}

	return e;
}

GenericEvent * Model::validateOpponentPurchase(purchase * purch)
{
	GenericEvent * e = nullptr;
	
	if (purch != nullptr && m.canPurchaseUnit(purch->getPossition(), OPPONENT)) {
		//aca ya se que el oponente tiene una fabrica vacia ahi, falta ver si le alcanza la plata
		unit_t type = parseUnitString(purch->getEjercitoId());
		if (Unit::getCost(type) <= opponent.getMoney()) {
			e = new OpponentPurchase(purch->getPossition(), type);
		}
	}

	return e;
}

GenericEvent * Model::getTileEvent(Point p)
{
	GenericEvent * e = nullptr;

	switch (fsm.state()) {

	case USER_MOVING: {
		if (m.hasUnit(p) && m.getUnit(p)->getPlayer() == USER) {
			e = new UnitSelection(p);
		}
	} break;

	case UNIT_SELECTED: {
		for (std::list<Action>::iterator it = actions.begin(); it != actions.end() && e == nullptr; it++) {
			if (it->whereTo == p) {
				if (it->basicType() == ACT_ATTACK) {
					e = new UserAttack(p);
				}
				else if (it->basicType() == ACT_MOVE){
					e = new UserMove(p);
				}
			}
		}

		if (e == nullptr) {
			e = new SkirmishEvent(EV_UNSELECT);
		}
	} break;

	case PURCHASE_SELECTED: {
		if (m.canPurchaseUnit(p, USER)) {
			e = new UserPurchase(p);
		}
		else {
			e = new SkirmishEvent(EV_UNSELECT);
		}
	} break;

	}

	return e;
}

bool Model::dispatch(GenericEvent * ev)
{
	fsm.dispatch(ev);
	return (fsm.state() < N_STATES);
}

bool Model::playerWon(player_t p)
{
	if (p == USER) {
		return opponent.wasDefeated();
	}
	else {
		return user.wasDefeated();
	}
}

void Model::notifyUserVictory()
{
	if (opponent.wasDefeated()) {
		softwareEvents->push_back(new GenericEvent(EV_USER_WON));
	}
}

void Model::showAvailableFactories()
{
	clearActions();
	for (unsigned int i = 0; i < B_H; i++) {
		for (unsigned int j = 0; j < B_W; j++) {
			Point p(i, j);
			if (m.getBuildingPlayer(p) == turn && m.getBuilding(p)->getType() == FACTORY) {
				m.showAction(p, ACT_MOVE);
				actions.push_back(Action(ACT_MOVE, p)); //para registrarlo y borrarlo despues
			}
		}
	}
}

void Model::showPossibleActions(Point p)
{
	Unit * u = m.getUnit(p);
	if (u != nullptr && u->getPlayer() == USER) {
		m.select(p);
		clearActions();
		u->getPossibleActions(actions);

		for (std::list<Action>::iterator it = actions.begin(); it != actions.end(); it++) {
			m.showAction(it->whereTo, it->basicType());
		}
		actions.push_back(Action(N_ACTIONS, p)); // para que se vaya despues la seleccion
	}
}

void Model::clearActions()
{
	for (std::list<Action>::iterator it = actions.begin(); it != actions.end(); it++) {
		m.showAction(it->whereTo, N_ACTIONS);
	}

	actions.clear();
}

bool Model::nextTurn()
{
	bool valid = true;
	Player * prev = currPlayer();	//esto nunca va a devolver null si model existe!
	turn = (turn == USER ? OPPONENT : USER);
	Player * curr = currPlayer();
	
	if (prev->getStatus() == MOV_AND_ATT) {
		prev->nextState();	//paso primero a purchasing
	}
	prev->nextState(); //y despues a waiting
	 
	curr->collectIncome();
	m.update(curr->id());

	unsigned int cities, factories, hqHp, units; //solo me importan los edificios pero tengo que preguntar todo 
	m.playerInfo(USER, hqHp, factories, cities, units);
	user.updateStats(hqHp, factories, cities, units);
	m.playerInfo(OPPONENT, hqHp, factories, cities, units);
	opponent.updateStats(hqHp, factories, cities, units);

	if (prev->wasDefeated()) {
		softwareEvents->push_back(new GenericEvent(turn == USER ? EV_WAIT_FOR_YOU_WON : EV_OPPONENT_WON));
	}
	else {
		curr->nextState();
	}

	return valid;
}

bool Model::registerAttack(Point origin, Point target, unsigned int dice)
{
	bool valid = false;
	player_t attacker = m.getUnitPlayer(origin);
	Unit * u = m.getUnit(origin);
	//this->target = target; 
	
	if (u != nullptr) {
		if (u->attack(Action(ACT_ATTACK, target), dice)) {
			valid = true;
			checkForUnitDeath(target);
			m.notifyTileObserver(target);
		}
		else if (u->startCapture(Action(ACT_CAPTURE, target))) {
			//si no hay una unidad en el target, si o si tiene que ser una captura!
			valid = true;
		}
	}

	if (valid) {
		updateActiveUnit(u);
		if (turn != attacker) { //en el contra ataque no hago esto!
			m.revealUnit(origin, attacker == USER ? OPPONENT : USER);
		}
		if (turn == USER && attacker == USER) {
			//solo en el ataque de la unidad!
			m.unselect(origin);
			clearActions();
		}
	}
	
	return valid;
}

void Model::endAttack(Point attacker)
{
	m.hideUnit(attacker, turn == USER? OPPONENT : USER);
}

bool Model::registerMove(Point p0, Point pf)
{
	bool valid = false;

	if (m.getUnitPlayer(p0) == turn) {
		Unit * u = m.getUnit(p0);
		std::list<Action> moves;
		u->getPossibleActions(moves);

		while (moves.size() && !(moves.front().basicType() == ACT_MOVE && moves.front().whereTo == pf)) {
			moves.pop_front();
		}

		if (moves.size()) {
			switch (moves.front().type) {
			case ACT_MOVE: {
				valid = u->move(moves.front());
			} break;
			case ACT_LOAD: {
				valid = u->loadIntoApc(moves.front());
			} break;
			case ACT_UNLOAD: {
				if (p0 == pf) {
					valid = ((Apc *)u)->startUnloading();
				}
				else {
					valid = ((Apc *)m.getUnit(p0))->unload(pf);
				}
			} break;
				//default: valid queda en false
			}
		}
		
		if (valid) {
			updateActiveUnit(u);

			if (u->getPlayer() == USER) {
				m.unselect(p0);
				clearActions();
			}
		}
	}

	return valid;
}

bool Model::registerPurchase(player_t who, Point factory, unit_t type)
{
	bool valid = false;
	
	if (turn == who) {
		if (currPlayer()->getStatus() == MOV_AND_ATT) {
			currPlayer()->nextState();
		}

		Unit * purch = currPlayer()->buy(type, factory);

		if (purch != nullptr && m.updateUnitPos(purch, purch->getPosition())) {
			valid = true;
			clearActions();
		}
	}

	return valid;
}

void Model::checkForUnitDeath(Point where)
{
	player_t whose = m.getUnitPlayer(where);
	Player * player;
	switch (whose) {
	case USER:		{ player = &user; }		break;
	case OPPONENT:	{ player = &opponent; } break;
	default:		{ player = nullptr; }	break;
	}

	if (player != nullptr && !m.getUnit(where)->isAlive()) {
		player->unitKilled();
		if (player->id() == USER && activeUnit->getPosition() == where) {
			clearActions();
		}
		m.clearTile(where);
		if (player->wasDefeated()) {
			softwareEvents->push_back(new GenericEvent(whose == USER ? EV_OPPONENT_WON : EV_WAIT_FOR_YOU_WON));
		}
	}

}

Player * Model::currPlayer()
{
	return (turn == USER? &user : &opponent);
}

void Model::updateActiveUnit(Unit * u)
{
	if (valid && u != activeUnit) {
		if (activeUnit != nullptr) {
			activeUnit->endTurn();
		}
		activeUnit = u;
	}

	//if (valid && selected != p0) {
	//	if (m.hasUnit(selected)) {
	//		m.getUnit(selected)->endTurn(); // si estaba en idle no va a pasar a postactive (:
	//	}
	//	selected = p0;
	//}
}
