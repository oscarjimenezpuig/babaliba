#include "babaliba.h"

object_t obj_new(uchar t,sprite_t s,palette_t p) {
    object_t o;
    o.typ=t;
    o.spr=s;
    for(uchar k=0;k<PALDIM;k++) o.pal[k]=p[k];
    o.x=o.y=-1;
    o.act=0;
    return o;
}

object_t* obj_mov(object_t* o,uchar px,uchar py,int x,int y) {
    object_t* oc=NULL;
    if(x>=0 && x<=SCRW-SPRDIM && y>=SPRDIM && y<=SCRH-2*SPRDIM) {
        if(room_can_plc(px,py,o,x,y)) {
            oc=room_obj_col(px,py,o,x,y);
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
    
