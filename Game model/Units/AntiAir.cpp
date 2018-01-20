#include "AntiAir.h"
#include "../unitInfo.h"

AntiAir::AntiAir(Point position, bool isMine) : Unit(ANTIAIR, position, isMine, AA_COST, AA_DEFENSE, AA_RNG_MIN, AA_RNG_MAX)
{
	restoreMPs();
}

unsigned int AntiAir::restoreMPs()
{
	movingPoints = AA_MP;
	return movingPoints;
}
int AntiAir::getTerrainMod(terrain_t t)
{
	switch (t) {
	case GRASS:
		return AA_MC_T;
	case RIVER:
		return AA_MC_R;
	case ROAD:
		return AA_MC_A;
	case FOREST:
		return AA_MC_F;
	case HILL:
		return AA_MC_H;

	default:
		return UINT_MAX;
	}
}

unsigned int AntiAir::getAttackMod(unitType_t basicType)
{
	if (isReduced()) {
		switch (basicType) {
		case WHEEL:
			return AA_RFP_WHL;

		case FOOT:
			return AA_RFP_FT;

		case TREAD:
			return AA_RFP_TRD;

		default:
			return UINT_MAX;
		}
	}
	else {
		switch (basicType) {
		case WHEEL:
			return AA_FP_WHL;

		case FOOT:
			return AA_FP_FT;

		case TREAD:
			return AA_FP_TRD;

		default:
			return UINT_MAX;
		}
	}
}
