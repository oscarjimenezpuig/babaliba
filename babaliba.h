// Includes

#include "sprite.h"

// Constantes

#define PIXDIM 4 //dimension del pixel
#define SPRDIM (8*PIXDIM) //dimension del sprite

#define SCRW (SPRDIM*15) //dimension de la pantalla
#define SCRH (SPRDIM*17)

#define DECS 15 //numero de sprites de decorado maximo en una pantalla

#define MAPW 5 //dimension del mapa
#define MAPH 5

// Tipos

typedef unsigned char uchar;

//un decorado es un sprite 2x2

typedef struct {
    sprite_t spr[2][2];
    palette_t pal;
} decspr_t; //sprite de decorado (2x2 con paleta)

typedef decspr_t* decsprs_t; //matriz de dimension variable que contiene todos los sprites del decorado

typedef struct {
    uchar x : 4; //posicion (en sprites)
    uchar y : 4;
    uchar cod; //codigo del decorado
} deco_t;

typedef struct {
    struct {
        uchar decs : 4; //decorados
        uchar enes : 2; //enemigos
    };
    deco_t dec[DECS];
} room_t;

typedef room_t map_t[MAPW][MAPH];

// Variables

extern decsprs_t decsprs; //guarda todos los sprites del decorado

extern map_t map; //guarda todo el mapa

// Funciones

//decoration.c

int decspr_new(char* data[],palette_t pal);
//se crea un decorado nuevo que debe tener 16 columnas por 16 filas obligatoriamente
//la funcion devuelve el codigo o -1 si no se ha creado

void decsprs_del();
//libera todos los sprites de decorados guardados

void decspr_drw(uchar code,uchar psx,uchar psy);
//se dibuja el decorado de codigo dado en la posicion de sprites dada

