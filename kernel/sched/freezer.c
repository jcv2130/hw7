#include "sched.h"

/*
 * freezer scheduling class.
 */

#ifdef CONFIG_SMP
static int
select_task_rq_freezer(struct task_struct *p, int cpu, int sd_flag, int flags)
{
	int cpu, count, ret, min = -1;
	struct rq *rq;
	struct freezer_rq *freezer;
	for_each_possible_cpu(cpu) {
		rq = cpu_rq(cpu);
		freezer = &rq->freezer;
		count = freezer->count;
		if (count < min || min < 0) {
			min = count;
			ret = cpu;
		}
	}
	return ret;
}
#endif /* CONFIG_SMP */

static struct task_struct *
pick_next_task_freezer(struct rq *rq, struct task_struct *prev)
{
	struct freezer_rq *freezer = &rq->freezer;
	struct list_head *entity = list_first_entry_or_null(&freezer->entities, struct sched_freezer_entity, entity);
	if (!entity)
		return NULL; 
	return container_of(entity, struct task_struct, freezer);
}

static void
dequeue_task_freezer(struct rq *rq, struct task_struct *p, int flags)
{
	struct freezer_rq *freezer = &rq->freezer;
	freezer->count--;
	list_del(p->freezer.entity);	
}

static void enqueue_task(struct rq *rq, struct task_struct *p, int flags) {
	struct freezer_rq *freezer = &rq_freezer;
	freezer->count++;
	list_add_tail(p->freezer.entity, &freezer->entities);
}

static void put_prev_task_freezer(struct rq *rq, struct task_struct *prev)
{
	// access freezer member variable of rq
	// idle_exit_fair(rq);
	// rq_last_tick_reset(rq);
}

static void task_tick_freezer(struct rq *rq, struct task_struct *curr, int queued)
{
}

static void set_curr_task_freezer(struct rq *rq)
{
}

static void switched_to_freezer(struct rq *rq, struct task_struct *p)
{
	// BUG();
}

static void
prio_changed_freezer(struct rq *rq, struct task_struct *p, int oldprio)
{
	// BUG();
}

static unsigned int get_rr_interval_freezer(struct rq *rq, struct task_struct *task)
{
	return 0;
}

static void update_curr_freezer(struct rq *rq)
{
}


struct sched_class freezer_sched_class = {
	/* .next is NULL */
	/* no yield_task for idle tasks */

	.enqueue_task		= enqueue_task_freezer,
	.dequeue_task		= dequeue_task_freezer,

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
