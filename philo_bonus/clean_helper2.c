# include "philo_bonus.h"

// only processes for bonus part
static void free_malloc_d(t_parent *mama)
{
    free(mama->eater_pid);
}

static void release_sem_printf_on_death(t_parent *mama)
{
    if (mama->exit_code == DEAD)
        sem_post(mama->sem_printf);
}

void clean_sems_guarded(t_parent *mama)
{
    if (mama->sem_forks != SEM_FAILED)
        sem_close(mama->sem_forks);
    if (mama->sem_printf != SEM_FAILED)
        sem_close(mama->sem_printf);
    if (mama->sem_waiter != SEM_FAILED)
        sem_close(mama->sem_waiter);
    sem_unlink("/fork");
    sem_unlink("/printf");
    sem_unlink("/waiter");
}

void clean(t_parent *mama)
{
    if (mama->exit_code == DEAD)
    {
        release_sem_printf_on_death(mama);
        clean_sems_guarded(mama);
        free_malloc_d(mama);
        return ;
    }
    if (mama->exit_code == UNSET || mama->exit_code == ERR
        || mama->exit_code == EATER_FULL)
    {
        clean_sems_guarded(mama);
        free_malloc_d(mama);
    }
}





