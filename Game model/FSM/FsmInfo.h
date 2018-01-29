#pragma once

typedef enum events {	
						TIMEOUT, ACK, GO_TO_PURCHASE,
						USER_PASS, USER_ATTACK, USER_MOVE, USER_PURCHASE,
						OPP_PASS, OPP_ATTACK, OPP_MOVE, OPP_PURCHASE,	//OPP es de OPPONENT
						PURCH_SELECTION, UNIT_SELECTION, UNSELECT,
						N_EVENTS 
					} event_t; 

typedef enum states {	
						OPP_MOVING, OPP_PURCHASING, WAITING_OPP_PASS,
						USER_MOVING, UNIT_SELECTED, WAITING_MOVE_ACK, USER_ATTACKING, 
						USER_PURCHASING, PURCHASE_SELECTED, WAITING_PURCH_ACK,
						WAITING_ACK_TURN_OVER, WAITING_ATTACK_TURN_OVER,
						N_STATES
					} state_t;