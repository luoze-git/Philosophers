#include "philo.h"

// update into absolute time
void update_last_eating_time(t_eater *eater)
{
    pthread_mutex_lock(&eater->meal_state);
    eater->last_eating_time = get_current_time_in_ms();
    pthread_mutex_unlock(&eater->meal_state);
}

void think(t_eater *eater)
{
    print_live_state(eater, "is thinking");
}

void lonely_eater(t_eater *eater)
{
    pthread_mutex_lock(eater->left_fork);
    print_live_state(eater, "has taken a fork.");
    while (!stop_simulation_by_reading_stop_flag(eater))
        usleep(eater->ptr_mona->time_to_die * 1000 / 10);
    pthread_mutex_unlock(eater->left_fork);
}

void eat(t_eater *eater)
{
    pthread_mutex_lock(eater->left_fork);
    print_live_state(eater, "has taken a fork.");

    pthread_mutex_lock(eater->right_fork);
    print_live_state(eater, "has taken a fork.");

    update_last_eating_time(eater);
    print_live_state(eater, "is eating");
    usleep(eater->ptr_mona->time_to_eat * 1000);

    pthread_mutex_unlock(eater->left_fork);
    pthread_mutex_unlock(eater->right_fork);
}

void sleep_eater(t_eater *eater)
{
    print_live_state(eater, "is sleeping.");
    usleep(eater->ptr_mona->time_to_sleep * 1000);
}
/*usleep() take microseconds*/
/*tothink: why putting half to sleep is needed in the beginnning to prevent instant deadlock?*/
void *eater_routine(void *arg)
{
    t_eater *eater;

    eater = (t_eater *)arg;
    while (eater->ptr_mona->num_eater == 1 && !stop_simulation_by_reading_stop_flag(eater))
    {
        think(eater);
        pthread_mutex_lock(eater->left_fork);
        print_live_state(eater, "has taken a fork.");
    }
    return NULL;

    if (eater->id % 2 == 0)
        usleep(1000);
    if (eater->ptr_mona->num_eater > 1)
    {
        while (!stop_simulation_by_reading_stop_flag(eater))
        {
            think(eater);
            eat(eater);
            sleep_eater(eater);
        }
    }
    else
    {
        think(eater);
        lonely_eater(eater);
    }
    return (NULL);
}
