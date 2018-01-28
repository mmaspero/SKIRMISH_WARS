#include "GenericState.h"

GenericState::GenericState(state_t id) : id(id)
{
	;
}

state_t GenericState::name() const
{
	return id;
}

GenericState * GenericState::onTimeout(GenericEvent *)
{
	return nullptr;
}

GenericState * GenericState::onAck(GenericEvent *)
{
	return nullptr;
}

GenericState * GenericState::onUserPass(GenericEvent *)
{
	return nullptr;
}

GenericState * GenericState::onUserAttack(GenericEvent *)
{
	return nullptr;
}

GenericState * GenericState::onUserMove(GenericEvent *)
{
	return nullptr;
}

GenericState * GenericState::onUserPurchase(GenericEvent *)
{
	return nullptr;
}

GenericState * GenericState::onGoToPurchase(GenericEvent *)
{
	return nullptr;
}

GenericState * GenericState::onOpponentPass(GenericEvent *)
{
	return nullptr;
}

GenericState * GenericState::onOpponentAttack(GenericEvent *)
{
	return nullptr;
}

GenericState * GenericState::onOpponentMove(GenericEvent *)
{
	return nullptr;
}

GenericState * GenericState::onOpponentPurchase(GenericEvent *)
{
	return nullptr;
}

GenericState * GenericState::onPurchaseSelection(GenericEvent *)
{
	return nullptr;
}

GenericState * GenericState::onUnitSelection(GenericEvent *)
{
	return nullptr;
}

GenericState * GenericState::onUnselect(GenericEvent *)
{
	return nullptr;
}

//handlers por default: no hacen nada o error?
