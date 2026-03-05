#include "philo.h"

int detect_liveness(t_monitor *mona)
{
}

int update_eating_states(t_monitor *mona)
{
}

int report_eater_state(t_monitor *mona, char *msg)
{
}

void *eater_routine(void *arg)
{
    t_eater *philo;

    philo = (t_eater *)arg;
    while (mona->stop_flag != 1)
    {
        think(philo);
        eat(philo);
        sleep_philo(philo);
    }
    return (NULL);
}

int monitor_routine(t_monitor * mona)
{

}

/*int pthread_create(
    pthread_t *thread,
    const pthread_attr_t *attr,
    void *(*start_routine)(void *),
    void *arg
);
*/

void create_threads(t_monitor *mona)
{
    int i;
    t_eater *eater;
    i = 0;
    eater = mona->eater;
    while (i < mona->num_eater)
    {
        pthread_create(&eater[i].thread_id, NULL, eater_routine, &eater[i]);
        i++;
    }
    pthread_create(&mona->monitor_thread, NULL, monitor_routine, mona);
}

/*control philo , philosss;  main born and recevie and cleanup , monitor death , philo eaters*/
void start_simulation(t_monitor *mona);
{
    create_threads(mona);
}

// /// args could be 5 - 6; must check the type
int main(int argc, char **argv)
{
    t_monitor mona;
    if (parse_args(&mona, argc, argv))
        return (1);
    if (prep_mona_n_eaters_pre_threads(&mona))
        return (1);
    start_simulation(&mona);
    wait_to_cleanup_plates(&mona);
    return (0);
}
