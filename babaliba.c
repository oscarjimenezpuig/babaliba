#include <stdio.h>

#include "babaliba.h"

static void mapa() {
    char* a[]={     "aaaaaaaa",
                    "a       ",
                    "aaa     ",
                    "a       ",
                    "a   bb  ",
                    "a       ",
                    "a",
                    "a"
    };
    char* b[]={     "aaaaaaaa",
                    "       a",
                    " bb    a",
                    "   b   a",
                    "       a",
                    "  f    a",
                    "       a",
                    "       a"
    };
    char* c[]={     "a",
                    "a",
                    "a   ddd",
                    "a   d",
                    "a   d e",
                    "a   d",
                    "a",
                    "aaaaaaaa"
    };
    char* d[]={     "       a",
                    "       a",
                    "  c    a",
                    " ccc   a",
                    " c     a",
                    "       a",
                    "  bbb  a",
                    "aaaaaaaa"
    };
    uchar decod[]={0,1,2,3,4,5};
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
    isl_ini();
    mapa();
    ite_ini();
    ply_ini();
    ens_ini(player.ply.px,player.ply.py);
}

static void end() {
    //decsprs_del();  
    scr_end();
    txt_end();
    ply_end();
    ens_end();
    ite_end();
    isl_end();
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


