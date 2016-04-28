#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

#define SCHED_FREEZER 7

void main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usage: ./set-freezer <pid>\n");
		exit(1);
	}

	pid_t pid = atoi(argv[1]);

	int prevPolicy;
	if ((prevPolicy = sched_getscheduler(pid)) < 0) {
		perror("sched_getscheduler() failed");
		exit(1);
	}

	struct sched_param param = { 0 };

	int newPolicy;
	if (sched_setscheduler(pid, SCHED_FREEZER, &param) != 0) {
	    //|| (newPolicy = sched_getscheduler(pid)) != SCHED_FREEZER) {
		perror("sched_setscheduler() failed");
		exit(1);
	}

	fprintf(stdout, "[%d] sched policy changed: %d --> %d\n", pid, prevPolicy, newPolicy);
	
}
