#include "babaliba.h"

object_t player;

uchar quit=0;

#define SPRPLY 4

static sprite_t sprply[SPRPLY];
static sprite_t sblank;

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
    sblank=spr_new(1);
    spr_ins(sblank,0,0,0);
}

void ply_ini() {
    palette_t ppl={WHITE,WHITE,WHITE,WHITE};
    ply_spr();
    player=obj_new(PLAYER,sprply[0],ppl);
    room_obj_ins(PPXI,PPYI,PXI,PYI,&player);
    player.ply.scr=0;
    player.ply.liv=LIVESINI;
    player.ply.bnt=0;
    player.ply.its=0;
}

void ply_end() {
    for(int k=0;k<SPRPLY;k++) spr_del(sprply+k);
}

static void ply_era_mrk(int x,int y,uchar len) {
    //borrado de sprites de dimesniones SPRDIM
    palette_t pblank={BLACK};
    for(uchar k=0;k<len;k++) {
        spr_drw(sblank,pblank,x,y,SPRDIM);
        x+=SPRDIM;
    }
}

static void ply_inv_drw() {
    //dibuja el inventario
    const int Y=SCRH-SPRDIM+2;
    const int X=SCRW-SPRDIM*ITPLY;
    ply_era_mrk(X,Y,ITPLY);
    int x=X;
    for(uchar k=0;k<player.ply.its;k++) {
        object_t* it=player.ply.it[k];
        if(it) {
            spr_drw(it->spr,it->pal,x,Y,PIXMDIM);
            x+=SPRDIM;
        }
    }
}

static void ply_liv_drw() {
    //dibuja el marcador de vidas
    const int Y=SCRH-SPRDIM+2;
    const int X=0;
    ply_era_mrk(X,Y,5);
    int x=X;
    for(int k=0;k<player.ply.liv;k++) {
        spr_drw(player.spr,player.pal,x,Y,PIXMDIM);
        x+=SPRDIM;
    }
}

static void reset_ene(uchar px,uchar py) {
    //cuenta los enemigos activos
    room_t* r=&(map[px][py]);
    uchar count=0;
    printf("enemigos iniciales en %i,%i=%i\n",px,py,r->enes);//dbg
    for(uchar k=0;k<r->enes;k++) {
        if(enemies[k].act) count++;
    }
    r->enes=count;
    printf("          finales=%i\n",r->enes);//dbg
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
        reset_ene(player.ply.px,player.ply.py);
        player.ply.px=px;
        player.ply.py=py;
        player.x=x;
        player.y=y;
    }
    return ret;
}

static void drw_act_rom() {
    //dibuja la habitacion actual del player
    player.ply.bnt=0;
    scr_clr();
    ens_ini(player.ply.px,player.ply.py);
    room_dec_drw(player.ply.px,player.ply.py);
    ens_drw(player.ply.px,player.ply.py);
    ply_inv_drw();
    scr_fls();
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
        drw_act_rom();
    }
    return (vx||vy);
}

static int arr_psh(object_t* new,object_t* arr[],int dim) {
    //se introduce un objeto nuevo en el principio del array (no se verifica dimension)
    for(int k=dim-1;k>=0;k--) {
        arr[k+1]=arr[k];
    }
    arr[0]=new;
    return dim+1;
}

static int arr_pop(object_t* arr[],int dim,object_t** o) {
    //se extrae el ultimo objeto si existe, devuelve la nueva dimension
    if(dim>0) {
        --dim;
        *o=arr[dim];
    }
    return dim;
}

static int arr_fnd(object_t* arr[],int dim,int (*cond)(object_t*)) {
    //buscamos un objeto del array y devolvemos su posicion
    int k=0;
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
            o->act=0;
            spr_era(o->spr,o->x,o->y,PIXDIM);
            room_obj_era(player.ply.px,player.ply.py,o);
        } else {
            //muerte jugador
            spr_era(player.spr,player.x,player.y,PIXDIM);
            pause(1);
            player.ply.liv-=1;
            if(player.ply.liv==0) {
                quit=1;
            } else {
                room_obj_era(player.ply.px,player.ply.py,&player);
                room_obj_ins(PPXI,PPYI,PXI,PYI,&player);
                drw_act_rom();
            }
            return 0;
        }
    } else if(o->typ==ITEM) return ply_tak(o);
    return 1;
}  


void ply_drw() {
    obj_drw(player);
    ply_liv_drw();
}

