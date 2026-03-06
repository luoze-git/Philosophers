#include "philo.h"

// get current time and transform it to milliseconds. return -1 on error
long get_current_absolute_time_in_ms(void)
{
    long now;
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1)
        return -1;
    now = 1000 * tv.tv_sec + tv.tv_usec / 1000;
    return now;
}

long ft_atol_assume_legit_input(char *str)
{
    int i;
    long result;

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

void print_live_state(t_eater *eater, char *msg)
{
    long timestamp;
    timestamp = get_current_absolute_time_in_ms() - eater->ptr_mona->start_time_abs;

    if (!stop_simulation_by_reading_stop_flag(eater))
    {
        pthread_mutex_lock(&eater->ptr_mona->printf_mutex);
        printf("%ld %d %s\n", timestamp, eater->id + 1, msg);
        pthread_mutex_unlock(&eater->ptr_mona->printf_mutex);
    }
}

void print_death_state(t_eater *eater, char *msg)
{
    long timestamp;
    timestamp = get_current_absolute_time_in_ms() - eater->ptr_mona->start_time_abs;
    pthread_mutex_lock(&eater->ptr_mona->printf_mutex);
    printf("%ld %d %s\n", timestamp, eater->id + 1, msg);
    pthread_mutex_unlock(&eater->ptr_mona->printf_mutex);
}
int stop_simulation_by_reading_stop_flag(t_eater *eater)
{
    pthread_mutex_lock(&eater->ptr_mona->stop_flag_mutex);
    if (eater->ptr_mona->stop_flag)
    {
        pthread_mutex_unlock(&eater->ptr_mona->stop_flag_mutex);
        return 1;
    }
    pthread_mutex_unlock(&eater->ptr_mona->stop_flag_mutex);
    return 0;
}
