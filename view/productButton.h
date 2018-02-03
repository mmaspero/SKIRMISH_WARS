#pragma once
#include "button.h"
#include "../Game model/Unit.h"
#include "../Game model/unitInfo.h"
#include "../Game model/types.h"

#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

class productButton :
	public button
{
public:
//	productButton(Unit * u, float rLeftX, float rTopY, float rWidth, float rHeight,
	productButton(float rLeftX, float rTopY, float rWidth, float rHeight,
		float eLeftX, float eTopY, float eWidth, float eHeight);
	productButton(float rLeftX, float rTopY, float rWidth, float rHeight,
		float eLeftX, float eTopY, float eWidth, float eHeight, unit_t unitSpecificType);	//BORRAR
	~productButton();

	virtual void draw();

	bool getCanBuy();
	void setCanBuy(bool canBuy);
	unit_t getUnitSpecificType();

	//Redefinidas para que el boton modifique su tamanio cuando se lo selecciona o deselecciona
	virtual void selectedOn();
	virtual void selectedOff();
	virtual void toggleSelected();
	virtual void setSelected(bool selected);


	void hiddenOn();
	void hiddenOff();
	void toggleHidden();
	void setHidden(bool hidden);
	bool isHidden();

	//setters de las dimensiones del boton cuando esta en modo reducido
	void setReducedLeftX(float rLeftX);
	void setReducedTopY(float rTopY);
	void setReducedWidth(float rWidth);
	void setReducedHeight(float rHeight);
	void setReducedDimensions(float rLeftX, float rTopY, float rWidth, float rHeight);
	void getReducedDimensions(float * rLeftX, float * rTopY, float * rWidth, float * rHeight);


	void setExpandedLeftX(float eLeftX);
	void setExpandedTopY(float eTopY);
	void setExpandedWidth(float eWidth);
	void setExpandedHeight(float eHeight);
	void setExpandedDimensions(float eLeftX, float eTopY, float eWidth, float eHeight);
	void getExpandedDimensions(float * rLeftX, float * rTopY, float * rWidth, float * rHeight);

	void setAllDimensions(float rLeftX, float rTopY, float rWidth, float rHeight,
					   float eLeftX, float eTopY, float eWidth, float eHeight);
	void getAllDimensions(float * rLeftX, float * rTopY, float * rWidth, float * rHeight,
		float * eLeftX, float * eTopY, float * eWidth, float * eHeight);

private:
	bool hidden;	//Indica si el boton esta visible o no. Por mas que este hidden, puede estar 
					//expandido (selected = true) o reducido (selected = false).
					//Sin embargo, en ninguno de los casos se dibuja si hidden es true
	float margin;	//margen usado para dibujar con proporcionalidad

	//Dimensiones cuando el boton reducido (cuando selected = false)
	float rLeftX;
	float rTopY;
	float rWidth;
	float rHeight;
	//Dimensiones cuando el boton esta expandido (cuando selected = true)
	float eLeftX;
	float eTopY;
	float eWidth;
	float eHeight;

	//En vez de usar resizedBmp, usar dos punteros diferentes: 
	//para cuando esta reducido y para cuando esta expandido
	ALLEGRO_BITMAP * reducedBmp;
	ALLEGRO_BITMAP * expandedBmp;

	bool setReducedBmp();	//Devuelve true si no hubieron errores
	bool setExpandedBmp();	//Devuelve true si no hubieron errores
	void calculateCurrentDimensions();	//con todas las dimensiones reducidas y expandidas y teniendo 
										//en cuenta si esta selected o no, calcula las dimensiones finales 
										//del boton. Se guardan en las variebles leftX, topY, width, 
										//height, pertenecientes a button.

	std::string unitSpecificTypeName;
	unit_t unitSpecificType;
	unitType_t unitBasicType;
	bool canBuy;
	unsigned int cost;
	unsigned int firepower[N_BASIC_U_TYPES];	//Cuantos HP le saca a cada tipo basico de unidad
	unsigned int firepowerReduced[N_BASIC_U_TYPES];
	unsigned int movingPoints[N_TERRAINS];
};