#include "philo.h"

// update into absolute time
void update_last_eating_time(t_eater *eater)
{
    eater->last_eating_time = get_current_time_in_ms();
}

int simulation_stopped(t_eater *eater)
{
    int stop_flag;
    pthread_mutex_lock(&eater->ptr_mona->stop_flag_mutex);
    stop_flag = eater->ptr_mona->stop_flag;
    pthread_mutex_unlock(&eater->ptr_mona->stop_flag_mutex);  
    if (stop_flag)
    {
        return 1;
    }
    return 0;
}

void think(t_eater *eater)
{
    print_eater_state(eater, "is thinking");
}
void eat(t_eater *eater)
{
    pthread_mutex_lock(eater->left_fork);
    print_eater_state(eater, "has taken a fork.");

    pthread_mutex_lock(eater->right_fork);
    print_eater_state(eater, "has taken a fork.");

    update_last_eating_time(eater);
    print_eater_state(eater, "is eating");
    usleep(eater->ptr_mona->time_to_eat * 1000);

    pthread_mutex_unlock(eater->left_fork);
    pthread_mutex_unlock(eater->right_fork);
}

void sleep_eater(t_eater *eater)
{
    print_eater_state(eater, "is sleeping.");
    usleep(eater->ptr_mona->time_to_sleep  * 1000);
}
/*usleep() take microseconds*/
/*tothink: why putting half to sleep is needed in the beginnning to prevent instant deadlock?*/
void *eater_routine(void *arg)
{
    t_eater *eater;

    eater = (t_eater *)arg;
    if (eater->id % 2 == 0)
        usleep(1000);
    while (!simulation_stopped(eater))
    {
        think(eater);
        eat(eater);
        sleep_eater(eater);
    }
    return (NULL);
}