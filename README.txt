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



Part 2:
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



Part 3:
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



Part 4:
First we built the linux-4.1.18-jcv2130 kernel using the
linux-4.1.18-jcv2130-bfs kernel. Using the time command we got the run
statistics:
real	9m56.685s
user	15m38.720s
sys	0m16.690s

Then we built the linux-4.1.18-jcv2130 kernel using the linux-4.1.18-jcv2130
kernel. Using the time command we got the run statistics:
real	9m45.942s
user	15m16.460s
sys	0m30.410s

Apparently the bfs kernel took slightly longer to compile the kernel, and
used slightly more user CPU time. However the bfs kernel used roughly half
the system CPU time. One thing to consider is that these tests were run as
the only running processes on the VM, we would expect that the bfs kernel
would show more of an advantage when the VM was handling multiple tasks at
once.

To perform an experiment that we thought would highlight the strengths of
the bfs scheduler, we repeated the first two tests with an added task. We
compiled the kernel as before, but with the added task of using firefox to
play an online game. The game, slither.io, requires very frequent user input
with the keyboard, as well as frequent refreshing of the visual display.
First, using the linux-4.1.18-jcv2130-bfs kernel, we compiled the
linux-4.1.18-jcv2130 kernel while playing the online game. Using the time
command we got the run statistics:
real	16m49.674s
user	17m20.140s
sys	0m14.100s

Then, using the linux-4.1.18-jcv2130 kernel, we compiled the
linux-4.1.18-jcv2130 kernel while playing the online game. Using the time
command we got the run statistics:
real	19m15.281s
user	17m0.830s
sys	0m38.400s

As we expected, the bfs kernel performed better than the cfs kernel in this
experiment. It compiled the kernel in 87% of the time the cfs kernel took,
used about the same amount of user CPU time, and used 37% as much system CPU
time. Also, an important difference, during the bfs run, the online game
operated much more smoothly than it did during the cfs run. During the cfs
run the game graphics refreshed poorly, and there was more lag on user
inputs.



Part 5:

1. With a larger HZ kernel timers execute with a finer resolution and
increased accuracy. This results in system calls with timeout values to
execute more precisely and measurements to be recorded more precisely. Process
preemption also occurs more accurately.

The major disadvantage to higher HZ values is that there is higher overhead
because the processor must spend more time executing the interrupt handler.
This overhead results in less processor time for other work and higher power
consumption.

2. The HZ is currently configured at 100, as seen in the config file.

3. jiffies is the number of ticks that have occurred since the system booted.
jiffies is normally stored in a 32-bit variable. jiffies_64 is the 64-bit
version of jiffies. jiffies is set equal to jiffies_64 and any program that
accesses jiffies is really accessing the lower 32-bits of jiffies_64. If all
64 bits are needed jiffies_64 can be accessed directly.

4. The value of jiffies when I checked it was 282718. The system uptime is 
thus 282718 / 100 seconds, which is equal to 2827.18 seconds, which is
approximately 47 minutes. The uptime command confirms this number.

5. The value of jiffies when I checked it the second time wa 322557. The value
of jiffies_64 when I checked it was 4295289853. I expected them to be the same
because the system has not been on long enough to overflow jiffies_64. They
are clearly not the same. The difference between the two values is
approximately 4294967296, or 2^32.They are different because they differ by
2^32, or the amount of extra bits that jiffies_64 has in comparison to 
jiffies.



Part 6: 581908c5dba2b5238a24839101d884b227c7b0c1



Part 7: 
