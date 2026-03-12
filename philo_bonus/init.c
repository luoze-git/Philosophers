#include "philo_bonus.h"

static int setup_semaphore(t_parent *mama);
static int setup_semaphore_helper_safe_open(t_parent *mama);


int init_mama(t_parent *mama)
{
    if (setup_semaphore(mama))
        return 1;
    mama->exit_code = UNSET ;
    mama->start_time_abs = get_curr_time_absolute_in_ms();
    mama->eater_pid = malloc(mama->num_eater * sizeof(*(mama->eater_pid)));
    if (mama->eater_pid == NULL)
    {
        clean_sems_guarded(mama);
        return 1;
    }
    return 0;
}

static int setup_semaphore(t_parent *mama)
{
    mama->sem_forks = SEM_FAILED;
    mama->sem_printf = SEM_FAILED;
    mama->sem_waiter = SEM_FAILED;
    sem_unlink("/fork");
    sem_unlink("/printf");
    sem_unlink("/waiter");

    return (setup_semaphore_helper_safe_open(mama));
}

static int setup_semaphore_helper_safe_open(t_parent *mama)
{
    mama->sem_forks = sem_open("/fork", O_CREAT, 0644, mama->num_eater);
    if (mama->sem_forks == SEM_FAILED)
    {
        clean_sems_guarded(mama);
        return 1;
    }
    mama->sem_printf = sem_open("/printf", O_CREAT, 0644, 1);
    if (mama->sem_printf == SEM_FAILED)
    {
        clean_sems_guarded(mama);
        return 1;
    }
    mama->sem_waiter = sem_open("/waiter", O_CREAT, 0644, mama->num_eater - 1);
    if (mama->sem_waiter == SEM_FAILED)
    {
        clean_sems_guarded(mama);
        return 1;
    }
    return 0;
}
