#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_color.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_ttf.h>



/*******************************************************************************************************
drawTexturedGradientRectangle

Dibuja en un rectangulo la textura recibida con un gradiente de colores. 

Recibe:
  -unsigned int leftX, topY, rightX, bottomY: coordenadas del rectangulo.
  -ALLEGRO_COLOR topLeft, topRight, bottomLeft, bottomRight: el color del gradiente en cada esquina.
  Por ejemplo, si topLeft y topRight son negros y bottomLeft y bottomRight son blancos, hay un gradiente
  vertical que es negro en el limite superior y blanco en el limite inferior
  -ALLEGRO_BITMAP * texture: textura del rectangulo. Si es nullptr, no se dibuja textura
  -float scaleX, scaleY: Factor por el cual se "estira" o "aprieta" la textura.
  Por ejemplo, si se quiere que una textura se esture verticalemente y horizontalmente se achique, 
  scaleX debe ser <1 y scaleY debe ser >1. Si no se quiere modificar el tamanio de la textura, ambos
  parametros deben valer 1
  //TODO: y si reciben 0 o negativos?
  //TODO: agregar lo de que para hacer tiles, tiene que ser cuadrado y potencia de dos o algo asi
********************************************************************************************************/
void drawTexturedGradientRectangle(unsigned int leftX, unsigned int topY, unsigned int rightX, unsigned int bottomY,
	ALLEGRO_COLOR topLeftColor, ALLEGRO_COLOR topRightColor, ALLEGRO_COLOR bottomLeftColor, ALLEGRO_COLOR bottomRightColor,
	ALLEGRO_BITMAP * texture, float scaleX, float scaleY);

/*******************************************************************************************************
drawTexturedRectangle

Dibuja en un rectangulo la textura recibida sin modificar su color. Es equivalente a llamar a drawTexturedGradientRectangle
con los 4 colores 100% transparentes.

Recibe:
-unsigned int leftX, topY, rightX, bottomY: coordenadas del rectangulo.
-ALLEGRO_BITMAP * texture: textura del rectangulo. Si es nullptr, no se dibuja.
-float scaleX, scaleY: Factor por el cual se "estira" o "aprieta" la textura.
Por ejemplo, si se quiere que una textura se esture verticalemente y horizontalmente se achique,
scaleX debe ser <1 y scaleY debe ser >1. Si no se quiere modificar el tamanio de la textura, ambos
parametros deben valer 1
//TODO: y si reciben 0 o negativos?
//TODO: agregar lo de que para hacer tiles, tiene que ser cuadrado y potencia de dos o algo asi
********************************************************************************************************/
void drawTexturedRectangle(unsigned int leftX, unsigned int topY, unsigned int rightX, unsigned int bottomY,
	ALLEGRO_BITMAP * texture, float scaleX, float scaleY);

/*******************************************************************************************************
drawGradientRectangle

Dibuja en un rectangulo un gradiente de colores.

Recibe:
-unsigned int leftX, topY, rightX, bottomY: coordenadas del rectangulo.
-ALLEGRO_COLOR topLeft, topRight, bottomLeft, bottomRight: el color del gradiente en cada esquina.
Por ejemplo, si topLeft y topRight son negros y bottomLeft y bottomRight son blancos, hay un gradiente
vertical que es negro en el limite superior y blanco en el limite inferior
********************************************************************************************************/
void drawGradientRectangle(unsigned int leftX, unsigned int topY, unsigned int rightX, unsigned int bottomY,
	ALLEGRO_COLOR topLeftColor, ALLEGRO_COLOR topRightColor, ALLEGRO_COLOR bottomLeftColor, ALLEGRO_COLOR bottomRightColor);

/*
cede ownership del bitmap resultante
*/
ALLEGRO_BITMAP * cropToCircle(ALLEGRO_BITMAP * bmp, float sourceRadius, float destinationRadius,
	float sourceCenterX, float sourceCenterY);


/*TODO: comentar*/
void drawFittingText(ALLEGRO_FONT * font, ALLEGRO_COLOR color, unsigned int x, unsigned int y, const char * text,
	unsigned int maxWidth);
