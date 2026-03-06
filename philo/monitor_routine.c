
#include "philo.h"

static void dead_set_stop_flag(t_monitor *mona)
{
    pthread_mutex_lock(&mona->stop_flag_mutex);
    mona->stop_flag = 1;
    pthread_mutex_unlock(&mona->stop_flag_mutex);
}

int thread_is_dead(t_eater eater, int time_to_die)
{
    pthread_mutex_lock(&eater.meal_state);
    if (get_current_absolute_time_in_ms() - eater.last_eating_time_abs > time_to_die)
    {
        pthread_mutex_unlock(&eater.meal_state);
        return 1;
    }
    pthread_mutex_unlock(&eater.meal_state);
    return 0;
}

void *monitor_routine(void *arg)
{
    t_monitor *mona;
    int i;

    i = 0;
    mona = (t_monitor *)arg;

    while (1)
    {
        if (thread_is_dead(mona->eater[i], mona->time_to_die))
        {
            print_death_state(&mona->eater[i], "died.");
            dead_set_stop_flag(mona);
            return NULL;
        }
        i++;
        i = i % mona->num_eater;
        usleep(1000);
    }
    return (NULL);
}
