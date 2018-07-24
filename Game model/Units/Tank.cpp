#include "Tank.h"
#include "../unitInfo.h"

Tank::Tank(Point position, bool isMine) : Unit(TANK, position, isMine, TA_COST, TA_DEFENSE, TA_RNG_MIN, TA_RNG_MAX)
{
	restoreMPs();
}

unsigned int Tank::restoreMPs()
{
	movingPoints = TA_MP;
	return movingPoints;
}

unsigned int Tank::getTerrainMod(terrain_t t)
{
	switch (t) {
	case GRASS:
		return TA_MC_T;
	case RIVER:
		return TA_MC_R;
	case ROAD:
		return TA_MC_A;
	case FOREST:
		return TA_MC_F;
	case HILL:
		return TA_MC_H;

	default:
		return UINT_MAX;
	}
}

unsigned int Tank::getAttackMod(basicUnitType_t basicType, bool reduced)
{
	if (reduced) {
		switch (basicType) {
		case WHEEL:
			return TA_RFP_WHL;

		case FOOT:
			return TA_RFP_FT;

		case TREAD:
			return TA_RFP_TRD;

		default:
			return UINT_MAX;
		}
	}
	else {
		switch (basicType) {
		case WHEEL:
			return TA_FP_WHL;

		case FOOT:
			return TA_FP_FT;

		case TREAD:
			return TA_FP_TRD;

		default:
			return UINT_MAX;
		}
	}
}

