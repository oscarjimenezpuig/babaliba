#include "babaliba.h"

map_t map;

static void map_ini() {
    //inicia todo el mapa
    static uchar init=0;
    if(!init) {
        init=1;
        for(uchar i=0;i<MAPW;i++) {
            for(uchar j=0;j<MAPH;j++) {
                map[i][j]=(room_t){{0,0},{},{}};
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

int room_obj(uchar px,uchar py,int x,int y,object_t* obj) {
    if(room_can_plc(px,py,*obj,x,y)) {
        obj_unplc(obj);
        obj_plc(obj,px,py,x,y);
        return 1;
    }
    return 0;
}

int room_can_plc(uchar px,uchar py,object_t o,int x,int y) {
    room_t r=map[px][py];
    for(uchar k=0;k<r.decs;k++) {
        deco_t d=r.dec[k];
        for(uchar i=0;i<2;i++) {
            for(uchar j=0;j<2;j++) {
                decspr_t ds=decsprs[d.cod];
                sprite_t s=ds.spr[i][j];
                if(spr_col(s,d.x+PIXDIM*8*i,d.y+PIXDIM*8*j,PIXDIM,o.spr,x,y,PIXDIM)) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

object_t* room_obj_col(uchar px,uchar py,object_t o) {
    room_t r=map[px][py];
    for(uchar k=0;k<r.objs;k++) {
        object_t* po=r.obj[k];
        if(o.id!=po->id && spr_col(o.spr,o.x,o.y,PIXDIM,po->spr,po->x,po->y,PIXDIM)) return po;
    }
    return NULL;
}

void room_dec_drw(uchar px,uchar py) {
    room_t r=map[px][py];
    for(uchar k=0;k<r.decs;k++) {
        deco_t d=r.dec[k];
        decspr_drw(d.cod,d.x,d.y);
    }
}

void room_obj_drw(uchar px,uchar py) {
room_t r=map[px][py];
    for(uchar k=0;k<r.objs;k++) {
        object_t* o=r.obj[k];
        obj_drw(*o);
    }
}
