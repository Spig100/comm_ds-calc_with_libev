#include <stdio.h>
#include <ev.h>
#include <unistd.h>
#include "calc.h"

ev_io calc_watcher;
ev_timer timer_watcher;


static void calc_cb (EV_P_ ev_io *w, int revents){
    char_stack operator;
    int_stack operand;
    if (revents & EV_READ){
        char ch;
        bool isMD = false;
        while (read(w->fd, &ch, 1) > 0){
            switch(ch){
                case '+':
                case '-':
                    if(isMD){
                        calculate(&operand, &operator);
                        isMD = false;
                    } 
                    break;
                case '*':
                case '/':
                    if (!isMD) isMD = true;
                    calculate(&operand, &operator);
                    break;
                case ' ':
                    break;
                default:
                    break;
                    
            }
        }
    }
}

int main(){

    struct ev_loop *loop = EV_DEFAULT;

    ev_io_init(&calc_watcher, calc_cb, STDIN_FILENO, EV_READ);
    ev_io_start(EV_A_ &calc_watcher); /* EV_A_ marco is used to send the loop. we've declared.*/

    /* TODO: Finish the timer function.*/

    ev_run(EV_A_ 0);

    ev_loop_destroy(EV_A);

	return 0;
}
