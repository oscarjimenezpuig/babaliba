#include "babaliba.h"

decsprs_t decsprs=NULL;

static uchar decsprs_siz=0;

static void decspr_del(decspr_t d) {
    for(int j=0;j<2;j++) {
        for(int i=0;i<2;i++) {
            spr_del(&(d.spr[i][j]));
        }
    }
}

int decspr_new(char* d[],palette_t p) {
    decspr_t dsn;
    for(int j=0;j<2;j++) {
        for(int i=0;i<2;i++) {
            char* data[8];
            for(int fila=0;fila<8;fila++) {
                data[fila]=d[j*8+fila]+8*i;
            }
            dsn.spr[i][j]=spr_grd(8,data);
        }
    }
    for(int k=0;k<PALDIM;k++) {
        dsn.pal[k]=p[k];
    }
    void* ptr=realloc(decsprs,sizeof(decspr_t)*(decsprs_siz+1));
    if(ptr) {
        decsprs=ptr;
        decsprs[decsprs_siz]=dsn;
        return decsprs_siz++;
    } else {
        decspr_del(dsn);
    }
    return -1;
}

void decsprs_del() {
    for(int k=0;k<decsprs_siz;k++) {
        decspr_del(decsprs[k]);
    }
    free(decsprs);
    decsprs=NULL;
}

void decspr_drw(uchar c,uchar x,uchar y) {
    if(c<decsprs_siz) {
        int ix=x*SPRDIM;
        int iy=y*SPRDIM;
        decspr_t d=decsprs[c];
        for(int j=0;j<2;j++) {
            for(int i=0;i<2;i++) {
                spr_drw(d.spr[i][j],d.pal,ix+SPRDIM*i,iy+SPRDIM*j,PIXDIM);
            }
        }
    }
}


