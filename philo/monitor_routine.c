
#include "philo.h"

void	set_stop_flag_with_mutex(t_monitor *mona)
{
	pthread_mutex_lock(&mona->printf_n_stop_mutex);
	mona->stop_flag = 1;
	pthread_mutex_unlock(&mona->printf_n_stop_mutex);
}

int	thread_is_dead(t_eater *eater, long time_to_die)
{
	pthread_mutex_lock(&eater->state_mutex);
	if (get_current_absolute_time_in_ms()
		- eater->last_eating_time_abs > time_to_die)
	{
		pthread_mutex_unlock(&eater->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&eater->state_mutex);
	return (0);
}

int	eaters_finish_eating(t_monitor *mona)
{
	pthread_mutex_lock(&mona->finished_eater_mutex);
	if (mona->finished_eater == mona->num_eater)
	{
		pthread_mutex_unlock(&mona->finished_eater_mutex);
		return (1);
	}
	pthread_mutex_unlock(&mona->finished_eater_mutex);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_monitor	*mona;
	int			i;

	i = 0;
	mona = (t_monitor *)arg;
	while (1)
	{
		while (i < mona->num_eater)
		{
			if (thread_is_dead(&mona->eater[i], mona->time_to_die))
			{
				print_death_n_set_stop(&mona->eater[i], "died.");
				return (NULL);
			}
			i++;
		}
		if (mona->must_eat_count != -1 && eaters_finish_eating(mona))
		{
			set_stop_flag_with_mutex(mona);
			return (NULL);
		}
		i = 0;
		usleep(1000);
	}
	return (NULL);
}
