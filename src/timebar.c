#include <time.h>
#include <stdio.h>
#include "timebar.h"

void print_bar(uint8_t width){
    for (int i = 0; i < width; i++)
        printf("=");
    printf("\n");
}

void update_time (uint8_t width){
    // TODO: Finish the timer updating function with escape sequence.
    time_t raw_time;
    struct tm * timeinfo;
    time(&raw_time);
    timeinfo = localtime(&raw_time);
    printf("\033[s");
    printf("\033[1;1H");
    print_bar(width);
    printf("\033[2:1H");
    printf( "Current Time: %s", asctime(timeinfo) );
    printf("\033[3:1H");
    print_bar(width);
    printf("\033[u");
    fflush(stdout);
}
