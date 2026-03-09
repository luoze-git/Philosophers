#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <pthread.h>
#include <semaphore.h>
#include <stddef.h>
#include <sys/time.h>
#include <sys/types.h>
#include <limits.h>

typedef struct s_eater
{
    int id;
    long last_eating_time_abs;
    int meals_eaten;
    t_parent *ptr_mom;
} t_eater;

typedef struct s_parent
{
    int num_eater;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int must_eat_count;
    int finished_eater;
    int stop_flag;
    long start_time_abs;
} t_parent;

long get_current_absolute_time_in_ms(void);
long ft_atol_assume_legit_input(char *str);
// /* Allowed external functions (bonus) */
// extern void	*memset(void *s, int c, size_t n);
// extern int	printf(const char *format, ...);
// extern void	*malloc(size_t size);
// extern void	free(void *ptr);
// extern ssize_t	write(int fd, const void *buf, size_t count);
// extern pid_t	fork(void);
// extern int	kill(pid_t pid, int sig);
// extern void	exit(int status);
// extern int	pthread_create(pthread_t *thread, const pthread_attr_t *attr,
// 				void *(*start_routine)(void *), void *arg);
// extern int	pthread_detach(pthread_t thread);
// extern int	pthread_join(pthread_t thread, void **retval);
// extern int	usleep(useconds_t usec);
// extern int	gettimeofday(struct timeval *tv, struct timezone *tz);
// extern pid_t	waitpid(pid_t pid, int *wstatus, int options);
// extern sem_t	*sem_open(const char *name, int oflag, ...);
// extern int	sem_close(sem_t *sem);
// extern int	sem_post(sem_t *sem);
// extern int	sem_wait(sem_t *sem);
// extern int	sem_unlink(const char *name);

#endif