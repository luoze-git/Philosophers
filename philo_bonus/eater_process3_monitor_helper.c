#include "philo_bonus.h"

int	eater_is_dead(t_eater *eater, long time_to_die)
{
	pthread_mutex_lock(&eater->mutex_eater);
	if (get_curr_time_absolute_in_ms()
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

void set_stop_flag_with_mutex(t_eater *eater)
{
	pthread_mutex_lock(&eater->mutex_eater);
	eater->stop_flag = 1;
	pthread_mutex_unlock(&eater->mutex_eater);
}

