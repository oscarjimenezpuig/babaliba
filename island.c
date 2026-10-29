#include "babaliba.h"

#define SPRS 24

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
    decspr_new(spr+4,pal);
}

static void montana() {
    //dibujo del sprite de la montaña
    char* da[]={    "        ",
                    "       0",
                    "       0",
                    "      03",
                    "      03",
                    "     032",
                    "     023",
                    "    0222"
    };
    char* db[]={    "        ",
                    "0",
                    "30",
                    "30",
                    "330",
                    "310",
                    "2110",
                    "2110"
    };
    char* dc[]={    "    0222",
                    "   02222",
                    "   02222",
                    "  022212",
                    "  022222",
                    " 0221222",
                    " 0222222",
                    "00000000"
    };
    char* dd[]={    "21110",
                    "21110",
                    "221110",
                    "222110",
                    "2211110",
                    "2211110",
                    "22111110",
                    "00000000"
    };
    nspr(da);
    nspr(db);
    nspr(dc);
    nspr(dd);
    palette_t pal={col_new(34,28,48),col_new(96,92,120),col_new(160,165,180),col_new(245,248,255)};
    decspr_new(spr+8,pal);
}

static void muro() {
    char* da[]={    "33333330",
                    "32222210",
                    "32222210",
                    "32212210",
                    "32222210",
                    "32222210",
                    "11111110",
                    "00000000"
    };
    char* db[]={    "33333330",
                    "32222210",
                    "32222210",
                    "32221210",
                    "32222210",
                    "32212210",
                    "11111110",
                    "00000000"
    };
    char* dc[]={    "33303333",
                    "22103222",
                    "22103222",
                    "22103222",
                    "22103222",
                    "22103221",
                    "11101111",
                    "00000000"
    };
    char* dd[]={    "33303333",
                    "22103222",
                    "22103222",
                    "12103221",
                    "22103222",
                    "22103222",
                    "11101111",
                    "00000000"
    };
    nspr(da);
    nspr(db);
    nspr(dc);
    nspr(dd);
    palette_t pal={col_new(52,46,60),col_new(138,130,142),col_new(192,184,190),col_new(234,228,224)};
    decspr_new(spr+12,pal);
}

static void fuente() {
    char* da[]={    "        ",
                    "       3",
                    "      32",
                    "    3  2",
                    "   3  32",
                    "   00000",
                    "  013222",
                    "   00111"
    };
    char* db[]={    "",
                    "3",
                    "23",
                    "2  3",
                    "23  3",
                    "00000",
                    "222210",
                    "11100"
    };
    char* dc[]={    "      03",
                    "      03",
                    "  000000",
                    " 0333333",
                    "01322222",
                    "01111111",
                    " 0011111",
                    "   00000"
    };
    char* dd[]={    "10",
                    "10",
                    "000000",
                    "3333330",
                    "22222310",
                    "11111110",
                    "1111100",
                    "00000"
    };
    nspr(da);
    nspr(db);
    nspr(dc);
    nspr(dd);
    palette_t pal={col_new(20,24,48),col_new(96,104,128),col_new(64,160,224),col_new(220,240,255)};
    decspr_new(spr+16,pal);
}

static void ruina() {
    char* da[]={    "  000000",
                    " 0322222",
                    " 0111111",
                    "   00000",
                    "   03322",
                    "   03322",
                    "   03322",
                    "   03322"
    };
    char* db[]={    "000000",
                    "2222210",
                    "1111110",
                    "00000",
                    "22110",
                    "22110",
                    "22110",
                    "22110"
    };
    char* dc[]={    "   03322",
                    "   03322",
                    "   03322",
                    "   03322",
                    "   00000",
                    "  000000",
                    " 0322222",
                    " 0000000"
    };
    char* dd[]={    "22110",
                    "22110",
                    "22110",
                    "22110",
                    "00000",
                    "000000",
                    "2222210",
                    "0000000"
    };
    nspr(da);
    nspr(db);
    nspr(dc);
    nspr(dd);
    palette_t pal={col_new(15,15,27),col_new(58,63,92),col_new(138,143,176),col_new(230,232,245)};
    decspr_new(spr+20,pal);
}

#undef nspr

static void isl_map() {
    char map[80][80];
    FILE* file=fopen("mapa.map","r");
    if(file) {
        char c=0;
        uchar x,y;
        x=y=0;
        uchar line=0;
        while((c=fgetc(file))!='~') {
            if(c=='\n') {
                if(line) {
                    ++y;
                    line=0;
                }
                x=0;
            } else if(c!=' ') {
                map[x++][y]=c;
            }
        }
        fclose(file);
    }
    uchar px,py;
    uchar x,y;
    for(int f=0;f<80;f++) {
        py=f/8;
        y=f%8;
        for(int c=0;c<80;c++) {
            px=c/8;
            x=c%8;
            char ch=map[c][f];
            if(ch!='.') {
                uchar code=ch-'0';
                deco_t deco={x,y,code};
                room_dec(px,py,deco);
            }
        }
    }
}

void isl_ini() {
    agua();
    bosque();
    montana();
    muro();
    fuente();
    ruina();
    isl_map();
}

void isl_end() {
    decsprs_del();
    for(uchar k=0;k<SPRS;k++) spr_del(spr);
}



