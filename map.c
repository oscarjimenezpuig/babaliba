#include "babaliba.h"

map_t map;

static void map_ini() {
    //inicia todo el mapa
    static uchar init=0;
    if(!init) {
        init=1;
        for(uchar i=0;i<MAPW;i++) {
            for(uchar j=0;j<MAPH;j++) {
                map[i][j]=(room_t){{0,0},{},NULL};
            }
        }
    }
}

void room_dec(uchar px,uchar py,uchar ds,...) {
    map_ini();
    room_t* r=&(map[px][py]);
    va_list l;
    va_start(l,ds);
    for(uchar k=0;k<ds && r->decs<DECS;k++) r->dec[r->decs++]=va_arg(l,deco_t);
    va_end(l);
}

void room_dec_grd(uchar px,uchar py,uchar* d,char* data[]) {
    map_ini();
    room_t* r=&(map[px][py]);
    for(uchar k=0;k<8;k++) {
        char* p=data[k];
        while(*p!='\0') {
            if(*p!=' ') {
                uchar cc=*p-'0';
                deco_t dn={p-data[k],k,d[cc]};
                r->dec[r->decs++]=dn;
            }
            p++;
        }
    }
}

void room_set_ene(uchar px,uchar py,uchar enes) {
    map[px][py].enes=enes;
}

int room_can_plc(uchar px,uchar py,object_t* o,int x,int y) {
    room_t r=map[px][py];
    for(uchar k=0;k<r.decs;k++) {
        deco_t d=r.dec[k];
        for(uchar i=0;i<2;i++) {
            for(uchar j=0;j<2;j++) {
                decspr_t ds=decsprs[d.cod];
                sprite_t s=ds.spr[i][j];
                if(spr_col(s,d.x*2*SPRDIM+SPRDIM*i,d.y*2*SPRDIM+SPRDIM+SPRDIM*j,PIXDIM,o->spr,x,y,PIXDIM)) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

static int obj_col_obj(object_t a,int x,int y,object_t b) {
    //dice si el objeto a colisiona con el b
    return spr_col(a.spr,x,y,PIXDIM,b.spr,b.x,b.y,PIXDIM);
}

object_t* room_obj_col(uchar px,uchar py,object_t* o,int x,int y) {
    if(o->typ!=PLAYER && obj_col_obj(*o,x,y,player)) return &player;
    room_t r=map[px][py];
    for(uchar k=0;k<r.enes;k++) {
        if(o!=enemies+k && obj_col_obj(*o,x,y,enemies[k])) return enemies+k;
    }
    if(o->typ==PLAYER && r.ite && obj_col_obj(*o,x,y,*(r.ite))) return r.ite;
    return NULL;
}

int room_obj_ins(uchar px,uchar py,int x,int y,object_t* o) {
    if(room_can_plc(px,py,o,x,y) && room_obj_col(px,py,o,x,y)==NULL) {
        if(o->typ!=ITEM || map[px][py].ite==NULL) {    
            o->x=x;
            o->y=y;
            o->act=1;
            if(o->typ==ITEM) map[px][py].ite=o;
            else if(o->typ==PLAYER) {
                o->ply.px=px;
                o->ply.py=py;
            }
            return 1;
        }
    }
    return 0;
}

void room_obj_era(uchar px,uchar py,object_t* o) {
    room_t* r=&(map[px][py]);
    if(o->typ==PLAYER) {
        o->ply.px=o->ply.py=NULLPP;
    } else if(o->typ==ITEM) {
        r->ite=NULL;
    }
    o->x=o->y=-1;
    o->act=0;
}

void room_dec_drw(uchar px,uchar py) {
    room_t r=map[px][py];
    for(uchar k=0;k<r.decs;k++) {
        deco_t d=r.dec[k];
        decspr_drw(d.cod,d.x,d.y);
    }
}

void room_ite_drw(uchar px,uchar py) {
    room_t r=map[px][py];
    if(r.ite) obj_drw(*(r.ite));
}

void room_ene_drw(uchar px,uchar py) {
    room_t r=map[px][py];
    uchar enes=r.enes;
    for(uchar k=0;k<enes;k++) {
        obj_drw(enemies[k]);
    }
}
