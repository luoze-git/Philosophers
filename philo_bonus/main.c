#include "philo_bonus.h"

static void	wait_for_children_exit(t_parent *mama);
static void	kill_cruelly_n_assign_exit_code(t_parent *mama, pid_t died_prc,
				int exit_code);

int	main(int argc, char *argv[])
{
	t_parent	mama;

	if (parse_args(&mama, argc, argv))
		return (1);
	if (init_mama(&mama))
		return (1);
	if (spawn_children_processes(&mama))
		return (1);
	wait_for_children_exit(&mama);
	clean(&mama);
	return (0);
}

static void	wait_for_children_exit(t_parent *mama)
{
	int	i;
	int	full_count;
	int	returnd_pid;
	int	status;
	int	code;

	i = 0;
	full_count = 0;
	while (i < mama->num_eater)
	{
		returnd_pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			code = WEXITSTATUS(status);
			if (code == DEAD || code == ERR)
				kill_cruelly_n_assign_exit_code(mama, returnd_pid, code);
			else if (code == EATER_FULL)
				full_count++;
		}
		i++;
	}
	if (mama->exit_code == UNSET && full_count == mama->num_eater)
		mama->exit_code = EATER_FULL;
}

static void	kill_cruelly_n_assign_exit_code(t_parent *mama, pid_t died_prc,
		int exit_code)
{
	int	i;

	i = 0;
	while (i < mama->num_eater)
	{
		if (mama->eater_pid[i] != died_prc)
			kill(mama->eater_pid[i], SIGKILL);
		i++;
	}
	mama->exit_code = exit_code;
}
