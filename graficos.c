#include "castle.h"

sprite_t spared[4];
sprite_t sescalera;
sprite_t sespada[2];
sprite_t sheroe[3];

palette_t ppared[3];
palette_t pescalera,pespada,pheroe;

static void pal_def(palette_t p,color_t a,color_t b,color_t c,color_t d) {
    p[0]=a;
    p[1]=b;
    p[2]=c;
    p[3]=d;
}

static void spared_def() {
    char* d1[]={    "00000000",
                    "00000000",
                    "00000011",
                    "00000011", 
                    "00001111", 
                    "00001111", 
                    "00111111", 
                    "00111111"
    };
    char* d2[]={    "00000000",
                    "00000000",
                    "11111111",
                    "11111111",
                    "11111111",
                    "11111111",
                    "11111111",
                    "11111111"
    };
    char* d3[]={    "00000000",
                    "00000000",
                    "00000000",
                    "00000000",
                    "00000000",
                    "00000000",
                    "00000000",
                    "22222222"
    };
    char* d4[]={    "11111111",
                    "11111111",
                    "11111111",
                    "11111111",
                    "11111111",
                    "00000000",
                    "00000000",
                    "22222222"
    };
    spared[0]=spr_grd(8,d1);
    spared[1]=spr_grd(8,d2);
    spared[2]=spr_grd(8,d3);
    spared[3]=spr_grd(8,d4);
    color_t darkgrey=col_new(10,10,10);
    pal_def(ppared[0],col_new(0,0,255),col_new(0,0,200),darkgrey,BLACK);
    pal_def(ppared[1],col_new(0,0,130),col_new(0,0,65),darkgrey,BLACK);
    pal_def(ppared[2],col_new(200,0,0),col_new(125,0,0),darkgrey,BLACK);
}

static void sescalera_def() {
    char* d[]={     "1      0",
                    "11000000",
                    "11111110",
                    "1      0",
                    "1      0",
                    "11000000",
                    "11111110",
                    "1      0"
    };
    sescalera=spr_grd(8,d);
    pescalera[0]=col_new(238,208,157);
    pescalera[1]=col_new(101,67,33);
}

static void sespada_def() {
    char* d[]={     "       1",
                    "      12",
                    "     123",
                    "    123 ",
                    "  0123  ",
                    " 003    ",
                    "01      ",
                    "1       "
    };
    sespada[0]=spr_grd(8,d);
    sespada[1]=spr_mov(sespada[0],"y");
    pespada[1]=WHITE;
    pespada[2]=col_new(175,175,175);
    pespada[3]=col_new(80,80,80);
    pespada[0]=col_new(205,127,50);
}

static void sheroe_def() {
    char* df[]={    "   221  ",
                    "  23311 ",
                    "  22211 ",
                    "  02220 ",
                    " 002220 ",
                    "  0232  ",
                    "   3 3  ",
                    "  33 33 "
    };
    char* de[]={    "   222  ",
                    "  23332 ",
                    "  22322 ",
                    "  02020 ",
                    " 200002 ",
                    " 300003 ",
                    "   33   ",
                    "  33    "
    };              
    sheroe[0]=spr_grd(8,df);
    sheroe[1]=spr_mov(sespada[0],"y");
    sheroe[2]=spr_grd(8,de);
    pheroe[0]=col_new(200,40,40);
    pheroe[1]=col_new(245,190,150);
    pheroe[2]=col_new(150,170,185);
    pheroe[3]=col_new(45,45,55);
}

void graf_ini() {
    spared_def();
    sescalera_def();
    sespada_def();
    sheroe_def();
}

static void mspd(int sps,sprite_t* sp) {
    for(int k=0;k<sps;k++) spr_del(sp+k);
}

void graf_end() {
    mspd(4,spared);
    spr_del(&sescalera);
    mspd(2,sespada);
    mspd(3,sheroe);
}
