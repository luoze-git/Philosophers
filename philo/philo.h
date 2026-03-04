#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <limits.h>

typedef struct s_control_philo
{
	int number_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat_count;
	long start_time;
	int stop_flag;
	pthread_mutex_t *forks;
	pthread_mutex_t printf_mutex;
	pthread_mutex_t stop_flag_mutex;
	t_philo_child *philos;
} t_control_philo;

typedef struct s_philo_child
{
	int id;
	pthread_t thread_id;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	long last_meal_time;
	int meals_eaten;
	t_control_philo *ctl_ptr;
} t_philo_child;
/*parse*/
int parse_args(t_control_philo *ctl, int argc, char **argv);
int check_args_legitimacy(int argc, char **argv);
long get_current_time_in_ms(void);
long ft_atol_assume_legit_input(char *str);

/*init before spawning threads*/
int init_philos_struct(t_control_philo *ctl);


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
