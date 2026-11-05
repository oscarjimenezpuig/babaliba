#include "babaliba.h"

object_t coin[COINS];
object_t life;

static sprite_t sswr, scrs, sddt,skey,scoi,slif;
static palette_t pswr,pcrs,pddt,pkey,pcoi,plif;

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
    char* dcoi[]={      "  0000",
                        " 011220",
                        "01233220",
                        "01233220",
                        "02233220",
                        "02233220",
                        " 022220",
                        "  0000"
    };
    char* dlif[]={      " 00  00 ",
                        "03300220",
                        "03222220",
                        "02222210",
                        "02222110",
                        " 022110",
                        "  0110",
                        "   00"
    };
    sswr=spr_grd(8,desp);
    scrs=spr_grd(8,dcrs);
    sddt=spr_grd(8,dins);
    skey=spr_grd(8,dkey);
    scoi=spr_grd(8,dcoi);
    slif=spr_grd(8,dlif);
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
    pcoi[0]=col_new(110,66,0);
    pcoi[1]=col_new(255,240,150);
    pcoi[2]=col_new(240,180,20);
    pcoi[3]=col_new(180,110,10);
    plif[0]=col_new(90,0,20);
    plif[1]=col_new(160,10,40);
    plif[2]=col_new(220,30,50);
    plif[3]=col_new(255,170,180);
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

static void coi_pan(uchar* px,uchar* py,uchar xmin,uchar xmax,uchar ymin,uchar ymax) {
    *px=rnd(xmin,xmax);
    *py=rnd(ymin,ymax);
}

static void coi_ini() {
    uchar XMIN[]={5,8,4,4};
    uchar XMAX[]={8,9,9,9};
    uchar YMIN[]={0,3,5,6};
    uchar YMAX[]={1,5,6,7};
    for(uchar nc=0;nc<COINS;nc++) {
        coin[nc]=obj_new(ITEM,scoi,pcoi);
        coin[nc].ite.cls=COIN;
        uchar px,py;
        coi_pan(&px,&py,XMIN[nc],XMAX[nc],YMIN[nc],YMAX[nc]);
        int x,y;
        do {
            x=rnd(0,SCRW-SPRDIM);
            y=rnd(SPRDIM,SCRH-2*SPRDIM);
        } while(!room_obj_ins(px,py,x,y,coin+nc));
    }
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

static void lif_ini() {
    life=obj_new(ITEM,slif,plif);
    life.ite.cls=LIFE;
    while(!one_ite_plc(&life));
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
    coi_ini();
    key_ini();
    lif_ini();
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
    spr_del(&scoi);
    spr_del(&slif);
}
