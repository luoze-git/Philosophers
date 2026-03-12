#include "philo_bonus.h"

static void	load_parsed_args(t_parent *mama, int argc, char **argv);
static int	pre_terminate(t_parent *mama);

/// @brief Precheck input satisfy the format. Then load the args into mama.
/// @param mama
/// @param argc
/// @param argv
/// @return 0 if suc. 1 if failed.
int	parse_args(t_parent *mama, int argc, char **argv)
{
	if (check_args_legitimacy(argc, argv))
	{
		printf("this is not acceptible for me for a reason stated above.");
		return (1);
	}
	load_parsed_args(mama, argc, argv);
	if (pre_terminate(mama))
		return (1);
	return (0);
}

/*
./philo number_of_philosophers time_to_die
time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
*/

static void	load_parsed_args(t_parent *mama, int argc, char **argv)
{
	mama->num_eater = (int)ft_atol_assume_legit_input(argv[1]);
	mama->time_to_die = ft_atol_assume_legit_input(argv[2]);
	mama->time_to_eat = ft_atol_assume_legit_input(argv[3]);
	mama->time_to_sleep = ft_atol_assume_legit_input(argv[4]);
	if (argc == 6)
		mama->must_eat_count = (int)ft_atol_assume_legit_input(argv[5]);
	else
		mama->must_eat_count = -1;
}

static int	pre_terminate(t_parent *mama)
{
	if (mama->must_eat_count == 0)
	{
		write(1, "0 meals", 7);
		return (1);
	}
	return (0);
}
