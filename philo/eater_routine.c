#include "philo.h"

void update_last_eating_time(t_eater *eater)
{
    int mse;
    mse = eater->ptr_mona->must_eat_count;
    pthread_mutex_lock(&eater->meal_state);
    eater->last_eating_time_abs = get_current_absolute_time_in_ms();
    pthread_mutex_unlock(&eater->meal_state);
    if (mse != -1)
    {
        eater->meals_eaten ++;
        if(eater->meals_eaten == mse )
        {
            pthread_mutex_lock(&eater->ptr_mona->finished_eater_mutex);
            eater->ptr_mona->finished_eater++;
            pthread_mutex_unlock(&eater->ptr_mona->finished_eater_mutex);
        }
    }
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



// todo: You should not die of a block/deadlock.
// You still can die of a common starve.
// But you can also run theoretically forever.
// that death occurs when the must_eat_count reaches.
// Now the questions narrows to: forks aquirement strategy to prevent deadlock.
// After that, if death occur, make that thread return provided they did not.
void eat(t_eater *eater)
{
    if (eater->id % 2 == 0)
    {
        pthread_mutex_lock(eater->left_fork);
        print_live_state(eater, "has taken a fork.");
        pthread_mutex_lock(eater->right_fork);
        print_live_state(eater, "has taken a fork.");
    }
    else
    {
        pthread_mutex_lock(eater->right_fork);
        print_live_state(eater, "has taken a fork.");
        pthread_mutex_lock(eater->left_fork);
        print_live_state(eater, "has taken a fork.");
    }
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

    if (eater->id % 2 == 0)
        usleep(1000);
    if (eater->ptr_mona->num_eater > 1)
    {
        while (!stop_simulation_by_reading_stop_flag(eater))
        {
            eat(eater);
            sleep_eater(eater);
            think(eater);
        }
    }
    else
        lonely_eater(eater);
    return (NULL);
}
