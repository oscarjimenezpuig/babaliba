#include "babaliba.h"

#define DOPX 3
#define DOPY 9
#define DOX (6*SPRDIM)
#define DOY (2*SPRDIM)

static sprite_t sdoor[DOORS];
static palette_t pdoor;
static uchar close=1;

void dor_ini() {
    //inicio de los sprites y las paletas de la puerta
    char* sdi[]={   
                    " 0000000",
                    "01111111",
                    "01222222",
                    "01322222",
                    "01322222",
                    "01222222",
                    "01111111",
                    " 0000000"
    };
    char* sdd[]={
                    "0000000 ",
                    "11111110",
                    "22222210",
                    "22222210",
                    "22222210",
                    "22222210",
                    "11111110",
                    "0000000 "
    };
    sdoor[2]=spr_grd(8,sdi);
    sdoor[3]=spr_grd(8,sdd);
    sdoor[0]=spr_mov(sdoor[3],"y");
    sdoor[1]=spr_mov(sdoor[2],"y");
    pdoor[0]=col_new(59,35,20);
    pdoor[1]=col_new(122,74,33);
    pdoor[2]=col_new(184,115,51);
    pdoor[3]=col_new(255,210,63);
}

void dor_end() {
    for(uchar k=0;k<DOORS;k++) spr_del(sdoor+k);
}

int dor_col(object_t* obj,int x,int y) {
    if(player.ply.px==DOPX && player.ply.py==DOPY && close) {
        for(uchar k=0;k<DOORS;k++) {
            if(spr_col(obj->spr,x,y,PIXDIM,sdoor[k],DOX+k*SPRDIM,DOY,PIXDIM)) return 1;
        }
    }
    return 0;
}

void dor_opn() {
    for(uchar k=0;k<DOORS;k++) {
        spr_era(sdoor[k],DOX+k*SPRDIM,DOY,PIXDIM);
    }
    close=0;
}

void dor_drw() {
   if(close && player.ply.px==DOPX && player.ply.py==DOPY) {
       for(uchar k=0;k<DOORS;k++) {
           spr_drw(sdoor[k],pdoor,DOX+k*SPRDIM,DOY,PIXDIM);
       }
   }
}
