#include "babaliba.h"

enemies_t enemies;

#define SOLS 1
#define SKLS 1
#define SPDS 1

static sprite_t sol[SOLS]; //sprite del soldado
static sprite_t skl[SKLS]; //sprite del esqueleto
static sprite_t spd[SPDS]; //sprite de la araña

static palette_t psol,pskl,pspd; //paletas de los diferentes sprites

static void sprdef() {
    static uchar init=0;
    if(!init) {
        char* dspd[]={      "2  00  2",
                            " 2 00 2",
                            "2 0110 2",
                            " 203302  ",
                            "20000002",
                            " 200002",
                            "2 2  2 2",
                            "2      2"
        };
        char* dskl[]={      "  1111",
                            " 131131",
                            "  1001",
                            "  1212",
                            " 111111",
                            " 121121",
                            "  1  1",
                            " 11  11"
        };
        char* dsol[]={      "  3333",
                            " 333333",
                            "  1001",
                            " 222222",
                            "12222223",
                            " 222222",
                            "  2  2",
                            " 00  00"
        };
        sol[0]=spr_grd(8,dsol); 
        skl[0]=spr_grd(8,dskl); 
        spd[0]=spr_grd(8,dspd);
        psol[0]=col_new(32,33,20);
        psol[1]=col_new(240,192,144);
        psol[2]=col_new(168,32,40);
        psol[3]=col_new(176,184,196);
        pskl[0]=col_new(0,0,0);
        pskl[1]=col_new(237,232,208);
        pskl[2]=col_new(138,136,120);
        pskl[3]=col_new(224,32,32);
        pspd[0]=col_new(16,16,16);
        pspd[1]=col_new(255,32,32);
        pspd[2]=col_new(112,112,120);
        pspd[3]=col_new(248,248,248);
        init=1;
    }
}

static void ene_ale_pos(int* x,int* y) {
    //genera una posicion aleatoria para el enemigo
    *x=rnd(0,SCRW-SPRDIM);
    *y=rnd(SPRDIM,SCRH-2*SPRDIM);
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
    oe.ene.vx=oe.ene.vy=0;
    int x,y;
    do {
        ene_ale_pos(&x,&y);
    }while(!room_obj_ins(px,py,x,y,&oe));
    return oe;
}   

int ens_ini(uchar px,uchar py) {
    sprdef();
    room_t* r=&(map[px][py]);
    uchar enes=r->enes;
    r->enes=0;
    for(;r->enes<enes;r->enes++) {
        enemies[r->enes]=ene_new(px,py);
    }
    return r->enes;
}

void ens_end() {
    for(uchar k=0;k<SOLS;k++) spr_del(sol+k);
    for(uchar k=0;k<SKLS;k++) spr_del(skl+k);
    for(uchar k=0;k<SPDS;k++) spr_del(spd+k);
}

static schar setrnddir() {
    int val=rnd(0,2);
    val=(val==2)?-1:val;
    return val;
}

static int ene_prs(object_t* e) {
    //persecucion del objeto
    if(e->y>=player.y && e->y<player.y+SPRDIM) {
        e->ene.vy=0;
        if(e->x>player.x) e->ene.vx=-1;
        else e->ene.vx=1;
        return 1;
    } else if(e->x>=player.x && e->x<player.x+SPRDIM) {
        e->ene.vx=0;
        if(e->y>player.y) e->ene.vy=-1;
        else e->ene.vy=1;
        return 1;
    }
    return 0;
}

static void ene_rnd(object_t* e) {
    //movimiento random
    const uchar PCD=5; //probabilidad de cambio de direccion
    if(e->ene.vx==0 && e->ene.vy==0) {
        if(rnd(0,1)) {
            e->ene.vx=setrnddir();
        } else {
            e->ene.vy=setrnddir();
        }
    } else if(rnd(0,99)<PCD) {
        e->ene.vx=e->ene.vy;
    }
}

object_t* enemy=NULL;

static int ene_col(object_t* obj) {
    if(obj->typ==PLAYER) {
        ply_col(enemy);
        return 1;
    }
    return 0;
}

static void ene_act(object_t* e,uchar px,uchar py) {
    //accion de un enemigo
    enemy=e;
    int pom=(e->ene.cls==SOLDIER)?SOLPOM:(e->ene.cls==SKELETON)?SKEPOM:SPDPOM;
    if(e->act && rnd(0,99)<pom) {
        if(!ene_prs(e)) ene_rnd(e);
        int x=e->x+PIXDIM*e->ene.vx;
        int y=e->y+PIXDIM*e->ene.vy;
        if(!obj_mov(e,px,py,x,y,ene_col)) {
            e->ene.vx=e->ene.vy=0;
        }
    }
} 

void ens_act(uchar px,uchar py) {
    uchar enes=map[px][py].enes;
    for(uchar k=0;k<enes;k++) {
        ene_act(enemies+k,px,py);
    }
}

void ens_drw(uchar px,uchar py) {
    uchar enes=map[px][py].enes;
    for(uchar k=0;k<enes;k++) {
        if(enemies[k].act) obj_drw(enemies[k]);
    }
}
    





