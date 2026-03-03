
#include "philo.h"

/*
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
*/

static void load_ctl_from_args(t_control_philo0 *ctl, int argc, char **argv)
{
    ctl->number_philo = ft_atoi_only_transform_legit_num(argv[1]);
    ctl->time_to_die = ft_atoi_only_transform_legit_num(argv[2]);
    ctl->time_to_eat = ft_atoi_only_transform_legit_num(argv[3]);
    ctl->time_to_sleep = ft_atoi_only_transform_legit_num(argv[4]);
    if (argc == 6)
        ctl->must_eat_count = ft_atoi_only_transform_legit_num(argv[5]);
}



// todo3: destruct all mutex before free mem and after unlocked and not in use.
static int init_mutex(t_control_philo0 *ctl)
{
    int i;
    i =0 ;
    while(i < ctl->number_philo)
    {
        if (pthread_mutex_init(ctl->forks + i, NULL) != 0)
            return 1;
        i++;
    }
    if (pthread_mutex_init(&ctl->printf_mutex, NULL) != 0)
        return 1;
    if (pthread_mutex_init(&ctl->stop_flag_mutex, NULL) != 0)
        return 1;
    return 0;
}

int init_ctl(t_control_philo0 *ctl)
{
    ctl->start_time = get_current_time_in_ms();
    if ( ctl->start_time == -1)
        return 1;
    ctl->stop_flag = 0;
    // first malloc fail and no need to clean;
    ctl->forks = malloc(ctl->number_philo * sizeof(pthread_mutex_t));
    if (!(ctl->forks))
    {
        printf("malloc failed at mutex");
        return 1;
    }
    // init mutex 
    if (init_mutex(ctl))
        return 1;
    return 0;
}