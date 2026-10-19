#include "babaliba.h"

object_t player;

uchar quit=0;

#define SPRPLY 4

static sprite_t sprply[SPRPLY];

static void ply_spr() {
    char* data[]={      "   00   ",
                        "   00   ", 
                        "00000000", 
                        "0 0000 0", 
                        "0  00  0", 
                        "  0000  ", 
                        "  0  0  ", 
                        "  0  0  "
    };
    sprply[0]=spr_grd(8,data);
}

void ply_ini() {
    palette_t ppl={WHITE,WHITE,WHITE,WHITE};
    ply_spr();
    player=obj_new(PLAYER,sprply[0],ppl);
    room_obj_ins(PPXI,PPYI,PXI,PYI,&player);
    player.ply.scr=0;
    player.ply.liv=LIVESINI;
    player.ply.bnt=0;
}

void ply_end() {
    for(int k=0;k<SPRPLY;k++) spr_del(sprply+k);
}

static void ply_inv_drw() {
    const int Y=SCRH-SPRDIM;
    const int X=SCRW-SPRDIM*ITPLY;
    int x=X;
    for(uchar k=0;k<player.ply.its;k++) {
        object_t* it=player.ply.it[k];
        spr_drw(it->spr,it->pal,x,Y,PIXDIM);
        x+=SPRDIM;
    }
}

static int ply_chg_scr(int vx,int vy) {
    //funcion que detecta el cambio de pantalla
    int ret=0;
    int px=player.ply.px;
    int py=player.ply.py;
    int x=player.x;
    int y=player.y;
    if(x<=0 && vx==-1 && px>0) {
        x=SCRW-SPRDIM;
        px--;
        ret=1;
    } else if(x>=SCRW-SPRDIM && vx==1 && px<MAPW-1) {
        x=0;
        px++;
        ret=1;
    }
    if(y<=SPRDIM && vy==-1 && py>0) {
        y=SCRH-2*SPRDIM;
        py--;
        ret=1;
    } else if(y>=SCRH-2*SPRDIM && vy==1 && py<MAPH-1) {
        y=SPRDIM;
        py++;
        ret=1;
    }
    if(ret) {
        player.ply.px=px;
        player.ply.py=py;
        player.x=x;
        player.y=y;
    }
    return ret;
}

int ply_act() {
    key_lis();
    int vx,vy;
    vx=vy=0;
    if(key_in('i')) vy=-1;
    else if(key_in('k')) vy=1;
    if(key_in('j')) vx=-1;
    else if(key_in('l')) vx=1;
    if(key_in('q')) quit=1;
    object_t* ocol=NULL;
    if(vx) ocol=obj_mov(&player,player.ply.px,player.ply.py,player.x+vx*PIXDIM,player.y);
    if(vy && !ocol) ocol=obj_mov(&player,player.ply.px,player.ply.py,player.x,player.y+vy*PIXDIM);
    if(ocol) {
        ply_col(ocol);
        vx=vy=0;
    } else if(ply_chg_scr(vx,vy)) {
        player.ply.bnt=0;
        scr_clr();
        ens_ini(player.ply.px,player.ply.py);
        room_dec_drw(player.ply.px,player.ply.py);
        ens_drw(player.ply.px,player.ply.py);
        ply_inv_drw();
        scr_fls();
    }
    return (vx||vy);
}

static uchar arr_psh(object_t* new,object_t* arr[],uchar dim) {
    //se introduce un objeto nuevo en el principio del array (no se verifica dimension)
    for(int k=dim-2;k>=0;k--) {
        arr[k+1]=arr[k];
    }
    arr[0]=new;
    return dim+1;
}

static uchar arr_pop(object_t* arr[],uchar dim,object_t** o) {
    //se extrae el ultimo objeto si existe, devuelve la nueva dimension
    if(dim>0) {
        --dim;
        *o=arr[dim];
    }
    return dim;
}

static uchar arr_fnd(object_t* arr[],uchar dim,int (*cond)(object_t*)) {
    //buscamos un objeto del array y devolvemos su posicion
    uchar k=0;
    for(;k<dim;k++) if(cond(arr[k])) break;
    return k;
}

static int arr_is_fnd(uchar pos,uchar dim) {
    //dice si la posicion coincide con encontrado
    return (pos<dim);
}

static uchar arr_era(object_t* arr[],uchar dim,uchar pos) {
    //borramos el elemento de la posicion pos y devolvemos la dimension
    if(pos<dim) {
        for(uchar k=pos;k<dim;k++) arr[k]=arr[k+1];
        return dim-1;
    }
    return dim;
}

int ply_tak(object_t* o) {
    if(player.ply.bnt==0) {
        spr_era(o->spr,o->x,o->y,PIXDIM);
        room_obj_era(player.ply.px,player.ply.py,o);
        if(player.ply.its==ITPLY) {
            object_t* leave;
            player.ply.its=arr_pop(player.ply.it,player.ply.its,&leave);
            room_obj_ins(player.ply.px,player.ply.py,player.x,player.y,leave);
        }
        player.ply.its=arr_psh(o,player.ply.it,player.ply.its);
        player.ply.bnt=1;
        ply_inv_drw();
        return 1;
    }
    return 0;
}

static schar tip_weap=-1;

static int cond_weap(object_t* o) {
    return (o->typ==ITEM && o->ite.cls==tip_weap);
}

static int ply_use_weap(object_t* enemy) {
    //usa el weapon (1 lo usa, 0 no lo usa)
    tip_weap=enemy->ene.cls;
    uchar pos=arr_fnd(player.ply.it,player.ply.its,cond_weap);
    if(arr_is_fnd(pos,player.ply.its)) {
        player.ply.its=arr_era(player.ply.it,player.ply.its,pos);
        ply_inv_drw();
        return 1;
    } else return 0;
}

int ply_col(object_t* o) {
    if(o->typ==ENEMY) {
        if(ply_use_weap(o)) {
            //muerte de enemigo
            room_obj_era(player.ply.px,player.ply.py,o);
            room_t* r=&map[player.ply.px][player.ply.py];
            r->enes--;
        } else {
            //muerte jugador
            quit=1;
            return 0;
        }
    } else if(o->typ==ITEM) return ply_tak(o);
    return 1;
}  


void ply_drw() {
    obj_drw(player);
}

