#include "babaliba.h"

enemies_t enemies;

static sprite_t sol[1]; //sprite del soldado
static sprite_t skl[1]; //sprite del esqueleto
static sprite_t spd[1]; //sprite de la araña

static palette_t psol,pskl,pspd; //paletas de los diferentes sprites

static void sprdef() {
    static uchar init=0;
    if(!init) {
        char* dsol[]={      "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000"
        };
        char* dskl[]={      "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000"
        };
        char* dspd[]={      "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000",
                            "00000000"
        };
        sol[0]=spr_grd(8,dsol); 
        skl[0]=spr_grd(8,dskl); 
        spd[0]=spr_grd(8,dspd);
        psol[0]=col_new(255,0,0);
        pskl[0]=col_new(125,0,0);
        pspd[0]=col_new(50,0,0);
        init=1;
    }
}

static void ene_ale_pos(int* x,int* y) {
    //genera una posicion aleatoria para el enemigo
    *x=rnd(0,RDW*2)*SPRDIM;
    *y=rnd(1,RDH*2+1)*SPRDIM;
}

static object_t ene_new(uchar px,uchar py) {
    int num=rnd(0,2);
    object_t oe;
    switch(num) {
        case 0:
            oe=obj_new(ENEMY,sol[0],psol);
            break;
        case 1:
            oe=obj_new(ENEMY,skl[0],pskl);
            break;
        case 2:
            oe=obj_new(ENEMY,spd[0],pspd);
            break;
    }
    oe.ene.cls=num;
    int x,y;
    do {
        ene_ale_pos(&x,&y);
    }while(!room_obj_ins(px,py,x,y,&oe));
    return oe;
}   

int ene_ini(uchar px,uchar py) {
    sprdef();
    room_t r=map[px][py];
    uchar enes=r.enes;
    int k=0;
    for(;k<enes;k++) {
        enemies[k]=ene_new(px,py);
    }
    return k;
}

void ene_drw(uchar px,uchar py) {
    uchar enes=map[px][py].enes;
    for(uchar k=0;k<enes;k++) {
        obj_drw(enemies[k]);
    }
}
    





