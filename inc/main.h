#ifndef MAIN_H
#define MAIN_H

#include <ev.h>

#define STRING_BUFFER_SIZE 256

static void calc_cb (EV_P_ ev_io *w, int revents);
static void terminated_cb(EV_P_ ev_signal *w, int revents);

#endif
