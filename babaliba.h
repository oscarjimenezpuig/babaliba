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

extern map_t map;

// Funciones


