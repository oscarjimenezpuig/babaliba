// Includes

#include "sprite.h"

// Constantes

#define PIXDIM 4 //dimension del pixel
#define SPRDIM (8*PIXDIM) //dimension del sprite

#define RDW 8 //dimension de los decorados
              //
#define RDH 8

#define SCRW (SPRDIM*RDW) //dimension de la pantalla
#define SCRH (SPRDIM*(RDH+2))

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
    uchar x : 3; //posicion (en sprites)
    uchar y : 3;
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

int decspr_new(sprite_t* spr,palette_t pal);
//se crea un decorado a partir de cuatro sprites y una paleta (se han de liberar los sprites)
//los sprites empiezan con los dos de la fila superior y despues los de la inferior

void decsprs_del();
//se libera el espacio de los sprites del decorado (no de los sprites individuales);

void decspr_drw(uchar code,uchar psx,uchar psy);
//se dibuja el decorado de codigo dado en la posicion de decorado

//map.c

int room_new(uchar c,uchar r,int data[RDW][RDH],uchar enes);
//creacion de una habitacion nueva data es un array de 8x8 donde se ponen
//los codigos de los decorados (de 0 a 255), c y r es la posicion que ocupan
//en el mapa la habitacion



