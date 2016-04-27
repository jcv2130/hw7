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
from top can be seen below:

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
process also enters an infinite for-loop. By loading the kernel and running
myprogram2.c as we did in task 1, we achieve 11 processes running on CPU 0,
at this point sharing it equally. Then using the command sudo chrt -f -p 99
<pid> we set the scheduling policy of one of the processes to SCHED_FIFO,
giving it real time priority. (Using sudo is necessary to change process to
real time priority). The real time process then preempts the other processes
and takes around 97% of the CPU. The output from top can be seen below:

top - 22:08:55 up 41 min,  1 user,  load average: 12.10, 6.06, 3.06
Tasks:  11 total,  11 running,   0 sleeping,   0 stopped,   0 zombie
%Cpu0  : 100.0/0.0   100[|||||||||||||||||||||||||||||||||||||||||||||||||||||]
%Cpu1  :   1.6/0.5     2[                                                     ]
GiB Mem :  6.2/1.972    [                                                     ]
GiB Swap:  0.0/0.000    [                                                     ]

  PID USER      PR  NI    VIRT    RES  %CPU %MEM     TIME+ S COMMAND
  846 voss      rt   0    2.0m   0.6m  97.3  0.0   2:12.76 R a.out
  847 voss      20   0    2.0m   0.0m   0.7  0.0   0:03.32 R  `- a.out
  848 voss      20   0    2.0m   0.0m   0.7  0.0   0:03.32 R  `- a.out
  849 voss      20   0    2.0m   0.0m   0.0  0.0   0:03.32 R  `- a.out
  850 voss      20   0    2.0m   0.0m   0.0  0.0   0:03.32 R  `- a.out
  851 voss      20   0    2.0m   0.0m   0.7  0.0   0:03.32 R  `- a.out
  852 voss      20   0    2.0m   0.0m   0.7  0.0   0:03.32 R  `- a.out
  853 voss      20   0    2.0m   0.0m   0.7  0.0   0:03.32 R  `- a.out
  854 voss      20   0    2.0m   0.0m   0.0  0.0   0:03.32 R  `- a.out
  855 voss      20   0    2.0m   0.0m   0.0  0.0   0:03.32 R  `- a.out
  856 voss      20   0    2.0m   0.0m   0.0  0.0   0:03.32 R  `- a.out



Part 2
Output from diff  ../linux-4.1.18/.config  .config-jcv2130-bfs:

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
532,533d524
< # CONFIG_BOOTPARAM_HOTPLUG_CPU0 is not set
< # CONFIG_DEBUG_HOTPLUG_CPU0 is not set
3686d3676
< # CONFIG_RCU_TORTURE_TEST is not set

We have successfully patched and booted into kernel 4.1.18-jcv2130-bfs



Part 3
The result of performing the steps of task 1 in the bfs kernel are
essentially the same as they were in Part 1, however there were two main
differences. First, before using renice, we noticed one difference while
examining the output from top. In Part 1 all 10 of the generated processes
had a priority value of 20. In the bfs kernel, the default priority seemed
to be 1 and the scheduler appeared to rotate higher priority values around
the 10 processes. Despite the rotating higher priority values on some of the
processes, all 10 processes seem to share the CPU evenly.Second, when trying
to use renice to divide the CPU into 5 processes taking 70% and 5 processes
taking 30%, the previous nice values of 7 and 3 did not give the processes
with a nice value of 7 enough of the CPU. It ended up taking a greater
difference in nice values with the bfs scheduler to achieve the same
scenario as in Part 1. We found that 5 processes running with nice value 12
or 13 and 5 processes running with nice value 0 gave up the 30% 70%
allocation of the CPU.

Performing the steps of task 2, first we tried the command chrt -f -p 99
<pid> without using sudo. We found that at first the designated process is
given a priority value of 0 and uses 100% of the CPU, but after a few
seconds, the scheduler begins to rotate the priority values as before. The
process designated as an unprivileged real time task still takes more of the
CPU than the other processes, using anywhere between 24% and 65% of the
CPU. When we ran the chrt command using sudo we found that the designated
process is given a priority value of rt and uses 100% of the CPU
indefinitely, with none of the other processes getting any percent of the
CPU.



Part 4


