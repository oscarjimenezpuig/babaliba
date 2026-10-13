#include "babaliba.h"

static sprite_t sol[1]; //sprite del soldado
static sprite_t skl[1]; //sprite del esqueleto
static sprite_t spd[1]; //sprite de la araña

static palette_t psol,pskl,pspd; //paletas de los diferentes sprites

static void sprdef() {
    static uchar init=0;
    if(!init) {
        char* dsol[]={      "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000"
        };
        char* dskl[]={      "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000"
        };
        char* dspd[]={      "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000"
        };
        sol[0]=spr_grd(8,dsol); 
        skl[0]=spr_grd(8,dskl); 
        spd[0]=spr_grd(8,dspd);
        psol[0]=col_new(255,0,0);
        pskl[0]=col_new(255,0,0);
        pspd[0]=col_new(255,0,0);
        init=1;
    }
}

void ene_ini(int px,int py,enemy_t* ene) {
    if(ene->act==1) {
        
        
}



