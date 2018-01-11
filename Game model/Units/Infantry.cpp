#include "Infantry.h"
#include "../unitInfo.h"

Infantry::Infantry(Point position, bool isMine) : Unit(INFANTRY, position, isMine, IN_DEFENSE, IN_RNG_MIN, IN_RNG_MAX)
{
	restoreMPs();
}

unsigned int Infantry::restoreMPs()
{
	movingPoints = IN_MP;
	return movingPoints;
}
int Infantry::getTerrainMod(terrain_t t)
{
	switch (t) {
	case GRASS:
		return IN_MC_T;
	case RIVER:
		return IN_MC_R;
	case ROAD:
		return IN_MC_A;
	case FOREST:
		return IN_MC_F;
	case HILL:
		return IN_MC_H;

	default:
		return UINT_MAX;
	}
}

unsigned int Infantry::getAttackMod(unitType_t basicType)
{
	if (isReduced()) {
		switch (basicType) {
		case WHEEL:
			return IN_RFP_WHL;

		case FOOT:
			return IN_RFP_FT;

		case TREAD:
			return IN_RFP_TRD;

		default:
			return UINT_MAX;
		}
	}
	else {
		switch (basicType) {
		case WHEEL:
			return IN_FP_WHL;

		case FOOT:
			return IN_FP_FT;

		case TREAD:
			return IN_FP_TRD;

		default:
			return UINT_MAX;
		}
	}
}
