#include "Artillery.h"
#include "../unitInfo.h"

Artillery::Artillery(Point position, bool isMine) : Unit(ARTILLERY, position, isMine, AR_COST, AR_DEFENSE, AR_RNG_MIN, AR_RNG_MAX)
{
	restoreMPs();
}

unsigned int Artillery::restoreMPs()
{
	movingPoints = AR_MP;
	return movingPoints;
}

unsigned int Artillery::getTerrainMod(terrain_t t)
{
	switch (t) {
	case GRASS:
		return AR_MC_T;
	case RIVER:
		return AR_MC_R;
	case ROAD:
		return AR_MC_A;
	case FOREST:
		return AR_MC_F;
	case HILL:
		return AR_MC_H;

	default:
		return UINT_MAX;
	}
}

unsigned int Artillery::getAttackMod(basicUnitType_t basicType, bool reduced)
{
	if (reduced) {
		switch (basicType) {
		case WHEEL:
			return AR_RFP_WHL;

		case FOOT:
			return AR_RFP_FT;

		case TREAD:
			return AR_RFP_TRD;

		default:
			return UINT_MAX;
		}
	}
	else {
		switch (basicType) {
		case WHEEL:
			return AR_FP_WHL;

		case FOOT:
			return AR_FP_FT;

		case TREAD:
			return AR_FP_TRD;

		default:
			return UINT_MAX;
		}
	}
}
