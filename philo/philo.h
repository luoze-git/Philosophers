#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <limits.h>

typedef struct s_eater
{
	int id;
	long last_meal_time;
	int meals_eaten;
	pthread_t thread_id;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	t_monitor *ptr_mona;
} t_eater;

typedef struct s_monitor
{
	int num_eater;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat_count;
	int stop_flag;
	long start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t printf_mutex;
	pthread_mutex_t stop_flag_mutex;
	t_eater *eater;
	pthread_t monitor_thread;
} t_monitor;



int parse_args(t_monitor *ctl, int argc, char **argv);
int prep_mona_n_eaters_pre_threads(t_monitor *mona);




long get_current_time_in_ms(void);



/*init before spawning threads*/

// /* Allowed external functions (mandatory)
// extern void	*memset(void *s, int c, size_t n);
// extern int	printf(const char *format, ...);
// extern void	*malloc(size_t size);
// extern void	free(void *ptr);
// extern ssize_t	write(int fd, const void *buf, size_t count);
// extern int	usleep(useconds_t usec);
// extern int	gettimeofday(struct timeval *tv, struct timezone *tz);
// extern int	pthread_create(pthread_t *thread, const pthread_attr_t *attr,
// 				void *(*start_routine)(void *), void *arg);
// extern int	pthread_detach(pthread_t thread);
// extern int	pthread_join(pthread_t thread, void **retval);
// extern int	pthread_mutex_init(pthread_mutex_t *mutex,
// 				const pthread_mutexattr_t *attr);
// extern int	pthread_mutex_destroy(pthread_mutex_t *mutex);
// extern int	pthread_mutex_lock(pthread_mutex_t *mutex);
// extern int	pthread_mutex_unlock(pthread_mutex_t *mutex);
// */
#endif
