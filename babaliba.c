#include <stdio.h>

#include "babaliba.h"

sprite_t decorado;

static void mapa() {
    char* dd[]=  {   "00000000",
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
}

static void ini() {
    scr_ini(SCRW,SCRH);
    mapa();
    ply_ini();
}

static void end() {
    //decsprs_del();  
    spr_del(&decorado);
    scr_end();
    ply_end();
}

int main() {
    ini();
    room_dec_drw(player.px,player.py);
    ply_drw();
    while(!quit) {
        ply_act();
        ply_drw();
        scr_fls();
        pause(0.01);
    }
    end();
    return 0;
}


