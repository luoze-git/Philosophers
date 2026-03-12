#include "philo_bonus.h"


static void join_eater_routine_thread(t_eater *eater)
{
    pthread_join(eater->thread_eater_eater, NULL);
}
void destroy_local_mutex(t_eater *eater)
{
    pthread_mutex_destroy(&eater->mutex_eater);
}

void clean_children_process(t_eater *eater)
{
    join_eater_routine_thread(eater);
    destroy_local_mutex(eater);
}
