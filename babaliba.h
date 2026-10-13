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
#define SPIDER 3 

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

typedef struct {
} item_t;

typedef struct {
    item_t* it[ITPLY];
    struct {
        uchar liv : 4;
        uchar its : 4;
    }
    ushort scr;
}player_t;

typedef struct {
    uchar act : 1; //enemigo activo
    uchar ety : 2; //tipo de enemigo
    uchar rnd : 1;
    uchar prs : 1;
    uchar spox : 4;
    uchar spoy : 4; //posicion en unidades sprite inicial
    uchar spdx : 4; 
    uchar spdy : 4; //posicion en unidades sprite final
}enemy_t;

typedef struct {
    sprite_t spr;
    palette_t pal;
    int x,y;
    struct {
        uchar px : 3;
        uchar py :3 ;
        uchar typ : 2;
    };
    union {
        item_t ite;
        player_t ply;
        enemy_t ene;
    };
} object_t;

typedef struct {
    struct {
        uchar decs : 5; //decorados
        uchar enes : 2; //objetos
    };
    deco_t dec[DECS]; //decorados
    object_t* ite; //item de la posicion
    object_t* ene[ENES];
} room_t;

typedef room_t map_t[MAPW][MAPH];

// Variables

extern decsprs_t decsprs; //guarda todos los sprites del decorado

extern map_t map; //guarda todo el mapa

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

void obj_plc(object_t* obj,uchar px,uchar py,int x,int y);
//se emplaza un objeto (y pasa a ser activo)

void obj_unplc(object_t* obj);
//se le quita la posicion al objeto (y pasa a ser inactivo)

object_t* obj_mov(object_t* object,int x,int y);
//movemos un objeto de una posicion a otra (devuelve el objeto de colision)

void obj_drw(object_t obj);
//dibuja el objeto

//map.c

void room_dec(uchar px,uchar py,uchar decs,...);
//introduce los decorados de la habitacion

int room_ite(uchar px,uchar py,int x,int y,object_t* obj);
//introduce el item en una habitacion (si no hay ninguno)

int room_ene(uchar px,uchar py,enemy_t ene);
//introduce un enemigo en una habitacion

void room_dec_grd(uchar px,uchar py,uchar* deco,char* data[]);
//se crea la habitacion a partir de una parrilla como los sprites,
//solo acepta 10 decorados (de 0 a 9) contenidos en el array deco

int room_obj(uchar px,uchar py,int x,int y,object_t* obj);
//introduce un objeto en la habitacion (en un lugar libre)

int room_can_plc(uchar px,uchar py,object_t* obj,int x,int y);
//dice si un objeto colisiona con el decorado

object_t* room_obj_col(uchar px,uchar py,object_t* obj);
//dice si un objecto colisionara con enemigo de la habitacion
//devuelve el enemigo colisionado

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

//enemy.c

void ene_ini(int px,int py,enemy_t* ene);
//inicia un enemigo cuando se visita una pantalla
