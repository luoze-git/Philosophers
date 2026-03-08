#include "philo.h"

/*int pthread_create(
	pthread_t *thread,
	const pthread_attr_t *attr,
	void *(*start_routine)(void *),
	void *arg
);
*/
int	create_threads(t_monitor *mona)
{
	int		i;
	t_eater	*eater;

	i = 0;
	eater = mona->eater;
	while (i < mona->num_eater)
	{
		if (pthread_create(&eater[i].thread_id, NULL, eater_routine,
				&eater[i]) != 0)
		{
			set_stop_flag_with_mutex(mona);
			join_multi_threads(mona, i);
			return (1);
		}
		i++;
	}
	if (pthread_create(&mona->monitor_thread, NULL, monitor_routine, mona) != 0)
	{
		set_stop_flag_with_mutex(mona);
		join_multi_threads(mona, mona->num_eater);
		return (1);
	}
	return (0);
}

int	start_simulation(t_monitor *mona)
{
	if (create_threads(mona))
	{
		free_all_malloc_d(mona);
		destroy_mona_mutex(mona);
		destroy_eater_mutex(mona->eater, mona->num_eater);
		return (1);
	}
	return (0);
}

/// @brief clean up malloced, mutex, join threads
/// @param mona
void	normal_cleanup_all(t_monitor *mona)
{
	int	i;

	i = 0;
	pthread_join(mona->monitor_thread, NULL);
	while (i < mona->num_eater)
	{
		pthread_join(mona->eater[i].thread_id, NULL);
		i++;
	}
	destroy_eater_mutex(mona->eater, mona->num_eater);
	destroy_mona_mutex(mona);
	free_all_malloc_d(mona);
}
// /// args could be 5 - 6; must check the type

// rough arg condition:  time_to_die > 2 * time_to_eat   parallel eating waves

/*number_of_philosophers1 time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]*/

int	main(int argc, char **argv)
{
	t_monitor	mona;

	if (parse_args(&mona, argc, argv))
		return (1);
	if (prep_mona_n_eaters_pre_threads(&mona))
		return (1);
	if (start_simulation(&mona))
		return (1);
	normal_cleanup_all(&mona);
	return (0);
}
