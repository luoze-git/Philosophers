#include "philo_bonus.h"

int init_mama(t_parent *mama)
{
    if (setup_semaphore(mama))
        return 1;
    mama->finished_eater = 0;
    mama->start_time_abs = get_curr_time_absolute_in_ms();
    // here no need to clean anything
    mama->eater_pid = malloc(mama->num_eater * sizeof(*(mama->eater_pid)));
    if (mama->eater_pid == NULL)
        return 1;
    return 0;
}
int setup_semaphore(t_parent *mama)
{
    sem_unlink("/fork");
    sem_unlink("/printf");
    sem_unlink("/waiter");

    mama->sem_forks = sem_open("/fork", O_CREAT, 0644,
                               mama->num_eater);
    if (mama->sem_forks == SEM_FAILED)
        return 1;
    mama->sem_printf = sem_open("/printf", O_CREAT, 0644, 1);
    if (mama->sem_printf == SEM_FAILED)
        return 1;
    mama->sem_waiter = sem_open("/waiter", O_CREAT, 0644, mama->num_eater - 1);
    if (mama->sem_waiter == SEM_FAILED)
        return 1;
    return 0;
}
