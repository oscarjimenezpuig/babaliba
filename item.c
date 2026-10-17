#include "item.c"

static sprite_t sswr, scrs, sddt;

static object_t wep[SWRS+CRSS+DDTS];

static void sprdef() {
    char* desp[]={      "       0",
                        "      0 ",
                        "     0  ",
                        "    0   ",
                        "   0    ",
                        "0 0     ",
                        " 0      ",
                        "0 0     "
    };
    char* dcrs[]={      "   00   ",
                        "   00   ",
                        "00000000",
                        "00000000",
                        "   00   ",
                        "   00   ",
                        "   00   ",
                        "   00   "
    };
    char* dins[]={      "   00   ",
                        "   00   ",
                        "        ",
                        "  0000  ",
                        " 000000 ",
                        " 000000 ",
                        " 000000 ",
                        " 000000 "
    };
    sswr=spr_grd(8,desp);
    scrs=spr_grd(8,dcrs);
    sddt=spr_grd(8,dins);
}

int ite_ini() {
    int swrs=SWRS;
    int crss=CRSS;
    int ddts=DDTS;
    while(swrs+crss+ddts) {
        int 


}

void ite_end() {
    spr_del(&esp);
    spr_del(&crs);
    spr_del(&ins);
}
