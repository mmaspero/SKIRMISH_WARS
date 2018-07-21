#include "button.h"

#include <allegro5\allegro_primitives.h>
#include "drawingFunctions.h"

button::button(float leftX, float topY, float width, float height)
{
	unformattedBmp = resizedBmp = nullptr;
	this->width = width;
	this->height = height;
	this->leftX = leftX;
	this->topY = topY;

	hovered = pressed = selected = false;

	if (height <= 0 || width <= 0)	//TODO: control de leftX y topY
	{
		valid = false;
	}
	else
	{
		valid = true;
	}
}

button::button(ALLEGRO_BITMAP * bmp, float leftX, float topY)
{
	if (bmp == nullptr)
	{
		valid = false;
	}
	else
	{
		resizedBmp = nullptr;
		this->unformattedBmp = al_clone_bitmap(bmp);
		width = al_get_bitmap_width(bmp);
		height = al_get_bitmap_height(bmp);
		resize();
		this->leftX = leftX;
		this->topY = topY;
		hovered = pressed = selected = false;
		valid = true;
	}

}

button::button(ALLEGRO_BITMAP * bmp, float leftX, float topY, float width, float height)
{
	if (bmp == nullptr)
	{
		valid = false;
	}
	else	//TODO: limitar width y height
	{
		resizedBmp = nullptr;
		this->unformattedBmp = al_clone_bitmap(bmp);
		this->leftX = leftX;
		this->topY = topY;
		this->width = width;
		this->height = height;

		hovered = pressed = selected = false;

		resize();
	}
}

button::button(ALLEGRO_BITMAP * bmp, float leftX, float topY, float scalingFactor)
{
	if (bmp == nullptr)
	{
		valid = false;
	}
	else
	{
		this->unformattedBmp = al_clone_bitmap(bmp);
		this->leftX = leftX;
		this->topY = topY;

		width = al_get_bitmap_width(bmp) * scalingFactor;
		height = al_get_bitmap_height(bmp) * scalingFactor;

		hovered = pressed = selected = false;

		resize(width, height);
	}
}

button::~button()
{
	if (unformattedBmp != nullptr)
	{
		al_destroy_bitmap(unformattedBmp);
	}
	if (resizedBmp != nullptr)
	{
		al_destroy_bitmap(resizedBmp);
	}
}

bool button::isValid()
{
	return valid;
}

buttonType_t button::getType()
{
	return buttonType;
}

void button::hoveredOn()
{
	hovered = true;
}

void button::hoveredOff()
{
	hovered = false;
}

void button::toggleHovered()
{
	hovered = !hovered;
}

bool button::isHovered()
{
	return hovered;
}

void button::setHovered(bool hovered)
{
	this->hovered = hovered;
}

void button::pressedOn()
{
	pressed = true;
}

void button::pressedOff()
{
	pressed = false;
}

void button::togglePressed()
{
	pressed = !pressed;
}

bool button::isPressed()
{
	return pressed;
}

void button::setPressed(bool pressed)
{
	this->pressed = pressed;
}

void button::selectedOn()
{
	selected = true;
}

void button::selectedOff()
{
	selected = false;
}

void button::toggleSelected()
{
	selected = !selected;
}

bool button::isSelected()
{
	return selected;
}

void button::setSelected(bool selected)
{
	this->selected = selected;
}

float button::getLeftX()
{
	return leftX;
}

float button::getTopY()
{
	return topY;
}

float button::getWidth()
{
	return width;
}

float button::getHeight()
{
	return height;
}

void button::setLeftX(unsigned int leftX)
{
	this->leftX = leftX;
}

void button::setTopY(unsigned int topY)
{
	this->topY = topY;
}


bool button::isItHere(int xPixel, int yPixel)
{
	return(leftX < xPixel && xPixel < leftX + width
  		 && topY < yPixel && yPixel < topY + height);
}

void button::setUnformattedBmp(ALLEGRO_BITMAP * unformattedBmp)
{
	if (unformattedBmp != nullptr)
	{
		al_destroy_bitmap(this->unformattedBmp);
	}
	this->unformattedBmp = unformattedBmp;
	resize();
}

void button::resize(float scalingFactor)
{
	width = width * scalingFactor;
	height = height * scalingFactor;
	resize();
}

void button::resize(float width, float height)
{
	this->width = width;
	this->height = height;
	resize();
}

void button::resize()
{
	//dibujar unformattedBmp con sus nuevas dimensiones en un nuevo bitmap
	if (resizedBmp != nullptr) {
		al_destroy_bitmap(resizedBmp);
	}
	resizedBmp = al_create_bitmap(width, height);
	ALLEGRO_BITMAP * targetBmpBackup = al_get_target_bitmap();
	al_set_target_bitmap(resizedBmp);
	al_draw_scaled_bitmap(unformattedBmp, 0, 0,
		al_get_bitmap_width(unformattedBmp), al_get_bitmap_height(unformattedBmp),
		0, 0, width, height, 0);
	al_set_target_bitmap(targetBmpBackup);
}
