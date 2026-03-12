#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h> // for O_CREAT
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define UNSET 0
# define DEAD 1
# define EATER_FULL 2
# define ERR 3

typedef struct s_parent	t_parent;

typedef struct s_eater
{
	int					id;
	long				last_eating_time_abs;
	int					meals_eaten;
	int					stop_flag;
	pthread_mutex_t		mutex_eater;
	pthread_t			thread_eater_eater;
	t_parent			*ptr_mama;
}						t_eater;

typedef struct s_parent
{
	int					num_eater;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					must_eat_count;
	pid_t				*eater_pid;
	sem_t				*sem_forks;
	sem_t				*sem_printf;
	sem_t				*sem_waiter;
	int					exit_code;
	long				start_time_abs;
}						t_parent;

/* Input parsing */
int						parse_args(t_parent *mama, int argc, char **argv);
int						check_args_legitimacy(int argc, char **argv);

/* Initialization */
int						init_mama(t_parent *mama);

/* Simulation control */
int						spawn_children_processes(t_parent *mama);

/* Eater process */
int						start_monitoring(t_eater *eater);
void					*eater_routine(void *arg);

/* Utility */
long					get_curr_time_absolute_in_ms(void);
long					ft_atol_assume_legit_input(char *str);
void					print_live_state(t_eater *eater, char *msg);
int						stop_flag_is_not_1(t_eater *eater);

/* Cleanup */
void					clean_sems_guarded(t_parent *mama);
void					clean(t_parent *mama);
void					clean_children_process(t_eater *eater);
void					destroy_local_mutex(t_eater *eater);

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
