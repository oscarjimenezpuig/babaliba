#include <stdio.h>

#include "babaliba.h"

static void ini() {
    scr_ini(SCRW,SCRH);
    txt_ini();
    isl_ini();
    dor_ini();
    ite_ini();
    ply_ini();
    ens_ini(player.ply.px,player.ply.py);
}

static void end() {
    //decsprs_del();  
    scr_end();
    txt_end();
    ply_end();
    ens_end();
    ite_end();
    isl_end();
    dea_end();
    dor_end();
}

int main() {
    ini();
    room_dec_drw(player.ply.px,player.ply.py);
    ply_drw();
    while(!quit) {
        room_ite_drw(player.ply.px,player.ply.py);
        dea_act();
        ply_act();
        ens_act(player.ply.px,player.ply.py);
        dor_drw();
        ply_drw();
        ens_drw(player.ply.px,player.ply.py);
        scr_fls();
        pause(0.01);
    }
    end();
    return 0;
}


