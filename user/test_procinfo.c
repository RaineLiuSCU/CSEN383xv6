#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define MAXPROC 10
#define MAXMEM 131072
void print_sysinfo(void)
{
    int n_active_proc, n_syscalls, n_free_pages;
    n_active_proc = sysinfo(0);
    n_syscalls = sysinfo(1);
    n_free_pages = sysinfo(2);
    printf("[sysinfo] active proc: %d, syscalls: %d, free pages: %d\n",
        n_active_proc, n_syscalls, n_free_pages);
}

struct pinfo {
    int ppid;
    int syscall_count;
    int page_usage;
};
int main(int argc, char *argv[]) {
    if (argc != 3) {
        exit(0);
    }
    int n_proc = atoi(argv[1]);
    int mem_size = atoi(argv[2]);
    if (n_proc > MAXPROC) {
        printf("Max limit of processes exceeded; using maximum allowed");
        n_proc = MAXPROC;
    }
    if (mem_size > MAXMEM) {
        printf("Max limit of processes exceeded; using half of maximum allowed");
        n_proc = MAXMEM/2;
    }
    print_sysinfo();
    int ret;
    int proc_pid[MAXPROC];
    for (int i = 0; i < n_proc; i++) {
        sleep(1);
        ret = fork();
        if (ret == 0) { // child process
            struct pinfo param;
            malloc(mem_size); // this triggers a syscall
            for (int j = 0; j < 10; j++) procinfo((void *)&param); // calls 10 times
            printf("[procinfo %d] ppid: %d, syscalls: %d, page usage: %d\n",
                getpid(), param.ppid, param.syscall_count, param.page_usage);
            while (1);
        }
        else { // parent
            proc_pid[i] = ret;
            continue;
        }
    }
    sleep(1);
    print_sysinfo();
    for (int i = 0; i < n_proc; i++){
        kill(proc_pid[i]);
    }
    exit(0);
}