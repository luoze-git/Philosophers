#include "philo.h"

// todo: look into 1. why the name of left fork and right fork is needed - to simplify the problem.  2. circular fork is neater

static int init_eaters(t_monitor *mona)
{
    t_eater *eater;
    int i;

    i = 0;
    eater = mona->eater;
    while (i < mona->num_eater)
    {
        eater[i].id = i;
        eater[i].ptr_mona = mona;
        eater[i].right_fork = mona->forks + i;
        eater[i].left_fork = mona->forks + ((i + 1) % mona->num_eater);
        eater->last_meal_time = -1;
        eater->meals_eaten = 0;
        eater->ptr_mona = mona;
        i++;
    }
    return 0;
}

int init_mona(t_monitor *mona)
{
    int i;
    i = 0;
    while (i < mona->num_eater)
    {
        if (pthread_mutex_init(mona->forks + i, NULL) != 0)
            return 1;
        i++;
    }
    if (init_for_printf_n_stopschild(mona))
        return 1;
    mona->stop_flag = 0;
    mona->start_time = get_current_time_in_ms();
    if (mona->start_time == -1)
        return 1;
    return 0;
}

// todo3: destruct all mutex before free mem and after unlocked and not in use.
int init_for_printf_n_stopschild(t_monitor *mona)
{
    if (pthread_mutex_init(&mona->printf_mutex, NULL) != 0)
        return 1;
    if (pthread_mutex_init(&mona->stop_flag_mutex, NULL) != 0)
        return 1;
    return 0;
}

int malloc_d_eaters_forks(t_monitor *mona)
{
    mona->forks = malloc(mona->num_eater * sizeof(pthread_mutex_t));
    if (!(mona->forks))
    {
        printf("malloc failed at mutex");
        return 1;
    }

    mona->eater = malloc(mona->num_eater * sizeof(t_eater));
    if (!mona->eater)
        return 1;
}


// initiate up the monitor struct along with the main needed identity information.
//
// todo3: clean here if malloc fail
int prep_mona_n_eaters_pre_threads(t_monitor *mona)
{
    if (malloc_d_eaters_n_forks(mona))
        return 1;
    if (init_mona(mona))
        return 1;
    if (init_eaters(mona))
        return 1;
    return 0;
}


