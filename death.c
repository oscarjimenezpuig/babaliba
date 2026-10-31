#include "babaliba.h"

#define DEASPRS 3
#define DEAOBS 3
#define ITEMAX 10

static sprite_t deathspr[DEASPRS];
static palette_t deathpal;

static death_t deaob[DEAOBS]; 

static void dea_ini() {
    //se inician los sprites de muerte
    char* data[]={  "   3 3",
                    "  32123",
                    "  321013",
                    " 3210012",
                    "  321012",
                    "  32123",
                    "   323",
                    "    3"
    };
    char* datb[]={  "    3",
                    "  3 2 3",
                    "   212  3",
                    " 3 2112",
                    "   21 2 3",
                    "  3 212",
                    "    2 3",
                    "     3"
    };
    char* datc[]={  "",
                    "  3  3",
                    "   3",
                    " 3  2 3",
                    "    3  3",
                    "  3",
                    "   3  3",
                    ""
    };
    deathpal[0]=col_new(70,70,76);
    deathpal[1]=col_new(120,120,128);
    deathpal[2]=col_new(175,175,182);
    deathpal[3]=col_new(225,225,230);
    deathspr[0]=spr_grd(8,data);
    deathspr[1]=spr_grd(8,datb);
    deathspr[2]=spr_grd(8,datc);
    dea_res();
}

void dea_new(int x,int y) {
    static uchar ini=0;
    if(!ini) {
        dea_ini();
        ini=1;
    }
    death_t* p=deaob;
    while(p!=deaob+DEAOBS) {
        if(p->off) {
            p->off=0;
            p->spr=0;
            p->ite=0;
            p->x=x;
            p->y=y;
            break;
        }
        p++;
    }
}

void dea_res() {
    death_t* p=deaob;
    while(p!=deaob+DEAOBS) {
        p->off=1;
        p++;
    }
}

void dea_act() {
    death_t* p=deaob;
    while(p!=deaob+DEAOBS) {
        if(p->off==0) {
            if(p->ite<ITEMAX) {
                p->ite++;
            } else {
                spr_era(deathspr[p->spr],p->x,p->y,PIXDIM);
                p->spr++;
                p->ite=0;
                if(p->spr==DEASPRS) {
                    p->off=1;
                }
            }
            if(!p->off) spr_drw(deathspr[p->spr],deathpal,p->x,p->y,PIXDIM);
        }
        p++;
    }
}

void dea_end() {
    for(uchar k=0;k<DEASPRS;k++) spr_del(deathspr+k);
}
