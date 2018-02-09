#include "Rocket.h"
#include "../unitInfo.h"

Rocket::Rocket(Point position, bool isMine) : Unit (ROCKET, position, isMine, RO_COST, RO_DEFENSE, RO_RNG_MIN, RO_RNG_MAX)
{
	restoreMPs();
}

unsigned int Rocket::restoreMPs()
{
	movingPoints = RO_MP;
	return movingPoints;
}

unsigned int Rocket::getTerrainMod(terrain_t t)
{
	switch (t) {
	case GRASS:
		return RO_MC_T;
	case RIVER:
		return RO_MC_R;
	case ROAD:
		return RO_MC_A;
	case FOREST:
		return RO_MC_F;
	case HILL: 
		return RO_MC_H;
		
	default:
		return UINT_MAX;
	}
}

unsigned int Rocket::getAttackMod(basicUnitType_t basicType)
{
	if (isReduced()) {
		switch (basicType) {
		case WHEEL:
			return RO_RFP_WHL;

		case FOOT:
			return RO_RFP_FT;

		case TREAD:
			return RO_RFP_TRD;

		default:
			return UINT_MAX;
		}
	}
	else {
		switch (basicType) {
		case WHEEL:
			return RO_FP_WHL;

		case FOOT:
			return RO_FP_FT;

		case TREAD:
			return RO_FP_TRD;

		default:
			return UINT_MAX;
		}
	}
}

