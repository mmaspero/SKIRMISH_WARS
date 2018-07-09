#pragma once

#define CONTENT_MARGIN	15.0		//margen entre el verdadero inicio de la caja del textbox y los limites del texto
#define CORNER_ROUNDNESS 20.0
#define DISPLAY_SECTION_MARGIN 10.0	//margen para la "caja" que contiene todos los elementos del display
									//EJ.: en un display de ancho 600, si dice que la ubicacion de un elemento
									//del display va entre 300 a 600, en realidad, va entre:
									//(300 + DISPLAY_SECTION_MARGIN) y (600 - DISPLAY_SECTION_MARGIN)


#define DEFAULT_BACKGROUND_COLOR {(float)0, (float)0, (float)0, (float)1}
#define DEFAULT_FRAME_BASE_COLOR {(float)0.45, (float)1, (float)0, (float)1}	//"lawngreen"
#define DEFAULT_FRAME_HIGHLIGHT_COLOR {(float)0, (float)0, (float)0, (float)1}

#define FRAME_WIDTH 10
#define FRAME_HIGHLIGHT_WIDTH 2