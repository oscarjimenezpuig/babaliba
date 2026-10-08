#include "babaliba.h"

object_t obj_new(uchar i,sprite_t s,palette_t p) {
    object_t o;
    o.id=i;
    o.spr=s;
    for(uchar k=0;k<PALDIM;k++) o.pal[k]=p[k];
    o.x=o.y=-1;
    o.px=o.py=NULLPP;
    o.con=NULL;
    o.act=0;
    return o;
}

void obj_plc(object_t* o,uchar px,uchar py,int x,int y) {
    o->px=px;
    o->py=py;
    o->x=x;
    o->y=y;
    o->act=1;
}

void obj_unplc(object_t* o) {
    o->x=o->y=-1;
    o->px=o->py=NULLPP;
    o->act=0;
}

int obj_con(object_t* o,object_t* c) {
    if(!o->con) {
        o->con=c;
        return 1;
    }
    return 0;
}

object_t* obj_mov(object_t* o,int x,int y) {
    object_t* oc=NULL;
    if(x>=0 && x<SCRW-SPRDIM && y>=SPRDIM && y<SCRH-2*SPRDIM) {
        uchar px=o->px;
        uchar py=o->py;    
        if(room_can_plc(px,py,*o,x,y)) {
            oc=room_obj_col(px,py,*o);
            if(!oc) {
                spr_era(o->spr,o->x,o->y,PIXDIM);
                o->x=x;
                o->y=y;
            }
        }
    }
    return oc;
}

void obj_drw(object_t o) {
   if(o.act) spr_drw(o.spr,o.pal,o.x,o.y,PIXDIM);
}
    
