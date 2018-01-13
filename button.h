#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>


//mute quit pass product tile

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

	virtual void draw() = 0;

	void hoveredOn();
	void hoveredOff();
	void toggleHovered();
	bool isHovered();
	void setHovered(bool hovered);

	void pressedOn();
	void pressedOff();
	void togglePressed();
	bool isPressed();
	void setPressed(bool pressed);

	void selectedOn();
	void selectedOff();
	void toggleSelected();
	bool isSelected();
	void setSelected(bool selected);

	float getLeftX();
	float getTopY();
	float getWidth();
	float getHeight();

	void setUnformattedBmp(ALLEGRO_BITMAP * unformattedBmp);
	void resize(float scalingFactor);
	void resize(float width, float height);

private:
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

