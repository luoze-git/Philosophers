# include "philo_bonus.h"

void kill_cruelly_n_assign_exit_code(t_parent *mama, pid_t died_prc , int exit_code)
{
    int i;
    i = 0;
    while (i < mama->num_eater)
    {
        if (mama->eater_pid[i] != died_prc)
            kill(mama->eater_pid[i], SIGKILL);
        i++;
    }
    mama->exit_code = exit_code;
}

void release_sem_printf_on_death(t_parent *mama)
{
    sem_post(mama->sem_printf);
}

void clean_sems(t_parent *mama)
{
    if (mama->exit_code == DEAD)
        release_sem_printf_on_death(mama);
    sem_close(mama->sem_forks);
    sem_close(mama->sem_printf);
    sem_close(mama->sem_waiter);

    sem_unlink(mama->sem_forks);
    sem_unlink(mama->sem_printf);
    sem_unlink(mama->sem_waiter);
}

// only processes for bonus part
void free_malloc_d(t_parent *mama)
{
    free(mama->eater_pid);
}

void join_eater_routine_thread(t_eater *eater)
{
    pthread_join(eater->thread_eater_eater, NULL);
}

void clean(t_parent *mama)
{
    if (mama->exit_code == DEAD)
    {
        release_sem_printf_on_death(mama);
        clean_sems(mama);
        free_malloc_d(mama);
    }
    // todo: on error clean immediately

    if (mama->exit_code == 0)
    {
        clean_sems(mama);
        free_malloc_d(mama);
    }
}