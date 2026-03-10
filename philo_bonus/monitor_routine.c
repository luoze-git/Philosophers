#include "philo_bonus.h"

void	set_stop_flag_with_mutex(t_eater *eater)
{
	pthread_mutex_lock(&eater->mutex_eater);
	eater->stop_flag = 1;
	pthread_mutex_unlock(&eater->mutex_eater);
}

int	eater_is_dead(t_eater *eater, long time_to_die)
{
	pthread_mutex_lock(&eater->mutex_eater);
	if (get_current_absolute_time_in_ms()
		- eater->last_eating_time_abs > time_to_die)
	{
		pthread_mutex_unlock(&eater->mutex_eater);
		return (1);
	}
	pthread_mutex_unlock(&eater->mutex_eater);
	return (0);
}

int	eater_is_full(t_eater *eater)
{
	pthread_mutex_lock(&eater->mutex_eater);
	if (eater->meals_eaten == eater->ptr_mama->must_eat_count)
	{
		pthread_mutex_unlock(&eater->mutex_eater);
		return (1);
	}
	pthread_mutex_unlock(&eater->mutex_eater);
	return (0);
}

int start_monitoring(t_eater *eater)
{
	int i;

	i = 0;
	while (1)
	{
		if (eater_is_dead(eater, eater->ptr_mama->time_to_die))
		{
			print_death_n_set_stop_n_never_post_sem(eater, "died.");
			return (NULL);
		}
		if (eater->ptr_mama->must_eat_count != -1 && eater_is_full(eater))
		{
			set_stop_flag_with_mutex(eater);
			return (NULL);
		}
		usleep(1000);
	}
}

