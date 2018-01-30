#include "Model.h"
#include "FSM/States/UserMoving.h"
#include "FSM\States\OpponentMoving.h"

Model::Model(const char * map, player_t first, gui g) : user(USER), opponent(OPPONENT), m(map, first), g(g)
{
	if (m.isValid()) {
		user.setObserver(g.playerObserverFactory(&user));
		opponent.setObserver(g.playerObserverFactory(&opponent));
		
		for (unsigned int i = 0; i < B_H; i++) {
			for (unsigned int j = 0; j < B_W; j++) {
				m.board[i][j]->setObserver(g.tileObserverFactory(m.board[i][j]));
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
	}
}

bool Model::validMove(Point p0, Point pf)
{
	bool valid = false;
	
	if (fsm.state() == OPP_MOVING) {
		if (m.hasUnit(p0) && m.isInMap(pf) && !m.hasUnit(pf)) {
			Unit * u = m.getUnit(p0);
			if (u->getPlayer() == OPPONENT) {
				u->getPossibleActions(moves, attacks);

				std::list<Action>::iterator it = moves.begin();
				while (it != moves.end() && it->whereTo != pf) {
					it++;
				}

				if (it != moves.end()) {
					valid = true;
				}
				moves.clear();
				attacks.clear();
			}
		}
	}

	return valid;
}

bool Model::validAttack(Point p0, Point pf)
{
	bool valid = false;

	if (fsm.state() == OPP_MOVING) {
		if (m.hasUnit(p0) && m.hasUnit(pf)) {
			Unit * attacker = m.getUnit(p0);
			Unit * attacked = m.getUnit(pf);
			if (attacker->getPlayer() == OPPONENT && attacked->getPlayer() == USER) {
				attacker->getPossibleActions(moves, attacks);

				std::list<Attack>::iterator it = attacks.begin();
				while (it != attacks.end() && it->whereTo != pf) {
					it++;
				}

				if (it != attacks.end()) {
					valid = true;
				}
				moves.clear();
				attacks.clear();
			}
		}
	}

	return valid;
}

bool Model::validAction(action_t type, Point p0, Point pf)
{
	return (type == ATTACK ? validAttack(p0, pf) : validMove(p0, pf));
}


