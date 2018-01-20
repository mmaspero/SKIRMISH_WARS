#pragma once

typedef enum players { NEUTRAL, USER, OPPONENT } player_t;
typedef enum playerStatus { PURCHASING, MOV_AND_ATT, WAITING } playerStatus_t;
typedef enum tileStatus { VISIBLE, FOG, SELECTED, CAN_ATTACK, CAN_MOVE } tileStatus_t;
typedef enum terrains { GRASS, RIVER, ROAD, FOREST, HILL, N_TERRAINS } terrain_t; 
typedef enum actions { MOVE, LOAD, UNLOAD, ATTACK, N_ACTIONS} action_t;