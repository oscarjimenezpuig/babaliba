#include "babaliba.h"

#define SPRS 16

sprite_t spr[SPRS];

uchar sprs=0;

#define nspr(D) spr[sprs++]=spr_grd(8,D)

static void agua() {
    char* da[]={    "00000000",
                    "00011100",
                    "00123210",
                    "00333321",
                    "02333211",
                    "02221100",
                    "00000000",
                    "00000000"
    };
    char* db[]={    "00000000",
                    "00000000",
                    "00000000",
                    "00000000",
                    "00000000",
                    "00000000",
                    "01100000",
                    "23100000"
    };
    char* dc[]={    "00000003",
                    "00000023",
                    "00000000",
                    "00000000",
                    "00011100",
                    "00123210",
                    "00333321",
                    "02333211"
    };
    char* dd[]={    "33210000",
                    "21100000",
                    "00000000",
                    "00000000",
                    "00000000",
                    "00000000",
                    "00000000",
                    "00000000"
    };
    nspr(da);
    nspr(db);
    nspr(dc);
    nspr(dd);
    palette_t pal={col_new(0,119,190),col_new(176,224,230),col_new(64,224,208),col_new(0,71,171)};
    decspr_new(spr,pal);
}   

static void bosque() {
    //dibujo de todos los sprites del decorado con sus paletas
    char* da[]={    "      11",
                    "     111",
                    "    1111",
                    "    1111",
                    "    1111",
                    "    1110",
                    "    1110",
                    "    1100"
    };
    char* db[]={    "111     ",
                    "1111    ",
                    "1111    ",
                    "1100    ",
                    "0000    ",
                    "0000    ",
                    "0000    ",
                    "0000    "
    };
    char* dc[]={    "     110",
                    "     110",
                    "      00",
                    "        ",
                    "        ",
                    "       2",
                    "      22",
                    "     222"
    };
    char* dd[]={    "0000    ",
                    "000",
                    "2300",
                    "23",
                    "23",
                    "233",
                    "2333",
                    "2333"
    };
    nspr(da);
    nspr(db);
    nspr(dc);
    nspr(dd);
    palette_t pal={col_new(38,92,66),col_new(106,190,48),col_new(143,86,59),col_new(74,42,29)};
    decspr_new(spr,pal);
}

void isl_ini() {
    agua();
    bosque();
}

void isl_end() {
    decsprs_del();
    for(uchar k=0;k<SPRS;k++) spr_del(spr);
}



