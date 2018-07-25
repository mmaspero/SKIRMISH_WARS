#pragma once

typedef enum { WELCOME, INSERTING_NAME, TRYING_IP, RETRYING_IP, CHOOSING_MAP, WAITING_CONNECTION }pipBoyStatus_t;

#define PIPBOY_DEFAULT_W 1000
#define PIPBOY_DEFAULT_H 400

#define PIPBOY_FONT_NAME FONT_PATH "runescape_chat_font.ttf"
#define PIPBOY_FONT_SIZE (PIPBOY_DEFAULT_H / 6.0)
#define PIPBOY_FONT_COLOR {(float)0.45, (float)1, (float)0, (float)1}	//"lawngreen"

#define MAX_USERNAME_LENGTH 255

#define PIPBOY_WELCOME_MSG_LINE_1 "Bienvenido al pip-Boy"
#define PIPBOY_WELCOME_MSG_LINE_2 "En EDA todo anda"
#define PIPBOY_INSERTING_NAME_MSG "Nombre?"
#define PIPBOY_TRYING_IP_MSG "Ingrese la IP del oponente:"
#define PIPBOY_RETRYING_IP_MSG "IP ingresada no valida. Reintente:"
#define PIPBOY_CONNECTION_MSG "Aguardando conexion..."
