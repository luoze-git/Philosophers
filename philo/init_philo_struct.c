#include "philo.h"


static int assign_philo_id_readable(t_control_philo *ctl)
{
    t_philo_child *philo;
    int i;

    i = 0;
    philo = ctl->philos;
    
    while(i < ctl->number_philo)
    {
        philo[i].id = i;
        i++;
    }
    return 0;
}

philo_routine();
// todo: look into 1. why the name of left fork and right fork is needed.  2. circular fork is neater
static int spread_forks_to_philos(t_control_philo *ctl)
{
    pthread_mutex_t *forks;
    t_philo_child *philos;
    int i;

    i = 0;
    philos = ctl->philos;
    forks = ctl->forks;
    while(i < ctl->number_philo)
    {
        philos[i].right_fork = forks + i;
        i++;
    }
    
    philos->left_fork = forks + ctl->number_philo - 1;
    i=1;
    while(i < ctl->number_philo)
    {
        philos[i].left_fork = forks + i - 1;
        i++;
    }
}

// to each philo, add in ctl ptr, init last_meal_time and meals_eaten 
static int fill_up_philos(t_control_philo *ctl)
{
    t_philo_child * philos;
    philos = ctl->philos;
    
    int i;
    i = 0;
    while(i < ctl->number_philo)
    {
        philos[i].ctl_ptr = ctl;
        philos->last_meal_time = -1;
        philos->meals_eaten = 0;
        i++;
    }
    return 0;
}

// todo3: clean here if malloc fail
int init_philos_struct(t_control_philo *ctl)
{
    ctl->philos = malloc(ctl->number_philo * sizeof(t_philo_child));
    if (!ctl->philos)
        return 1;
    assign_philo_id_readable(ctl);
    spread_forks_to_philos(ctl);
    fill_up_philos(ctl);
    return 0;
}
