#pragma once


#define FONT_NAME					FONT_PATH "slkscr.ttf"
#define SMALL_FONT_SIZE_IN_HEIGHT	(1/18.0)
#define BIG_FONT_SIZE_IN_HEIGHT		(1.5 * SMALL_FONT_SIZE_IN_HEIGHT)
#define FONT_COLOR					al_color_name("black")

#define BUTTON_MARGIN(w, h)		(((w)>(h) ? h : w) / 20.0)
#define BUTTON_CORNER_ROUNDNESS 10

#define COIN_HEIGHT_IN_MARGINS	6	//La moneda que indica plata tiene COIN_HEIGHT_IN_MARGIN veces la altura del margen
#define LOGO_SIDE_IN_MARGINS	7

#define COIN_IMG "coin.png"

#define ANTIAIR_NAME "ANTIAIR"

#define TREAD_LOGO_BMP	IMAGE_PATH "tread_logo.png"
#define FOOT_LOGO_BMP	IMAGE_PATH "png7.png"
#define WHEEL_LOGO_BMP	TREAD_LOGO_BMP


#define ANTIAIR_NAME	"ANTIAIR"
#define APC_NAME		"APC"
#define ARTILLERY_NAME	"ARTILLERY"
#define INFANTRY_NAME	"INFANTRY"
#define MECH_NAME		"MECH"
#define MEDTANK_NAME	"MEDTANK"
#define RECON_NAME		"RECON"
#define ROCKET_NAME		"ROCKET"
#define TANK_NAME		"TANK"

#define DEF_STAT_NAME	"DEFENSE"
#define MP_STAT_NAME	"MAX MOVING POINTS"
#define RNG_STAT_NAME	"RANGE"
#define FP_STAT_NAME	"FIREPOWER"
#define RFP_STAT_NAME	"RED. FIREPOWER"
#define MC_STAT_NAME	"MOVING COST"

#define	CURRENT_MP_STAT_NAME "MP" 
#define CURRENT_HP_STAT_NAME "HP"