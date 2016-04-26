HW 7
jcv2130
README.txt


Part 1:
To create the task 1 scenario first we wrote the program myprogram.c, which
forks 10 processes, then returns. Each of the 10 child processes enters an
infinite for-loop that shuffles around the values of three variables. Then,
to ensure that these 10 processes had an entire processor to themselves, we
restarted the VM and during boot added the command isolcpus=0 to the kernel
command line. This restricted any other processes from running on CPU 0. 
Then using the command taskset 0x1 ./a.out, we started the 10 processes on
the reserved CPU 0. Finally using the application top, we used renice to set
the nice values of 5 of the tasks to 3, and the nice values of the other 5
tasks to 7. This resulted in the situation specified by task 1. The output
from top can be seen below.

top - 15:27:06 up 20 min,  1 user,  load average: 10.02, 9.38, 6.02
Tasks: 10 total, 10 running, 0 sleeping, 0 stopped, 0 zombie
%Cpu0  : 100.0/0.0   100[|||||||||||||||||||||||||||||||||||||||||||||||||||||]
%Cpu1  :   0.7/0.0     1[                                                     ]
GiB Mem :  6.6/1.972    [                                                     ]
GiB Swap:  0.0/0.000    [                                                     ]

  PID USER      PR  NI    VIRT    RES  %CPU %MEM     TIME+ S COMMAND
  516 voss      27   7    2.0m   0.0m   6.0  0.0   0:48.37 R a.out
  517 voss      27   7    2.0m   0.0m   6.0  0.0   0:46.68 R a.out
  518 voss      27   7    2.0m   0.0m   6.0  0.0   0:45.66 R a.out
  519 voss      27   7    2.0m   0.0m   6.0  0.0   0:44.89 R a.out
  520 voss      27   7    2.0m   0.0m   6.0  0.0   0:43.84 R a.out
  521 voss      23   3    2.0m   0.0m  14.7  0.0   1:01.46 R a.out
  522 voss      23   3    2.0m   0.0m  13.3  0.0   1:00.50 R a.out
  523 voss      23   3    2.0m   0.0m  14.0  0.0   1:00.10 R a.out
  524 voss      23   3    2.0m   0.0m  14.0  0.0   0:59.61 R a.out
  525 voss      23   3    2.0m   0.0m  14.0  0.0   0:59.17 R a.out


To create the task 2 scenario we edited myprogram.c to myprogram2.c, which
forks the 10 processes as before, but then instead of returning, the parent
process also enters an infinite for-loop.

NEEDS FURTHER EXPLANATION!!!!!!!

Part 2
Output from diff  ../linux-4.1.18/.config  .config-jcv2130-bfs:

3c3
< # Linux/x86 4.1.18 Kernel Configuration
---
> # Linux/x86 4.1.18-ck2 Kernel Configuration
48a49
> CONFIG_SCHED_BFS=y
52c53
< CONFIG_LOCALVERSION="-jcv2130"
---
> CONFIG_LOCALVERSION="-jcv2130-bfs"
112,113c113
< CONFIG_TICK_CPU_ACCOUNTING=y
< # CONFIG_IRQ_TIME_ACCOUNTING is not set
---
> CONFIG_IRQ_TIME_ACCOUNTING=y
134d133
< # CONFIG_RCU_NOCB_CPU is not set
148d146
< CONFIG_CGROUP_CPUACCT=y
156,159d153
< CONFIG_CGROUP_SCHED=y
< CONFIG_FAIR_GROUP_SCHED=y
< CONFIG_CFS_BANDWIDTH=y
< # CONFIG_RT_GROUP_SCHED is not set
169d162
< CONFIG_SCHED_AUTOGROUP=y
221d213
< # CONFIG_SLAB is not set
423a416
> CONFIG_SMT_NICE=y
455a449,453
> CONFIG_VMSPLIT_3G=y
> # CONFIG_VMSPLIT_3G_OPT is not set
> # CONFIG_VMSPLIT_2G is not set
> # CONFIG_VMSPLIT_2G_OPT is not set
> # CONFIG_VMSPLIT_1G is not set
518c516
< # CONFIG_HZ_250 is not set
---
> # CONFIG_HZ_250_NODEFAULT is not set
532,533d529
< # CONFIG_BOOTPARAM_HOTPLUG_CPU0 is not set
< # CONFIG_DEBUG_HOTPLUG_CPU0 is not set
3686d3681
< # CONFIG_RCU_TORTURE_TEST is not set



