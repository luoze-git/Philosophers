#include "philo.h"

void join_multi_threads(t_monitor *mona, int num)
{
    int i;
    i = 0;
    while (i < num)
    {
        pthread_join(mona->eater[i].thread_id, NULL);
        i++;
    }
}

void destroy_eater_mutex(t_eater *eater, int num)
{
    int i;
    i = 0;
    while (i < num)
    {
        pthread_mutex_destroy(&eater->meal_state);
        i++;
    }
}

void destroy_mutex_array(pthread_mutex_t *mutex, int num)
{
    int i;
    i = 0;
    while (i < num)
    {
        pthread_mutex_destroy(&mutex[i]);
        i++;
    }
}
void free_all_malloc_d(t_monitor *mona)
{
    free(mona->forks);
    free(mona->eater);
}

void destroy_mona_mutex(t_monitor *mona)
{
    destroy_mutex_array(mona->forks, mona->num_eater);
    pthread_mutex_destroy(&mona->finished_eater_mutex);
    pthread_mutex_destroy(&mona->printf_n_stop_mutex);
}


