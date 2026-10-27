#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define MAX_PROC 10
#define RUN_TESTS 5
int main(int argc, char *argv[])
{
    int sleep_ticks, n_proc, ret, proc_pid[MAX_PROC*RUN_TESTS];
    if (argc < 4) {
        printf("Usage: %s [SLEEP] [N_PROC] [TICKET1] [TICKET2]...\n", argv[0]);
        exit(-1);
    }
    sleep_ticks = atoi(argv[1]);
    n_proc = atoi(argv[2]);
    if (n_proc > MAX_PROC) {
        printf("Cannot test with more than %d processes\n", MAX_PROC);
        exit(-1);
    }
    for (int j = 0; j < RUN_TESTS; j++) {
        for (int i = 0; i < n_proc; i++) {
            int n_tickets = atoi(argv[3+i]);
            ret = fork();
            if (ret == 0) { // child process
                sched_tickets(n_tickets);
                while(1);
            }
            else { // parent
                proc_pid[i+j*n_proc] = ret;
                continue;
            }
        }
        sleep(sleep_ticks);
    } 
    for (int i = 0; i < n_proc*RUN_TESTS; i++) kill(proc_pid[i]);
    sched_statistics();
    exit(0);
}