#include "babaliba.h"

static void map_ini() {
    //inicia todo el mapa
    static uchar init=0;
    if(!init) {
        init=1;
        for(uchar i=0;i<MAPW;i++) {
            for(uchar j=0;j<MAPH;j++) {
                map[i][j]=(room_t){{0,0}};
            }
        }
    }
}

int room_dec(uchar px,uchar py,uchar ds,...) {
    map_ini();
    room_t* r=&(map[px][py]);
    va_list l;
    va_start(l,ds);
    for(uchar k=0;k<ds && r->dec<DECS;k++) r->dec[r->dec++]=va_arg(l,deco_t);
    va_end(l);
}

int room_obj(uchar px,uchar py,int x,int y,object_t* obj) {
    if(room_can_plc(*obj,x,y)) {
        obj->unplc(obj);
        obj_plc(obj,px,py,x,y);
        return 1;
    }
    return 0;
}

int room_can_plc(uchar px,uchar py,object_t o,int x,int y) {
    room_t r=map[px][py];
    for(uchar k=0;k<r.decs;r++) {
        deco_t d=r.dec[k];
        for(uchar i=0;i<2;i++) {
            for(uchar j=0;j<2;j++) {
                if(spr_col(d.spr[i][j],d.x+PIXDIM*8*i,dy+PIXDIM*8*j,o.spr,x,y)) {
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
        object_t* po=obj[k];
        if(o.id!=o->id && spr_col(o.spr,o.x,o.y,po->spr,po->x,po->y)) return po;
    }
    return NULL;
}

//TODO Programar los dibujos de los objetos y decorados
    


