#include <stdio.h>

#include "babaliba.h"

static void ini() {
    scr_ini(SCRW,SCRH);
}

static void end() {
    //decsprs_del();  
    scr_end();
}

static void alfombra() {
    char* data[]={  "11111111",
                    "1       ",
                    "1 111111",
                    "1 1     ",
                    "1 1 1111",
                    "1 1 1   ",
                    "1 1 1 11",
                    "1 1 1 1 "
    };
    sprite_t al[4];
    al[0]=spr_grd(8,data);
    al[1]=spr_mov(al[0],"y");
    al[2]=spr_mov(al[0],"x");
    al[3]=spr_mov(al[1],"x");
    palette_t p={BLACK,col_new(255,0,0)};
    int cal=decspr_new(al,p);
    if(cal==-1) puts("ERROR");
    else {
        decspr_drw(cal,7,7);
        decspr_drw(cal,0,0);
        decspr_drw(cal,7,0);
        decspr_drw(cal,0,7);
        scr_fls();
    }
    for(int k=0;k<4;k++) spr_del(al+k);
}

int main() {
    ini();
    alfombra();
    getchar();
    end();
    return 0;
}


