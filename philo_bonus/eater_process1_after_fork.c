#include "philo_bonus.h"

int create_eater_routine_thread( t_eater *eater)
{
    if (pthread_create(&eater->thread_eater_eater, NULL, eater_routine, eater) != 0)
        return 1;
    return 0;
}

int init_eater(t_eater *eater , t_parent *mama)
{
    eater->ptr_mama = mama;
    eater->last_eating_time_abs = eater->ptr_mama->start_time_abs;
    eater->meals_eaten = 0;
    eater->stop_flag = 0 ;
    if (pthread_mutex_init(&eater->mutex_eater, NULL))
        return 1;
    return 0;
}

int start_monitoring(t_eater *eater)
{
    int i;

    i = 0;
    while (1)
    {
        if (eater_is_dead(eater, eater->ptr_mama->time_to_die))
        {
            print_death_n_set_stop_n_never_post_sem(eater, "died");
            return (DEAD);
        }
        if (eater->ptr_mama->must_eat_count != -1 && eater_is_full(eater))
        {
            set_stop_flag_with_mutex(eater);
            return (EATER_FULL);
        }
        usleep(1000);
    }
}

static void clean_children_process(t_eater *eater)
{
    join_eater_routine_thread(eater);
    pthread_mutex_destroy(&eater->mutex_eater);
}

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
        pthread_mutex_destroy(&eater.mutex_eater);
        exit(ERR);
    }    
    monitor_code = start_monitoring(&eater);
    clean_children_process(&eater);
    exit(monitor_code);
}
