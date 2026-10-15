#include "babaliba.h"

object_t player;

uchar quit=0;

#define SPRPLY 4

static sprite_t sprply[SPRPLY];

static void ply_spr() {
    char* data[]={      "00000000",
                        "00000000", 
                        "00000000", 
                        "00000000", 
                        "00000000", 
                        "00000000", 
                        "00000000", 
                        "00000000"
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
}

void ply_end() {
    for(int k=0;k<SPRPLY;k++) spr_del(sprply+k);
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
        ply_rea_col(ocol);
        vx=vy=0;
    } else if(ply_chg_scr(vx,vy)) {
        scr_clr();
        ens_ini(player.ply.px,player.ply.py);
        room_dec_drw(player.ply.px,player.ply.py);
        ens_drw(player.ply.px,player.ply.py);
        scr_fls();
    }
    return (vx||vy);
}

int ply_col(object_t* o) {
    //TODO Programar la colision

void ply_drw() {
    obj_drw(player);
}

