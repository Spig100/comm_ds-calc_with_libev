#include <stdio.h>
#include <ev.h>
#include <unistd.h>
#include <string.h>
#include "main.h"
#include "calc.h"

ev_io calc_watcher;
ev_timer timer_watcher;


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

        buf[strcspn(buf, "\n")] = '\0'; // Replacing '\n' for comparision.

        // printf("Debug: CALLBACK SUCCESS.\n");
        
        // printf("Debug: String input - %s\n", buf);

        if ( (strcmp(buf, "exit") == 0) || (strcmp(buf, "quit") == 0)){
            // printf("DEBUG: Process termiated by user.\n");
            ev_io_stop(EV_A_ w);
            ev_loop(EV_A_ EVBREAK_ALL);
            return;
        }

        printf("Result\t= %.2f\n\n", calculate(buf));
        printf("Expression\t> ");
        fflush(stdout);

    }

}

int main(){

    struct ev_loop *loop = EV_DEFAULT;

    ev_io_init(&calc_watcher, calc_cb, STDIN_FILENO, EV_READ);
    ev_io_start(EV_A_ &calc_watcher); 
    /* EV_A_ marco is used to send the loop we've declared.*/

    /* TODO: Finish the timer function.*/
    
    printf("Expression\t> ");
    fflush(stdout);

    ev_run(EV_A_ 0);

    ev_loop_destroy(EV_A);

	return 0;

}
