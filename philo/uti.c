#include "philo.h"

// get current time and transform it to milliseconds. return -1 on error
long	get_current_absolute_time_in_ms(void)
{
	long			now;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	now = 1000 * tv.tv_sec + tv.tv_usec / 1000;
	return (now);
}

long	ft_atol_assume_legit_input(char *str)
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
	long	relative_printed_t;

	relative_printed_t = get_current_absolute_time_in_ms()
		- eater->ptr_mona->start_time_abs;
	if (!stop_simulation_by_reading_stop_flag(eater))
	{
		pthread_mutex_lock(&eater->ptr_mona->printf_n_stop_mutex);
		printf("%-6ld %d %s\n", relative_printed_t, eater->id, msg);
		pthread_mutex_unlock(&eater->ptr_mona->printf_n_stop_mutex);
	}
}

void	print_death_n_set_stop(t_eater *eater, char *msg)
{
	long	relative_printed_t;

	relative_printed_t = get_current_absolute_time_in_ms()
		- eater->ptr_mona->start_time_abs;
	pthread_mutex_lock(&eater->ptr_mona->printf_n_stop_mutex);
	eater->ptr_mona->stop_flag = 1;
	printf("%-6ld %d %s\n", relative_printed_t, eater->id, msg);
	pthread_mutex_unlock(&eater->ptr_mona->printf_n_stop_mutex);
}
int	stop_simulation_by_reading_stop_flag(t_eater *eater)
{
	pthread_mutex_lock(&eater->ptr_mona->printf_n_stop_mutex);
	if (eater->ptr_mona->stop_flag)
	{
		pthread_mutex_unlock(&eater->ptr_mona->printf_n_stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&eater->ptr_mona->printf_n_stop_mutex);
	return (0);
}
