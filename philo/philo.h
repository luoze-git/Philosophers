#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <limits.h>

typedef struct s_monitor t_monitor;

typedef struct s_eater
{
	int id;
	long last_eating_time_abs;
	int meals_eaten;
	pthread_t thread_id;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	pthread_mutex_t meal_state;
	t_monitor *ptr_mona;
} t_eater;

typedef struct s_monitor
{
	int num_eater;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	int must_eat_count;
	int finished_eater;
	int stop_flag;
	long start_time_abs;
	pthread_mutex_t finished_eater_mutex;
	pthread_mutex_t *forks;
	pthread_mutex_t printf_mutex;
	pthread_mutex_t stop_flag_mutex;
	t_eater *eater;
	pthread_t monitor_thread;
} t_monitor;

int parse_args(t_monitor *mona, int argc, char **argv);
int prep_mona_n_eaters_pre_threads(t_monitor *mona);

long ft_atol_assume_legit_input(char *str);
long get_current_absolute_time_in_ms(void);
int stop_simulation_by_reading_stop_flag(t_eater *eater);
void print_live_state(t_eater *eater, char *msg);
void print_death_state(t_eater *eater, char *msg);

void *monitor_routine(void *arg);
void *eater_routine(void *arg);
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
