#include <stdio.h>

#include "babaliba.h"

sprite_t decorado;

static void mapa() {
    char* dd[]=  {  "00000000",
                    "00000000",
                    "00000000",
                    "00000000",
                    "00000000",
                    "00000000",
                    "00000000",
                    "00000000"
    };
    decorado=spr_grd(8,dd);
    palette_t pd={col_new(0,255,0),BLACK,BLACK,BLACK};
    sprite_t dspr[]={decorado,decorado,decorado,decorado};
    decspr_new(dspr,pd);
    char* a[]={     "00000000",
                    "0       ",
                    "000     ",
                    "0       ",
                    "0   00  ",
                    "0       ",
                    "0",
                    "0"
    };
    char* b[]={     "00000000",
                    "       0",
                    " 00    0",
                    "   0   0",
                    "       0",
                    "       0",
                    "       0",
                    "       0"
    };
    char* c[]={     "0",
                    "0",
                    "0",
                    "0",
                    "0",
                    "0",
                    "0",
                    "00000000"
    };
    char* d[]={     "       0",
                    "       0",
                    "       0",
                    "       0",
                    "       0",
                    "       0",
                    "  000  0",
                    "00000000"
    };
    uchar decod[]={0};
    room_dec_grd(0,0,decod,a);
    room_dec_grd(1,0,decod,b);
    room_dec_grd(0,1,decod,c);
    room_dec_grd(1,1,decod,d);
    //CREACION DE ENEMIGOS
    for(int i=0;i<2;i++) {
        for(int j=0;j<2;j++) {
            if(i!=PPXI || j!=PPYI) {
                room_set_ene(i,j,rnd(0,ENES));
            }
        }
    }
}

static void ini() {
    scr_ini(SCRW,SCRH);
    txt_ini();
    mapa();
    ite_ini();
    ply_ini();
    ens_ini(player.ply.px,player.ply.py);
}

static void end() {
    //decsprs_del();  
    spr_del(&decorado);
    scr_end();
    txt_end();
    ply_end();
    ens_end();
    ite_end();
}

int main() {
    ini();
    room_dec_drw(player.ply.px,player.ply.py);
    ply_drw();
    while(!quit) {
        room_ite_drw(player.ply.px,player.ply.py);
        ply_act();
        ens_act(player.ply.px,player.ply.py);
        ply_drw();
        ens_drw(player.ply.px,player.ply.py);
        scr_fls();
        pause(0.01);
    }
    end();
    return 0;
}


