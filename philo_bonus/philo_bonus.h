#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <pthread.h>
#include <semaphore.h>
#include <stddef.h>
#include <sys/time.h>
#include <sys/types.h>
#include <limits.h>

#include <fcntl.h> // for O_CREAT

#define EXIT_DEAD 1
#define EXIT_EATER_FULL 2

typedef struct s_parent t_parent;

typedef struct s_eater
{
    int id;
    long last_eating_time_abs;
    int meals_eaten;
    int stop_flag;
    pthread_mutex_t mutex_eater;
    t_parent *ptr_mama;
} t_eater;

typedef struct s_parent
{
    int num_eater;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int must_eat_count;
    pid_t *eater_pid;
    sem_t *sem_forks;
    sem_t *sem_printf;
    sem_t *sem_waiter;
    int finished_eater;
    long start_time_abs;
} t_parent;

long get_curr_time_absolute_in_ms(void);
long ft_atol_assume_legit_input(char *str);
void join_multi_threads(t_parent *mama, int num);

int parse_args(t_parent *mama, int argc, char **argv);
int prep_mama_n_eaters_pre_threads(t_parent *mama);
void destroy_eater_mutex(t_eater *eater, int num);
long ft_atol_assume_legit_input(char *str);
long get_curr_time_absolute_in_ms(void);
int stop_simulation_by_reading_stop_flag(t_eater *eater);
void print_live_state(t_eater *eater, char *msg);
void print_death_n_set_stop_n_never_post_sem(t_eater *eater, char *msg);

void *monitor_routine(void *arg);
void *eater_routine(void *arg);

void set_stop_flag_with_mutex(t_parent *mama);

void free_all_malloc_d(t_parent *mama);
void destroy_mutex_array(pthread_mutex_t *mutex,
                         int num);
void destroy_mama_mutex(t_parent *mama);
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