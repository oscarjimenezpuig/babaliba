#include "babaliba.h"

decsprs_t decsprs=NULL;

static uchar decsprs_siz=0;

int decspr_new(sprite_t* s,palette_t p) {
    void* ptr=realloc(decsprs,sizeof(decspr_t)*(decsprs_siz+1));
    if(ptr) {
        decsprs=ptr;
        decspr_t dn={{{s[0],s[2]},{s[1],s[3]}},{p[0],p[1],p[2],p[3]}};
        decsprs[decsprs_siz]=dn;
        return decsprs_siz++;
    }
    return -1;
}

void decsprs_del() {
    free(decsprs);
}

void decspr_drw(uchar c,uchar x,uchar y) {
    if(c<decsprs_siz) {
        int ix=x*SPRDIM*2;
        int iy=y*SPRDIM*2+SPRDIM;
        decspr_t d=decsprs[c];
        for(int j=0;j<2;j++) {
            for(int i=0;i<2;i++) {
                spr_drw(d.spr[i][j],d.pal,ix+SPRDIM*i,iy+SPRDIM*j,PIXDIM);
            }
        }
    }
}


