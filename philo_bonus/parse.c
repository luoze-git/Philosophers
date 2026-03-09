#include "philo_bonus.h"

/*this file is for checking the input legitimacy before parsing into struct.
 It allows size of integer arguments and storing them into long type variable. */
static int check_chars_are_numeric_and_positive(int argc, char **argv)
{
	int i;
	int j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && argv[i][j] != '+')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
//  int int int int int check int types. all args is specified to be int.
static int check_integer4B_overflow(int argc, char **argv)
{
	long result;
	int i;

	i = 1;
	while (i < argc)
	{
		result = ft_atol_assume_legit_input(argv[i]);
		if (result > INT_MAX)
			return (1);
		i++;
	}
	return (0);
}

/*
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
*/
// no need to clean before exit
int check_args_legitimacy(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("invalid arg numbers");
		return (1);
	}
	// Every argument is strictly numeric
	// go through all of the chars to match the expected style
	if (check_chars_are_numeric_and_positive(argc, argv))
	{
		printf("invalid arg type: should be number");
		return (1);
	}
	// No overflow
	if (check_integer4B_overflow(argc, argv))
	{
		printf("integer overflows");
		return (1);
	}
	// number_of_philosophers >= 1
	if (ft_atol_assume_legit_input(argv[1]) < 1)
	{
		printf("Number of philosophers should be at least 1.");
		return (1);
	}
	return (0);
}

/*
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
*/

static void load_parsed_args(t_parent *mom, int argc, char **argv)
{
	mom->num_eater = (int)ft_atol_assume_legit_input(argv[1]);
	mom->time_to_die = ft_atol_assume_legit_input(argv[2]);
	mom->time_to_eat = ft_atol_assume_legit_input(argv[3]);
	mom->time_to_sleep = ft_atol_assume_legit_input(argv[4]);
	if (argc == 6)
		mom->must_eat_count = (int)ft_atol_assume_legit_input(argv[5]);
	else
		mom->must_eat_count = -1;
}

int pre_terminate(t_parent *mom)
{
	if (mom->must_eat_count == 0)
	{
		write(1, "0 meals", 7);
		return (1);
	}
	return (0);
}
/// @brief Precheck input satisfy the format. Then load the args into mom.
/// @param mom
/// @param argc
/// @param argv
/// @return 0 if suc. 1 if failed.
int parse_args(t_parent *mom, int argc, char **argv)
{
	if (check_args_legitimacy(argc, argv))
	{
		printf("this is not acceptible for me for a reason stated above.");
		return (1);
	}
	load_parsed_args(mom, argc, argv);
	if (pre_terminate(mom))
		return (1);
	return (0);
}
