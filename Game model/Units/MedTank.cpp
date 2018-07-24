#include "MedTank.h"
#include "../unitInfo.h"

MedTank::MedTank(Point position, bool isMine) : Unit(MEDTANK, position, isMine, MT_COST, MT_DEFENSE, MT_RNG_MIN, MT_RNG_MAX)
{
	restoreMPs();
}

unsigned int MedTank::restoreMPs()
{
	movingPoints = MT_MP;
	return movingPoints;
}

unsigned int MedTank::getTerrainMod(terrain_t t)
{
	switch (t) {
	case GRASS:
		return MT_MC_T;
	case RIVER:
		return MT_MC_R;
	case ROAD:
		return MT_MC_A;
	case FOREST:
		return MT_MC_F;
	case HILL:
		return MT_MC_H;

	default:
		return UINT_MAX;
	}
}

unsigned int MedTank::getAttackMod(basicUnitType_t basicType, bool reduced)
{
	if (reduced) {
		switch (basicType) {
		case WHEEL:
			return MT_RFP_WHL;

		case FOOT:
			return MT_RFP_FT;

		case TREAD:
			return MT_RFP_TRD;

		default:
			return UINT_MAX;
		}
	}
	else {
		switch (basicType) {
		case WHEEL:
			return MT_FP_WHL;

		case FOOT:
			return MT_FP_FT;

		case TREAD:
			return MT_FP_TRD;

		default:
			return UINT_MAX;
		}
	}
}
