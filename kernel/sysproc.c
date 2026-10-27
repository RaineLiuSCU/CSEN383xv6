#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64 
sys_hello(void)
{
  int n;
  argint(0, &n);
  print_hello(n);
  return 0;
}

int
sys_sysinfo(void)
{
  int n;
  argint(0, &n);
  if (n == 0) {
    return active_processes();
  } else if (n == 1) {
    return num_syscalls();
  } else if (n == 2) {
    return free_pages();
  } else {
    return -1;
  }
}

int
sys_procinfo(void)
{
  uint64 info_addr;
  struct proc * p = myproc();
  if (p == 0) {
    return -1;
  }
  argaddr(0, &info_addr);

  struct pinfo * info = (struct pinfo *) info_addr;

  int pages = ((p->sz)+PGSIZE-1)/PGSIZE;
  int ppid = p->parent->pid;

  if (copyout(p->pagetable, (uint64) &info->ppid, (char *) &ppid, sizeof(int)) < 0 || copyout(p->pagetable, (uint64) &info->syscall_count, (char *) &p->syscall_count, sizeof(int)) < 0 || copyout(p->pagetable, (uint64) &info->page_usage, (char *) &pages, sizeof(int)) < 0){
    return -1;
  }
  
  return 0;


}

int 
sys_sched_statistics(void)
{
  print_sched_stats();
  return 0;
}

int 
sys_sched_tickets(void)
{
  int n;
  argint(0, &n);
  struct proc * p = myproc();
  set_tickets(n,p);
  return 0;
}

