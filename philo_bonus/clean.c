# include "philo_bonus.h"

static void release_sem_printf_on_death(t_parent *mama);

    void kill_cruelly_n_assign_exit_code(t_parent *mama, pid_t died_prc, int exit_code)
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

static void release_sem_printf_on_death(t_parent *mama)
{
    if (mama->exit_code == DEAD)
        sem_post(mama->sem_printf);
}
