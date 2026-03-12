#include "philo_bonus.h"

static int eater_is_dead(t_eater *eater, long time_to_die);
static int eater_is_full(t_eater *eater);
static void print_death_n_set_stop_n_never_post_sem(t_eater *eater, char *msg);
static void set_stop_flag_with_mutex(t_eater *eater);

int start_monitoring(t_eater *eater)
{
	int i;

	i = 0;
	while (1)
	{
		if (eater_is_dead(eater, eater->ptr_mama->time_to_die))
		{
			print_death_n_set_stop_n_never_post_sem(eater, "died");
			return (DEAD);
		}
		if (eater->ptr_mama->must_eat_count != -1 && eater_is_full(eater))
		{
			set_stop_flag_with_mutex(eater);
			return (EATER_FULL);
		}
		usleep(1000);
	}
}

static void print_death_n_set_stop_n_never_post_sem(t_eater *eater, char *msg)
{
	long curr_time;

	curr_time = get_curr_time_absolute_in_ms() - eater->ptr_mama->start_time_abs;
	pthread_mutex_lock(&eater->mutex_eater);
	eater->stop_flag = 1;
	pthread_mutex_unlock(&eater->mutex_eater);
	sem_wait(eater->ptr_mama->sem_printf);
	printf("%-6ld %d %s\n", curr_time, eater->id, msg);
}

static int eater_is_dead(t_eater *eater, long time_to_die)
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

static int eater_is_full(t_eater *eater)
{
	pthread_mutex_lock(&eater->mutex_eater);
	if (eater->meals_eaten >= eater->ptr_mama->must_eat_count)
	{
		pthread_mutex_unlock(&eater->mutex_eater);
		return (1);
	}
	pthread_mutex_unlock(&eater->mutex_eater);
	return (0);
}

static void set_stop_flag_with_mutex(t_eater *eater)
{
	pthread_mutex_lock(&eater->mutex_eater);
	eater->stop_flag = 1;
	pthread_mutex_unlock(&eater->mutex_eater);
}
