// Includesi

#include <stdarg.h>
#include <stdio.h> //dbg

#include "sprite.h"

// Constantes

#define PIXDIM 4 //dimension del pixel
#define SPRDIM (8*PIXDIM) //dimension del sprite

#define RDW 8 //dimension de los decorados
#define RDH 8

#define SCRW (SPRDIM*RDW*2) //dimension de la pantalla
#define SCRH (SPRDIM*(RDH*2+2))

#define DECS 63 //numero de sprites de decorado maximo en una pantalla
#define ENES 3 //numero maximo de enemigos

#define MAPW 2 //dimension del mapa
#define MAPH 2

#define NULLPP ((MAPW>MAPH)?(MAPW):(MAPH)) //posicion de pantalla nula

#define LIVESINI 3 //vidas iniciales

#define PPXI 0 //posicion de pantalla inicial del player
#define PPYI 0 

#define PXI SPRDIM*2 //posicion dentro de la pantalla inicial
#define PYI SPRDIM*3

#define POPSIZ 3 //numero maximo de objetos que puede tener un jugador

#define IDENE 1000 //primera de las identidades de los enemigos
#define IDITM 2000 //primera de las identidades de un objeto
#define ITPLY 4 //numero de items maximo que puede tener un jugador

#define PLAYER 0 //tipos de objeto
#define ENEMY 1
#define ITEM 2
#define NOTHING 3

#define SOLDIER 0 //tipos de enemigos
#define SKELETON 1
#define SPIDER 2

#define SOLPOM 25 //probabilidades de movimiento
#define SKEPOM 50
#define SPDPOM 75

#define SWORD 0 //tipos de items (cada uno en el orden que mata al enemigo)
#define CROSS 1
#define DDT 2

#define SWRS ((MAPW*MAPH)/3) //cantidad de armas disponibles
#define CRSS SWRS
#define DDTS SWRS

#define PIXMDIM (PIXDIM-1) //dimensiones de pixels en marcadores
#define SPRMDIM (PIXDIM*8)

// Tipos

typedef unsigned char uchar;
typedef signed char schar;
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

typedef struct {
    uchar cls : 4; //clase de item
} item_t;

typedef struct {
    uchar cls : 2; //clase de enemigo
    schar vx : 2; //guarda las direcciones
    schar vy : 2; 
} enemy_t;

typedef struct {
    struct object_s* it[ITPLY]; //items
    struct {
        uchar liv : 4; //lives
        uchar its : 4; //items poseidos
        uchar px : 3; //pantalla x
        uchar py : 3 ; //pantalla y
        uchar bnt : 1; //esta bandera si esta conectada no coge nada
    };
    ushort scr; //score
}player_t;

struct object_s{
    sprite_t spr;
    palette_t pal;
    int x,y;
    struct {
        uchar typ : 2; //tipo
        uchar act : 1; //activo
    };
    union {
        item_t ite;
        player_t ply;
        enemy_t ene;
    };
};

typedef struct object_s object_t;

typedef struct {
    struct {
        uchar decs : 5; //decorados
        uchar enes : 2; //enemigos
    };
    deco_t dec[DECS]; //decorados
    object_t* ite; //item de la posicion
} room_t;

typedef room_t map_t[MAPW][MAPH];

typedef object_t enemies_t[ENES];

// Variables

extern decsprs_t decsprs; //guarda todos los sprites del decorado

extern map_t map; //guarda todo el mapa

extern enemies_t enemies; //enemigos de la pantalla actual

extern object_t player; //guarda el jugador
                        
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

object_t obj_new(uchar type,sprite_t spr,palette_t pal);
//creacion de un objeto (sin lugar) 

object_t* obj_mov(object_t* object,uchar px,uchar py,int x,int y);
//movemos un objeto de una posicion a otra (devuelve el objeto de colision)

void obj_drw(object_t obj);
//dibuja el objeto

//map.c

void room_dec(uchar px,uchar py,deco_t deco);
//introduce un decorado en la habitacion

void room_set_ene(uchar px,uchar py,uchar enes);
//da los enemigos de cada habitacion

int room_can_plc(uchar px,uchar py,object_t* obj,int x,int y);
//dice si un objeto colisiona con el decorado

object_t* room_obj_col(uchar px,uchar py,object_t* obj,int x,int y);
//da las colisiones de un objeto con otro objeto de la habitacion

int room_obj_ins(uchar px,uchar py,int x,int y,object_t* obj);
//colocamos un objeto en una habitacion

void room_obj_era(uchar px,uchar py,object_t* obj);
//quitamos objeto de una habitacion

void room_dec_drw(uchar px,uchar py);
//dibujo del decorado

void room_ite_drw(uchar px,uchar py);
//dibujo de los objetos

void room_ene_drw(uchar px,uchar py);
//dibuja todos los enemigos

//player.c

void ply_ini();
//iniciamos el jugador

void ply_end();
//liberamos espacio del jugador

int ply_act();
//actuacion del jugador

int ply_tak(object_t* o);
//el jugador coge el objeto o

int ply_col(object_t* o);
//colision del jugador con un objeto (devuelve 1 si el jugador puede seguir
//moviendose o 0 si no puede)

void ply_drw();
//dibuja el jugador

//enemy.c

int ens_ini(uchar px,uchar py);
//creamos los enemigos de la pantalla actual y los situamos en ella

void ens_end();
//finaliza los sprites de los enemigos

void ens_act(uchar px,uchar py);
//actuacion de todos los enemigos de la pantalla

void ens_drw(uchar px,uchar py);
//dibujo de todos los enemigos de la pantalla

//item.c 

void ite_ini();
//define todos los items y los coloca en las diferentes pantallas

void ite_end();
//borra todos los sprites de item

//island.c

void isl_ini();
//inicia toda la isla colocando items y decorados

void isl_end();
//finaliza toda la isla, borrando todos los sprites de ella

