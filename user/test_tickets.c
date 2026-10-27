#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char * argv[]){
    printf("printing sched_statistics call: \n");
    sched_statistics();

    int ret = fork();

    if (ret == 0) {
        sched_tickets(5000);
        printf("tickets assigned");
        while(1);
    } 
    sleep(10);
    sched_statistics();
    kill(ret);
    exit(0);
}