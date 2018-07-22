#pragma once

#include "../paths.h"

#define DEFAULT_SCREEN_W 1200.0f
#define DEFAULT_SCREEN_H 800.0f

#define MIN_SCREEN_W 1024.0f
#define MIN_SCREEN_H  768.0f

#define GUI_DEFAULT_BACKGROUND_COLOR {(float)0, (float)0, (float)0, (float)1}

#define DISPLAY_ICON IMAGE_PATH "myAvatar1.png"
#define WINDOW_TITLE "Skirmish Wars"

#define MY_AVATAR IMAGE_PATH "myAvatar1.png"
#define THEIR_AVATAR IMAGE_PATH "theirAvatar.png"

//Dimensiones de las contentBox. Son relativas: por ejemplo, width = 1 
//implica que ocupa todo el ancho de la pantalla

#define BOARD_LEFT_X	0.0
#define BOARD_TOP_Y		0.2
#define BOARD_W			0.75
#define BOARD_H			0.8

#define SCOREBOARD_LEFT_X	0.0
#define SCOREBOARD_TOP_Y	0.0
#define SCOREBOARD_W		0.75
#define SCOREBOARD_H		0.2

#define GAMESTATUS_LEFT_X	0.75
#define GAMESTATUS_TOP_Y	0.0
#define GAMESTATUS_W		0.25
#define GAMESTATUS_H		0.1

#define TEXTLOG_LEFT_X	0.75
#define TEXTLOG_TOP_Y	0.6
#define TEXTLOG_W		0.25
#define TEXTLOG_H		0.4

#define TOOLBOX_LEFT_X	0.75
#define TOOLBOX_TOP_Y	0.1
#define TOOLBOX_W		0.25
#define TOOLBOX_H		0.5