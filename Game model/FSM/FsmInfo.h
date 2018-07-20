#pragma once

typedef enum events {	
						EV_TIMEOUT, 
						EV_ACK,
						EV_GO_TO_PURCHASE,
						EV_USER_PASS, 
						EV_USER_ATTACK, 
						EV_USER_MOVE, 
						EV_USER_PURCHASE,
						EV_OPP_PASS, 
						EV_OPP_ATTACK, 
						EV_OPP_MOVE, 
						EV_OPP_PURCHASE,	//OPP es de OPPONENT
						EV_PURCH_SELECTION, 
						EV_UNIT_SELECTION, 
						EV_UNSELECT,
						EV_WAIT_FOR_YOU_WON,
						EV_YOU_WON,
						

						EV_ERROR,
						EV_QUIT,				
						

						//ESTOS NO LLEGAN A LA FSM!!
						EV_USER_WON, 
						EV_OPPONENT_WON,
						EV_BUTTON_HOVER, 
						EV_BUTTON_UNHOVER,
						EV_BUTTON_PRESS, 
						EV_BUTTON_RELEASE,
						EV_BUTTON_SELECT, 
						EV_BUTTON_UNSELECT,
						EV_TIME_LEFT,
						EV_DISPLAY_RESIZE, 
						N_EVENTS

					} event_t; 

typedef enum states {	
						OPP_MOVING, 
						OPP_PURCHASING, WAITING_OPP_PASS,
						USER_MOVING, UNIT_SELECTED, WAITING_MOVE_ACK, USER_ATTACKING, 
						USER_PURCHASING, PURCHASE_SELECTED, WAITING_PURCH_ACK,
						WAITING_ACK_TURN_OVER, WAITING_ATTACK_TURN_OVER,
						WAITING_YOU_WON,

						FSM_CRASHED,	//el estado en el que se queda si exploto todo
						N_STATES
					} state_t;
