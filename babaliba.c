#include <stdio.h>

#include "babaliba.h"

static void ini() {
    scr_ini(SCRW,SCRH);
}

static void end() {
    scr_end();
    decsprs_del();
}

int main() {
    ini();
    getchar();
    end();
    return 0;
}


