#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

typedef enum {TILE_BUTTON, PRODUCT_BUTTON, SIMPLE_BUTTON, BUTTON_TYPES_N} buttonType_t;

typedef enum {PASS, BUY, CANCEL, BACK, SIMPLE_BUTTON_TYPES_N} simpleButtonType_t;	//botones que son solo una palabra y no hacen nada magico. Other quiere decir que no es niguno de los que ya estan estipulados


/*
NO toma ownership del ALLEGRO_BITMAP * bmp, sino que crea una copia.
*/
class button
{
public:
	/*
	crear sin bitmap
	*/
	button(float leftX, float topY, float width, float height);
	/*
	el tamanio de boton va a ser el tamanio del bitmap
	*/
	button(ALLEGRO_BITMAP * bmp, float leftX, float topY);
	/*
	el bitmap se estira o apreta para coincidir con las dimensiones del boton (width x height)
	*/
	button(ALLEGRO_BITMAP * bmp, float leftX, float topY, float width, float height);
	/*
	se modifica el tamanio del bitmap conservando sus proporciones. El boton tiene el tamanio del bitmap modificado
	*/
	button(ALLEGRO_BITMAP * bmp, float leftX, float topY, float scalingFactor);
	
	~button();

	bool isValid();

	buttonType_t getType();

	virtual void draw() = 0;

	virtual void hoveredOn();
	virtual void hoveredOff();
	virtual void toggleHovered();
	bool isHovered();
	virtual void setHovered(bool hovered);

	virtual void pressedOn();
	virtual void pressedOff();
	virtual void togglePressed();
	bool isPressed();
	virtual void setPressed(bool pressed);

	virtual void selectedOn();
	virtual void selectedOff();
	virtual void toggleSelected();
	bool isSelected();
	virtual void setSelected(bool selected);

	float getLeftX();
	float getTopY();
	float getWidth();
	float getHeight();

	bool isItHere(int xPixel, int yPixel);	//TODO: hacer que isItHEre no falle con product button cuando este hidden. setear width y height en 0?
	void setUnformattedBmp(ALLEGRO_BITMAP * unformattedBmp);
	void resize(float scalingFactor);
	void resize(float width, float height);

protected:
	buttonType_t buttonType;

	void resize();

	bool valid;

	bool hovered;
	bool pressed;
	bool selected;

	ALLEGRO_BITMAP * unformattedBmp;
	ALLEGRO_BITMAP * resizedBmp;
	float leftX;
	float topY;
	float width;
	float height;
};

