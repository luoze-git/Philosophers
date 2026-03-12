#include "philo_bonus.h"

static int init_eater(t_eater *eater , t_parent *mama);
static int create_eater_routine_thread( t_eater *eater);

// this thread will remain as the monitor
int eater_transform(t_parent *mama , int id_passed)
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


