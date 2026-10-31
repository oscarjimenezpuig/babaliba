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

int obj_mov(object_t* o,uchar px,uchar py,int x,int y,colision_t col) {
    object_t* oc=NULL;
    if(x>=0 && x<=SCRW-SPRDIM && y>=SPRDIM && y<=SCRH-2*SPRDIM) {
        if(room_can_plc(px,py,o,x,y)) {
            oc=room_obj_col(px,py,o,x,y);
            if(!oc && o->typ==PLAYER) o->ply.bnt=0;
            if(!oc || col==NULL || !col(oc)) {
                spr_era(o->spr,o->x,o->y,PIXDIM);
                o->x=x;
                o->y=y;
                return 1;
            }
        }
    }
    return 0;
}

void obj_drw(object_t o) {
   if(o.act) spr_drw(o.spr,o.pal,o.x,o.y,PIXDIM);
}
    
