#pragma once

#include "sprite_config.h"
#include "productButton_config.h"

#define WHEEL_BG_COLOR	"thistle"		//TODO: todos los colores o con nombres o con rgb
#define TREAD_BG_COLOR  "aquamarine"	//TODO: unificar con los defines de toolbox.cpp
#define FOOT_BG_COLOR	"beige"

#define TREAD_LOGO_BMP IMAGE_PATH "tread_logo.png"
#define FOOT_LOGO_BMP TREAD_LOGO_BMP
#define WHEEL_LOGO_BMP TREAD_LOGO_BMP

#define BUTTONS_PER_ROW 3
#define PRODUCT_SECTION_RELATIVE_H 0.95
#define BUTTON_MARGIN(w, h) (((w)>(h) ? h : w) / 20.0)
#define BUTTON_CORNER_ROUNDNESS 10

