#include "philo.h"
/*
// why the variables of left fork and right fork is needed
	- to simplify the problem plus the circular fork is neater.*/

static int	init_eaters(t_monitor *mona)
{
	t_eater	*eater;
	int		i;

	i = 0;
	eater = mona->eater;
	while (i < mona->num_eater)
	{
		eater[i].id = i + 1;
		eater[i].ptr_mona = mona;
		eater[i].right_fork = mona->forks + i;
		eater[i].left_fork = mona->forks + ((i + 1) % mona->num_eater);
		eater[i].last_eating_time_abs = mona->start_time_abs;
		eater[i].meals_eaten = 0;
		if (pthread_mutex_init(&eater[i].state_mutex, NULL) != 0)
		{
			destroy_eater_mutex(eater, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_for_printf_n_stop_flag_n_finished(t_monitor *mona)
{
	if (pthread_mutex_init(&mona->printf_n_stop_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&mona->finished_eater_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&mona->printf_n_stop_mutex);
		return (1);
	}
	return (0);
}

int	init_mona(t_monitor *mona)
{
	int	i;

	i = 0;
	while (i < mona->num_eater)
	{
		if (pthread_mutex_init(&mona->forks[i], NULL) != 0)
		{
			destroy_mutex_array(mona->forks, i);
			return (1);
		}
		i++;
	}
	if (init_for_printf_n_stop_flag_n_finished(mona))
	{
		destroy_mutex_array(mona->forks, mona->num_eater);
		return (1);
	}
	mona->stop_flag = 0;
	mona->finished_eater = 0;
	mona->start_time_abs = get_current_absolute_time_in_ms();
	return (0);
}

static int	malloc_d_eaters_n_forks(t_monitor *mona)
{
	mona->forks = malloc(mona->num_eater * sizeof(pthread_mutex_t));
	if (!(mona->forks))
		return (1);
	mona->eater = malloc(mona->num_eater * sizeof(t_eater));
	if (!mona->eater)
	{
		free(mona->forks);
		return (1);
	}
	return (0);
}

// initiate up the monitor struct along with the main needed identity information.
int	prep_mona_n_eaters_pre_threads(t_monitor *mona)
{
	if (malloc_d_eaters_n_forks(mona))
	{
		write(2, "malloc failed\n", 14);
		return (1);
	}
	if (init_mona(mona))
	{
		free_all_malloc_d(mona);
		return (1);
	}
	if (init_eaters(mona))
	{
		free_all_malloc_d(mona);
		destroy_mona_mutex(mona);
		return (1);
	}
	return (0);
}
