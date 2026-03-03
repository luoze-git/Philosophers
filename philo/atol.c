#include "philo.h"

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
