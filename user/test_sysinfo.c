#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define MAX_PROC 10
struct pinfo {
int ppid;
int syscall_count;
int page_usage;
};
void print_sysinfo(void)
{
    int n_active_proc, n_syscalls, n_free_pages;
    n_active_proc = sysinfo(0);
    n_syscalls = sysinfo(1);
    n_free_pages = sysinfo(2);
    printf("[sysinfo] active proc: %d, syscalls: %d, free pages: %d\n",
        n_active_proc, n_syscalls, n_free_pages);
}
int main(int argc, char * argv[]){
    print_sysinfo();
    print_sysinfo();
    printf("above: printing all system info options, then doing it again\n");
    int a = sysinfo(1);
    int b = sysinfo(1);
    printf("calling two sysinfos next to each other; syscall count for each is %d, %d\n", a, b);
}