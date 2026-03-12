#include "philo_bonus.h"

static int init_eater(t_eater *eater , t_parent *mama);
static int create_eater_routine_thread( t_eater *eater);
static int eater_transform(t_parent *mama , int id_passed);
static int clean_spawn_failure(t_parent *mama, int spawned_count);

int spawn_children_processes(t_parent *mama)
{
    int i;

    i = 0;
    while (i < mama->num_eater)
    {
        mama->eater_pid[i] = fork();
        if (mama->eater_pid[i] == -1)
            return (clean_spawn_failure(mama, i));
        if (mama->eater_pid[i] == 0)
            eater_transform(mama, i + 1);
        i++;
    }
    return (0);
}

// this thread will remain as the monitor
static int eater_transform(t_parent *mama , int id_passed)
{
    t_eater eater;
    int monitor_code;
    
    eater.id = id_passed;
    if (init_eater(&eater, mama))
        exit(ERR);
    if (create_eater_routine_thread(&eater))
    {
        destroy_local_mutex(&eater);
        exit(ERR);
    }    
    monitor_code = start_monitoring(&eater);
    clean_children_process(&eater);
    exit(monitor_code);
}

static int clean_spawn_failure(t_parent *mama, int spawned_count)
{
    int i;
    int status;

    i = 0;
    while (i < spawned_count)
    {
        if (mama->eater_pid[i] > 0)
            kill(mama->eater_pid[i], SIGKILL);
        i++;
    }
    i = 0;
    while (i < spawned_count)
    {
        waitpid(mama->eater_pid[i], &status, 0);
        i++;
    }
    mama->exit_code = ERR;
    clean(mama);
    return (1);
}

static int create_eater_routine_thread(t_eater *eater)
{
    if (pthread_create(&eater->thread_eater_eater, NULL, eater_routine, eater) != 0)
        return 1;
    return 0;
}

static int init_eater(t_eater *eater, t_parent *mama)
{
    eater->ptr_mama = mama;
    eater->last_eating_time_abs = eater->ptr_mama->start_time_abs;
    eater->meals_eaten = 0;
    eater->stop_flag = 0;
    if (pthread_mutex_init(&eater->mutex_eater, NULL))
        return 1;
    return 0;
}


