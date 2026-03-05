
#include "philo.h"


static void dead_set_stop_flag(t_monitor * mona)
{
    pthread_mutex_lock(&mona->stop_flag_mutex);
    mona->stop_flag = 1;
    pthread_mutex_unlock(&mona->stop_flag_mutex);
}

void *monitor_routine(void *arg)
{
    t_monitor *mona;
    int i;
    long time_to_die;
    
    i = 0;
    mona = (t_monitor *)arg;
    time_to_die = mona->time_to_die;

    while(1)
    {
        if (get_current_time_in_ms() - mona->eater[i].last_eating_time > time_to_die)
        {
            print_eater_state(&mona->eater[i], "died.");
            dead_set_stop_flag(mona);
            return;
        }
        i++;
        i = i % mona->num_eater;
        usleep(1000);
    }
    return (NULL);
}
