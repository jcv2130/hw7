#ifndef _SCHED_FREEZER_H
#define _SCHED_FREEZER_H

/*
 * default timeslice is 100 msecs (used only for SCHED_FREEZER tasks).
 * Timeslices get refilled after they expire.
 */
#define FREEZER_TIMESLICE	(100 * HZ / 1000)

#endif /* _SCHED_FREEZER_H */
