#include "babaliba.h"

int room_new(uchar c,uchar r,int d[RDW][RDH],uchar es) {
    room_t r;
    if(es<4) {
        r.decs=0;
        r.enes=es;
        for(uchar j=0;j<RDH;j++) {
            for(uchar i=0;i<RDW;i++) {
                int a=d[i][j];
                if(a!=-1 && r.decs<DECS) {
                    deco_t d={i,j,a};
                    r.dec[r.decs++]=d;
                }
            }
        }
        map[c][r]=r;
        return 1;
    }
    return 0;
}


