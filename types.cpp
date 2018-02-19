#include "types.h"
#include <unordered_map>

std::string getUnitString(unit_t type)
{
	std::string s;
	switch (type) {
	case RECON:		{ s = RE_STR; } break;
	case ROCKET:	{ s = RO_STR; } break;
	case MECH:		{ s = ME_STR; } break;
	case INFANTRY:	{ s = IN_STR; } break;
	case TANK:		{ s = TA_STR; } break;
	case ARTILLERY:	{ s = AR_STR; } break;
	case ANTIAIR:	{ s = AA_STR; } break;
	case APC:		{ s = AP_STR; } break;
	case MEDTANK:	{ s = MT_STR; }	break;
	}
	return s;
}

unit_t parseUnitString(std::string s)
{
	unit_t type = N_UNIT_TYPES;
	
	std::unordered_map<std::string, unit_t> units;
	units.emplace(std::string(RE_STR), RECON);
	units.emplace(std::string(RO_STR), ROCKET);
	units.emplace(std::string(ME_STR), MECH);
	units.emplace(std::string(IN_STR), INFANTRY);
	units.emplace(std::string(TA_STR), TANK);
	units.emplace(std::string(AR_STR), ARTILLERY);
	units.emplace(std::string(AA_STR), ANTIAIR);
	units.emplace(std::string(AP_STR), APC);
	units.emplace(std::string(MT_STR), MEDTANK);


	std::unordered_map<std::string, unit_t>::const_iterator it = units.find(s);
	if (it != units.end()) {
		type = it->second;
	}


	return type;
}

terrain_t parseTerrainChar(char c)
{
	switch (c) {
	case GRASS_CHR:		return GRASS;
	case RIVER_CHR:		return RIVER;
	case ROAD_CHR:		return ROAD;
	case FOREST_CHR:	return FOREST;
	case HILL_CHR:		return HILL;

	default:			return N_TERRAINS;
	}
}

terrain_t parseTerrainChar(std::string s)
{
	return terrain_t();
}

building_t parseBuildingChar(char c)
{
	switch (c) {
	case HQ_CHR:		return HEADQUARTERS;
	case FACTORY_CHR:	return FACTORY;
	case CITY_CHR:		return CITY;

	default:			return N_BUILDINGS;
	}
}
