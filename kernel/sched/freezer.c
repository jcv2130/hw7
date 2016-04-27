#include "sched.h"

/*
 * freezer scheduling class.
 */

#ifdef CONFIG_SMP
static int
select_task_rq_freezer(struct task_struct *p, int cpu, int sd_flag, int flags)
{
	return task_cpu(p); /* IDLE tasks as never migrated */
}
#endif /* CONFIG_SMP */

/*
 * Idle tasks are unconditionally rescheduled:
 */
static void check_preempt_curr_freezer(struct freezer_rq *rq, struct task_struct *p, int flags)
{
	resched_curr(rq);
}

static struct task_struct *
pick_next_task_freezer(struct freezer_rq *rq, struct task_struct *prev)
{
	put_prev_task(rq, prev);

	schedstat_inc(rq, sched_goidle);
	return rq->idle;
}

/*
 * It is not legal to sleep in the idle task - print a warning
 * message if some code attempts to do it:
 */
static void
dequeue_task_freezer(struct freezer_rq *rq, struct task_struct *p, int flags)
{
	raw_spin_unlock_irq(&rq->lock);
	printk(KERN_ERR "bad: scheduling from the idle thread!\n");
	dump_stack();
	raw_spin_lock_irq(&rq->lock);
}

static void put_prev_task_freezer(struct freezer_rq *rq, struct task_struct *prev)
{
	idle_exit_fair(rq);
	rq_last_tick_reset(rq);
}

static void task_tick_freezer(struct freezer_rq *rq, struct task_struct *curr, int queued)
{
}

static void set_curr_task_freezer(struct freezer_rq *rq)
{
}

static void switched_to_freezer(struct freezer_rq *rq, struct task_struct *p)
{
	BUG();
}

static void
prio_changed_idle(struct freezer_rq *rq, struct task_struct *p, int oldprio)
{
	BUG();
}

static unsigned int get_rr_interval_freezer(struct freezer_rq *rq, struct task_struct *task)
{
	return 0;
}

static void update_curr_idle(struct freezer_rq *rq)
{
}


struct sched_class freezer_sched_class = {
	/* .next is NULL */
	/* no enqueue/yield_task for idle tasks */

	/* dequeue is not valid, we print a debug message there: */
	.dequeue_task		= dequeue_task_freezer,

	.check_preempt_curr	= check_preempt_curr_freezer,

	.pick_next_task		= pick_next_task_freezer,
	.put_prev_task		= put_prev_task_freezer,

#ifdef CONFIG_SMP
	.select_task_rq		= select_task_rq_freezer,
#endif

	.set_curr_task          = set_curr_task_freezer,
	.task_tick		= task_tick_freezer,

	.get_rr_interval	= get_rr_interval_freezer,

	.prio_changed		= prio_changed_freezer,
	.switched_to		= switched_to_freezer,
	.update_curr		= update_curr_freezer,
};
