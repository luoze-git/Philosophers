#include "philo.h"

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
