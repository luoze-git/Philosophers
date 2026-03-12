#include "philo_bonus.h"

// get current time and transform it to milliseconds. return -1 on error
long	get_curr_time_absolute_in_ms(void)
{
	long			now;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	now = 1000 * tv.tv_sec + tv.tv_usec / 1000;
	return (now);
}

long ft_atol_assume_legit_input(char *str)
{
	int		i;
	long	result;

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

void	print_live_state(t_eater *eater, char *msg)
{
	long	curr_time;

	curr_time = get_curr_time_absolute_in_ms()
		- eater->ptr_mama->start_time_abs;
	if (!stop_flag_is_not_1(eater))
	{
		sem_wait(eater->ptr_mama->sem_printf);
		printf("%-6ld %d %s\n", curr_time, eater->id, msg);
		sem_post(eater->ptr_mama->sem_printf);
	}
}

int stop_flag_is_not_1(t_eater *eater)
{
	pthread_mutex_lock(&eater->mutex_eater);
	if (eater->stop_flag)
	{
		pthread_mutex_unlock(&eater->mutex_eater);
		return (1);
	}
	pthread_mutex_unlock(&eater->mutex_eater);
	return (0);
}

