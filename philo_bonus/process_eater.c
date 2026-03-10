#include "philo_bonus.h"

void think(t_eater *eater)
{
    print_live_state(eater, "is thinking");
}

void lonely_eater(t_eater *eater)
{
    sem_wait(eater->ptr_mama->sem_waiter);
}

void eat(t_eater *eater)
{
    sem_wait(eater->ptr_mama->sem_waiter);
    sem_wait(eater->ptr_mama->sem_forks);
    print_live_state(eater, "has taken a fork");
    sem_wait(eater->ptr_mama->sem_forks);
    print_live_state(eater, "has taken a fork");
    
    update_last_eating_time(eater);
    print_live_state(eater, "is eating");

    usleep(eater->ptr_mama->time_to_eat * 1000);
    sem_post(eater->ptr_mama->sem_waiter);
    sem_post(eater->ptr_mama->sem_forks);
    sem_post(eater->ptr_mama->sem_forks);
}
void update_last_eating_time(t_eater *eater)
{
    int mse;

    mse = eater->ptr_mama->must_eat_count;
    pthread_mutex_lock(&eater->mutex_eater);
    eater->last_eating_time_abs = get_curr_time_absolute_in_ms();
    pthread_mutex_unlock(&eater->mutex_eater);
    if (mse != -1)
    {
        eater->meals_eaten++;
        if (eater->meals_eaten == mse)
        {
            //todo: clean 
            exit(EATER_FULL);
        }
    }
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

int init_eater(t_eater *eater)
{
    
    eater->stop_flag = 0 ;
    if (pthread_mutex_init(&eater->mutex_eater, NULL))
        return 1;
    
    return 0;
}

eater_transform(t_parent *mama , int id_passed)
{
    t_eater eater;

    eater.id = id_passed;
    // this thread will remain as the monitor
    if (init_eater(&eater))
        return ;
    create_eating_thread(mama , eater);
    if (start_monitoring(mama))
        exit (DEAD);
    else        
        exit (must_eat_done);
}
//todo: git commit current change: in batch 