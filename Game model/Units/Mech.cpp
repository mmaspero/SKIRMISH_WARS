#include "Mech.h"
#include "../unitInfo.h"

Mech::Mech(Point position, bool isMine) : Unit(MECH, position, isMine, ME_DEFENSE, ME_RNG_MIN, ME_RNG_MAX)
{
	restoreMPs();
}

unsigned int Mech::restoreMPs()
{
	movingPoints = ME_MP;
	return movingPoints;
}
int Mech::getTerrainMod(terrain_t t)
{
	switch (t) {
	case GRASS:
		return ME_MC_T;
	case RIVER:
		return ME_MC_R;
	case ROAD:
		return ME_MC_A;
	case FOREST:
		return ME_MC_F;
	case HILL:
		return ME_MC_H;

	default:
		return UINT_MAX;
	}
}

unsigned int Mech::getAttackMod(unitType_t basicType)
{
	if (isReduced()) {
		switch (basicType) {
		case WHEEL:
			return ME_RFP_WHL;

		case FOOT:
			return ME_RFP_FT;

		case TREAD:
			return ME_RFP_TRD;

		default:
			return UINT_MAX;
		}
	}
	else {
		switch (basicType) {
		case WHEEL:
			return ME_FP_WHL;

		case FOOT:
			return ME_FP_FT;

		case TREAD:
			return ME_FP_TRD;

		default:
			return UINT_MAX;
		}
	}
}
