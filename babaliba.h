// Includes

#include <stdarg.h>

#include "sprite.h"

// Constantes

#define PIXDIM 4 //dimension del pixel
#define SPRDIM (8*PIXDIM) //dimension del sprite

#define RDW 8 //dimension de los decorados
#define RDH 8

#define SCRW (SPRDIM*RDW*2) //dimension de la pantalla
#define SCRH (SPRDIM*(RDH*2+2))

#define DECS 63 //numero de sprites de decorado maximo en una pantalla
#define OBJS 7 //numero maximo de enemigos por pantalla

#define MAPW 2 //dimension del mapa
#define MAPH 2

#define NULLPP ((MAPW>MAPH)?(MAPW):(MAPH)) //posicion de pantalla nula

#define LIVESINI 3 //vidas iniciales

#define PPXI 0 //posicion de pantalla inicial del player
#define PPYI 0 

#define PXI SPRDIM*2 //posicion dentro de la pantalla inicial
#define PYI SPRDIM*3

#define POPSIZ 3 //numero maximo de objetos que puede tener un jugador

#define IDPLA 0 //identidad jugador
#define IDENE 1000 //primera de las identidades de los enemigos
#define IDITM 2000 //primera de las identidades de un objeto

// Tipos

typedef unsigned char uchar;
typedef unsigned short ushort;

//un decorado es un sprite 2x2

typedef struct {
    sprite_t spr[2][2];
    palette_t pal;
} decspr_t; //sprite de decorado (2x2 con paleta)

typedef decspr_t* decsprs_t; //matriz de dimension variable que contiene todos los sprites del decorado

typedef struct {
    uchar x : 3; //posicion (en sprites de decorado)
    uchar y : 3;
    uchar cod; //codigo del decorado
} deco_t;

struct object_s; //predeclaracion de object_s

struct object_s {
    ushort id;
    sprite_t spr;
    palette_t pal;
    int x,y;
    struct object_s* con;
    struct {
        uchar act : 1;
        uchar px : 3;
        uchar py : 3;
        uchar ene : 1;
    };

};

typedef struct object_s object_t;

typedef struct {
    struct {
        uchar decs : 5; //decorados
        uchar objs : 3; //enemigos
    };
    deco_t dec[DECS];
    object_t* obj[OBJS];
} room_t;

typedef room_t map_t[MAPW][MAPH];

// Variables

extern decsprs_t decsprs; //guarda todos los sprites del decorado

extern map_t map; //guarda todo el mapa

extern object_t player; //guarda el jugador
extern int score,lives; //puntuacion y vidas
                        
extern uchar quit; //bandera de finalizar

// Funciones

//decoration.c

int decspr_new(sprite_t* spr,palette_t pal);
//se crea un decorado a partir de cuatro sprites y una paleta (se han de liberar los sprites)
//los sprites empiezan con los dos de la fila superior y despues los de la inferior

void decsprs_del();
//se libera el espacio de los sprites del decorado (no de los sprites individuales);

void decspr_drw(uchar code,uchar psx,uchar psy);
//se dibuja el decorado de codigo dado en la posicion de decorado

//object.c

object_t obj_new(ushort id,sprite_t spr,palette_t pal);
//creacion de un objeto (sin lugar)

void obj_plc(object_t* obj,uchar px,uchar py,int x,int y);
//se emplaza un objeto (y pasa a ser activo)

void obj_unplc(object_t* obj);
//se le quita la posicion al objeto (y pasa a ser inactivo)

int obj_con(object_t* object,object_t* container);
//se pone en el contenedor el objeto

object_t* obj_mov(object_t* object,int x,int y);
//movemos un objeto de una posicion a otra (devuelve el objeto de colision)

void obj_drw(object_t obj);
//dibuja el objeto

//map.c

void room_dec(uchar px,uchar py,uchar decs,...);
//introduce los decorados de la habitacion

void room_dec_grd(uchar px,uchar py,uchar* deco,char* data[]);
//se crea la habitacion a partir de una parrilla como los sprites,
//solo acepta 10 decorados (de 0 a 9) contenidos en el array deco

int room_obj(uchar px,uchar py,int x,int y,object_t* obj);
//introduce un objeto en la habitacion (en un lugar libre)

int room_can_plc(uchar px,uchar py,object_t obj,int x,int y);
//dice si un objeto colisiona con el decorado

object_t* room_obj_col(uchar px,uchar py,object_t obj);
//dice si un objecto colisionara con otros objetos de la habitacion
//devuelve el objeto colisionado

void room_dec_drw(uchar px,uchar py);
//dibujo del decorado

void room_obj_drw(uchar px,uchar py);
//dibujo de los objetos

//player.c

void ply_ini();
//iniciamos el jugador

void ply_end();
//liberamos espacio del jugador

int ply_act();
//actuacion del jugador

void ply_drw();
//dibuja el jugador
