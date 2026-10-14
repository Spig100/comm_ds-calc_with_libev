#include <stdio.h>
#include <ev.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include "main.h"
#include "calc.h"
#include "timebar.h"

ev_io calc_watcher;
ev_timer timer_watcher;
ev_signal terminate_watcher;
ev_signal resize_watcher;

uint8_t window_width = 0;

struct winsize ws;

static void resize_cb(EV_P_ ev_signal *w, int revents){
    if( ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 ) 
        fprintf(stderr, "Debug: Get windows size failed");
    window_width = ws.ws_col;
    update_time(window_width);
}

static void calc_cb (EV_P_ ev_io *w, int revents){
    
    /* Because of the design of libev, we need to make the 
     * input be processed here. 
     * (ev_io will not handle the input detection, 
     * e.g., the "enter pressed" event)
     * 
     * So we need to:
     * - Create a buffer to save the current input.
     * - Make a logic to detect if '\n' is input or not.*/

    char buf[STRING_BUFFER_SIZE];
    
    if (feof(stdin))
        // EOF detected
        ev_break(EV_A_ EVBREAK_ALL);


    if (fgets(buf, sizeof(buf), stdin) == NULL)
        
        return;
    
    /* Note that `strchr` is from string.h. 
     * It will return the first occurance address of the aspect char 
     * in the string. 
     *
     * This is a function I've asked from ChatGPT on Oct. 8.
     *
     * */
    
    if (strchr(buf, '\n') != NULL){
        
        /* `strcspn` will return the array index of the aspect charector.
         *
         * Note that strchr will return the "memory address".
         *
         * This is a function I've asked from ChatGPT on Oct. 8.
         * */

        buf[strcspn(buf, "\n")] = '\0'; 
        // Replacing '\n' for comparision. (This is an idea from ChatGPT.)

        // printf("Debug: CALLBACK SUCCESS.\n");
        
        // printf("Debug: String input - %s\n", buf);

        if ( (strcmp(buf, "exit") == 0) || (strcmp(buf, "quit") == 0)){
            // printf("DEBUG: Process termiated by user.\n");
            ev_io_stop(EV_A_ w);
            ev_break(EV_A_ EVBREAK_ALL);
            return;
        }

        // printf("Result\t= %.2f\n\n", calculate(buf));
        
        calculate(buf);
        
        printf("Expression\t> ");
        fflush(stdout);

    }

    update_time(window_width);
}

static void terminated_cb(EV_P_ ev_signal *w, int revents){
    ev_break(EV_A_ EVBREAK_ALL);
}

static void timer_cb(EV_P_ ev_timer *w, int revents){
    update_time(window_width);
}

int main(){
    
    printf("\033[?1049h"); // Change to the alternate screen by ASCII Esc Sequence.
    printf("\033[5;r");

    fflush(stdout);
    
    struct ev_loop *loop = EV_DEFAULT;
    
    ev_timer_init(&timer_watcher, timer_cb, 0.0, 1.0);
    ev_timer_start(EV_A_ &timer_watcher);

    ev_signal_init(&terminate_watcher, terminated_cb, SIGINT);
    ev_signal_start(EV_A_ &terminate_watcher);

    ev_signal_init(&resize_watcher, resize_cb, SIGWINCH);
    ev_signal_start(EV_A_ &resize_watcher);

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
        perror("ioctl");
    }

    window_width = ws.ws_col;

    ev_io_init(&calc_watcher, calc_cb, STDIN_FILENO, EV_READ);
    ev_io_start(EV_A_ &calc_watcher); 
    /* EV_A_ marco is used to send the loop we've declared.*/

    /* TODO: Finish the timer function.*/
    
    printf("\033[5;1H");
    printf("Expression\t> ");
    fflush(stdout);

    ev_run(EV_A_ 0);
    ev_loop_destroy(EV_A);

    printf("\033[?1049l");
    fflush(stdout);
    
    return 0;

}
