#include "philo_bonus.h"

static int check_integer4B_overflow(int argc, char **argv);
static int check_chars_are_numeric_and_positive(int argc, char **argv);

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

/*this file is for checking the input legitimacy 
before parsing into struct. It allows size of 
integer arguments and storing them into long 
type variable. */
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

