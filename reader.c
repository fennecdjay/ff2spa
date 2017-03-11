#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <signal.h>
#include "soundpipe.h"

typedef struct {
    sp_fosc *osc;
    sp_ftbl *ft;
    int counter;
} UserData;
static UserData ud;
static sp_data *sp;
static const char* filename;

void reload(int unused) {
    sp_ftbl_destroy(&ud.ft);
    sp_fosc_destroy(&ud.osc);
	sp_ftbl_loadspa(sp, &ud.ft, filename);
    sp_fosc_create(&ud.osc);
    sp_fosc_init(sp, ud.osc, ud.ft);
}

void clean(int unused) {
    sp_ftbl_destroy(&ud.ft);
    sp_fosc_destroy(&ud.osc);
    sp_destroy(&sp);
	exit(1);
}

void process(sp_data *sp, void *udata) {
    if(ud.counter == 0){
        ud.osc->freq = 500 + rand() % 2000;
    }
    sp_fosc_compute(sp, ud.osc, NULL, &sp->out[0]);
    ud.counter = (ud.counter + 1) % 4410;
}

int main(int argc, char** argv) {
	if(argc < 2) {
		printf("requires a spa file as argument.\n");
		return 1;
	}
	signal(SIGUSR1, reload);
	signal(SIGKILL, clean);
	signal(SIGINT,  clean);
	filename = argv[1];
    srand(time(NULL));
    ud.counter = 0;
    sp_create(&sp);
	sp_ftbl_loadspa(sp, &ud.ft, filename);
    sp_fosc_create(&ud.osc);

    sp_fosc_init(sp, ud.osc, ud.ft);
    sp->len = 0;
	ud.counter = 0;
#ifdef HAVE_JACK
    sp_jack_process(sp, &ud, process);
#else
    sp_rpi_process(sp, &ud, process);
#endif
    sp_ftbl_destroy(&ud.ft);
    sp_fosc_destroy(&ud.osc);
    sp_destroy(&sp);
    return 0;
}
