#include "Recon.h"
#include "../unitInfo.h"

Recon::Recon(Point position, bool isMine) : Unit(RECON, position, isMine, RE_COST, RE_DEFENSE, RE_RNG_MIN, RE_RNG_MAX)
{
	restoreMPs();
}

unsigned int Recon::restoreMPs()
{
	movingPoints = RE_MP;
	return movingPoints;
}

unsigned int Recon::getTerrainMod(terrain_t t)
{
	switch (t) {
	case GRASS:
		return RE_MC_T;
	case RIVER:
		return RE_MC_R;
	case ROAD:
		return RE_MC_A;
	case FOREST:
		return RE_MC_F;
	case HILL:
		return RE_MC_H;

	default:
		return UINT_MAX;
	}
}

unsigned int Recon::getAttackMod(basicUnitType_t basicType, bool reduced)
{
	if (reduced) {
		switch (basicType) {
		case WHEEL:
			return RE_RFP_WHL;

		case FOOT:
			return RE_RFP_FT;

		case TREAD:
			return RE_RFP_TRD;

		default:
			return UINT_MAX;
		}
	}
	else {
		switch (basicType) {
		case WHEEL:
			return RE_FP_WHL;

		case FOOT:
			return RE_FP_FT;

		case TREAD:
			return RE_FP_TRD;

		default:
			return UINT_MAX;
		}
	}
}
