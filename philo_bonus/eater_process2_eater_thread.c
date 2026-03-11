# include "philo_bonus.h"

void lonely_eater(t_eater *eater)
{
    sem_wait(eater->ptr_mama->sem_forks);
    print_live_state(eater, "has taken a fork");
    sem_wait(eater->ptr_mama->sem_forks);
}

void eat(t_eater *eater)
{
    sem_wait(eater->ptr_mama->sem_waiter);
    sem_wait(eater->ptr_mama->sem_forks);
    print_live_state(eater, "has taken a fork");
    sem_wait(eater->ptr_mama->sem_forks);
    print_live_state(eater, "has taken a fork");

    update_eating_state(eater);
    print_live_state(eater, "is eating");

    usleep(eater->ptr_mama->time_to_eat * 1000);
    sem_post(eater->ptr_mama->sem_waiter);
    sem_post(eater->ptr_mama->sem_forks);
    sem_post(eater->ptr_mama->sem_forks);
}

void update_eating_state(t_eater *eater)
{
    pthread_mutex_lock(&eater->mutex_eater);
    eater->last_eating_time_abs = get_curr_time_absolute_in_ms();
    eater->meals_eaten++;
    pthread_mutex_unlock(&eater->mutex_eater);
}

void sleep_eater(t_eater *eater)
{
    print_live_state(eater, "is sleeping");
    usleep(eater->ptr_mama->time_to_sleep * 1000);
}

/*usleep() take microseconds*/
/*tothink: why putting half to sleep is needed in the beginnning to prevent instant deadlock?*/
void *eater_routine(void *arg)
{
    t_eater *eater;

    eater = (t_eater *)arg;
    if (eater->ptr_mama->num_eater > 1)
    {
        while (!stop_flag_is_not_1(eater))
        {
            eat(eater);
            sleep_eater(eater);
            print_live_state(eater, "is thinking");
        }
    }
    else
        lonely_eater(eater);
    return (NULL);
}
