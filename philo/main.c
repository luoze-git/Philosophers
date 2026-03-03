#include "philo.h"

int check_chars_are_numeric_and_positive(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    while (i < argc)
    {
        j = 0;
        while (argv[i][j])
        {
            if ((argv[i][j] < '0' || argv[i][j] > '9') && argv[i][j] != '+')
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int	ft_atoi_only_transform_legit_num(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;

	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

// int int int int int check int types. all args is specified to be int.
int check_numeric_args_overflow(int argc, char** argv)
{
    long result;
    int i;
    int j;
    i = 1;
    while (i < argc)
    {
        result = ft_atoi_only_transform_legit_num(argv[i]); 
        if (result > INT_MAX)
            return (1);
        i++;
    }
    return 0;
}


/*
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
*/
// no need to clean before exit
int check_args_legitimacy(int argc, char **argv)
{
    if (argc != 5 && argc != 6)
    {
        printf("invalid arg numbers");
        return (1);
    }

    // Every argument is strictly numeric
    // go through all of the chars to match the expected style
    if (check_chars_are_numeric_and_positive(argc, argv))
    {
        printf("invalid arg type: should be number");
        return (1);
    }
    // No overflow
    if (check_numeric_args_overflow(argc, argv))
    {
        printf("integer overflows");
        return(1);
    }
    // number_of_philosophers >= 1
    if (argv[1] < 1)
    {
        printf("Number of philosophers should be at least 1.");
        return (1);
    }
    return (0);
}
/*
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
*/

void load_ctl_from_args(t_control_philo0 *ctl, int argc, char **argv)
{
    ctl->number_philo = ft_atoi_only_transform_legit_num(argv[1]);
    ctl->time_to_die = ft_atoi_only_transform_legit_num(argv[2]);
    ctl->time_to_eat = ft_atoi_only_transform_legit_num(argv[3]);
    ctl->time_to_sleep = ft_atoi_only_transform_legit_num(argv[4]);
    if (argc == 6)
        ctl->must_eat_count = ft_atoi_only_transform_legit_num(argv[5]);
}

// get current time and transform it to milliseconds. return -1 on error
long get_current_time_in_ms(void)
{
    long now;
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1)
        return -1;
    now = 1000 * tv.tv_sec + tv.tv_usec/1000;
    return now;
}

// todo3: destruct all mutex before free mem and after unlocked and not in use.
int init_mutex(t_control_philo0 *ctl)
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

int parse_args(t_control_philo0 *ctl, int argc, char **argv)
{
    if (check_args_legitimacy(argc, argv))
    {
        printf("this is not acceptible for me for a reason stated above.");
        return 1;
    }
    load_ctl_from_args(ctl, argc, argv);
    if (init_ctl(ctl))
        return 1;
    return (0);
}

/// args could be 5 - 6; must check the type
int main(int argc, char **argv)
{
    t_control_philo0 ctl;
    if (parse_args(&ctl, argc, argv))
        return (1);
    if (init_simulation(&ctl))
        return (1);

    start_simulation(&ctl);

    cleanup(&ctl);
    return (0);
}
