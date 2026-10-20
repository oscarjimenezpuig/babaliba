#include "babaliba.h"

static sprite_t sswr, scrs, sddt;
static palette_t pswr,pcrs,pddt;

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
    pswr[0]=col_new(0,255,255);
    pcrs[0]=col_new(0,255,255);
    pddt[0]=col_new(0,255,255);
}

static void one_ite_plc(object_t* item) {
    uchar px=rnd(0,MAPW-1);
    uchar py=rnd(0,MAPH-1);
    room_t r=map[px][py];
    if(r.ite==NULL) {
        int x,y;
        do {
            x=rnd(0,SCRW-SPRDIM);
            y=rnd(SPRDIM,SCRH-2*SPRDIM);
        }while(!room_obj_ins(px,py,x,y,item));
    }
}   

static void one_ite_ini(ushort n,uchar weap) {
    sprite_t sweap[]={sswr,scrs,sddt};
    color_t* pweap[]={pswr,pcrs,pddt};
    uchar cweap[]={SWORD,CROSS,DDT};
    wep[n]=obj_new(ITEM,sweap[weap],pweap[weap]);
    wep[n].ite.cls=cweap[weap];
    one_ite_plc(wep+n);
}

void ite_ini() {
    sprdef();
    int weaps[]={SWRS,CRSS,DDTS};
    ushort counter=0;
    while(weaps[0]+weaps[1]+weaps[2]) {
        int weap=rnd(SWORD,DDT);
        if(weaps[weap]) {
            one_ite_ini(counter++,weap);
            weaps[weap]--;
        } 
    }
}

void ite_end() {
    spr_del(&sswr);
    spr_del(&scrs);
    spr_del(&sddt);
}
