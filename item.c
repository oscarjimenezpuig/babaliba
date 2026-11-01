#include "babaliba.h"

static sprite_t sswr, scrs, sddt,skey;
static palette_t pswr,pcrs,pddt,pkey;

static object_t wep[SWRS+CRSS+DDTS];
static object_t key;

static void sprdef() {
    char* desp[]={      "      21",
                        "     21",
                        "    21",
                        "   21",
                        "  21",
                        " 3333",
                        " 03",
                        "00"
    };
    char* dcrs[]={      "   12   ",
                        "   12   ",
                        "12222222",
                        "22222223",
                        "   22   ",
                        "   22   ",
                        "   23   ",
                        "   33   "
    };
    char* dins[]={      "     33",
                        "    333",
                        "  2222",
                        "  2112",
                        "  2102",
                        "  2112",
                        "  2222",
                        "  2222"
    };
    char* dkey[]={      "",
                        " 000",
                        "03220000",
                        "02022210",
                        "02210020",
                        " 000 020",
                        "     000",
                        ""
    };
    sswr=spr_grd(8,desp);
    scrs=spr_grd(8,dcrs);
    sddt=spr_grd(8,dins);
    skey=spr_grd(8,dkey);
    pswr[0]=col_new(59,36,16);
    pswr[1]=col_new(232,232,240);
    pswr[2]=col_new(138,144,160);
    pswr[3]=col_new(224,176,48);
    pcrs[0]=col_new(0,0,0);
    pcrs[1]=col_new(225,243,176);
    pcrs[2]=col_new(224,176,48);
    pcrs[3]=col_new(160,120,124);
    pddt[0]=col_new(0,0,0);
    pddt[1]=col_new(255,255,255);
    pddt[2]=col_new(208,40,40);
    pddt[3]=col_new(160,160,168);
    pkey[0]=col_new(74,48,12);
    pkey[1]=col_new(176,120,24);
    pkey[2]=col_new(240,184,48);
    pkey[3]=col_new(255,236,152);
}

static int one_ite_plc(object_t* item) {
    uchar px=rnd(0,MAPW-1);
    uchar py=rnd(0,MAPH-1);
    room_t r=map[px][py];
    if(r.ite==NULL) {
        int x,y;
        do {
            x=rnd(0,SCRW-SPRDIM);
            y=rnd(SPRDIM,SCRH-2*SPRDIM);
        }while(!room_obj_ins(px,py,x,y,item));
        return 1;
    }
    return 0;
}   

static void key_ini() {
    const uchar PX[]={9,9,9,8,7};
    const uchar PY[]={7,8,9,9,9};
    const uchar POS=5;
    key=obj_new(ITEM,skey,pkey);
    key.ite.cls=KEY;
    uchar n=rnd(0,POS-1);
    int x,y;
    do {
        x=rnd(0,SCRW-SPRDIM);
        y=rnd(SPRDIM,SCRH-2*SPRDIM);
    }while(!room_obj_ins(PX[n],PY[n],x,y,&key));
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
    key_ini();
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
    spr_del(&skey);
}
