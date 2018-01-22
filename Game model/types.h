#pragma once

typedef enum players { NEUTRAL, USER, OPPONENT } player_t;
typedef enum playerStatus { PURCHASING, MOV_AND_ATT, WAITING } playerStatus_t;
typedef enum tileStatus { VISIBLE, FOG, SELECTED, CAN_ATTACK, CAN_MOVE } tileStatus_t;
typedef enum actions { MOVE, LOAD, UNLOAD, ATTACK, N_ACTIONS} action_t;

typedef enum buildings { HEADQUARTERS, FACTORY, CITY, N_BUILDINGS } building_t;
#define FACTORY_STR	"m"	//ademas se especifica el jugador para todos los edificios
#define	HQ_STR		"q"
#define CITY_STR	"c"

typedef enum terrains { GRASS, RIVER, ROAD, FOREST, HILL, N_TERRAINS } terrain_t;
#define GRASS_STR	"t"
#define	RIVER_STR	"r"
#define ROAD_STR	"a"
#define FOREST_STR	"f"
#define HILL_STR	"h"

typedef enum unitTypes { WHEEL, FOOT, TREAD, N_B_TYPES } unitType_t;
typedef enum units {
	RECON, ROCKET,							//	WHEEL
	MECH, INFANTRY,							//	FOOT
	TANK, ARTILLERY, ANTIAIR, APC, MEDTANK,	//	TREAD
	N_UNIT_TYPES
} unit_t;

#define RE_STR		"re"		
#define RO_STR		"ro"
#define ME_STR		"me"
#define IN_STR		"in"
#define TA_STR		"ta"
#define AR_STR		"ar"
#define	AA_STR		"aa"
#define	AP_STR		"ap"
#define MT_STR		"mt"

#define UNIT_TOKEN	'+'	//caracter que separa el terreno/edificio de la unidad
