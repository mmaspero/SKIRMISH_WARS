#pragma once
#include <string>

#define B_W	16	//tamanio del mapa
#define	B_H	12


typedef enum players { NEUTRAL, USER, OPPONENT, N_PLAYERS } player_t;
typedef enum playerStatus { PURCHASING, MOV_AND_ATT, WAITING } playerStatus_t;
typedef enum tileStatus { VISIBLE, FOG, UNIT_REVEALED, SELECTED, CAN_ATTACK, CAN_MOVE } tileStatus_t;

typedef enum actions { ACT_MOVE, ACT_LOAD, ACT_UNLOAD, ACT_ATTACK, ACT_CAPTURE, N_ACTIONS} action_t;

typedef enum buildings { HEADQUARTERS, FACTORY, CITY, N_BUILDINGS } building_t;
#define CP_HQ			8
#define CP_DEFAULT		4

#define FACTORY_CHR	'm'	//ademas se especifica el jugador para todos los edificios
#define	HQ_CHR		'q'
#define CITY_CHR	'c'

typedef enum terrains { GRASS, RIVER, ROAD, FOREST, HILL, N_TERRAINS } terrain_t;
#define GRASS_CHR	't'
#define	RIVER_CHR	'r'
#define ROAD_CHR	'a'
#define FOREST_CHR	'f'
#define HILL_CHR	'h'

typedef enum unitTypes { WHEEL, FOOT, TREAD, N_BASIC_U_TYPES } basicUnitType_t;
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

std::string getUnitString(unit_t type);
unit_t parseUnitString(std::string s);			//devuelve N_UNIT_TYPES si no era valida
terrain_t parseTerrainChar(char c);				//devuelve N_TERRAINS si no era valido
building_t parseBuildingChar(char c);			//devuelve N_BUILDINGS si no era valido