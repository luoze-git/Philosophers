#include "philo.h"


int parse_args(t_control_philo0 *ctl, int argc, char **argv)
{
    if (check_args_legitimacy(argc, argv))
    {
        printf("this is not acceptible for me for a reason stated above.");
        return 1;
    }
    load_ctl_from_args(ctl, argc, argv);
    if (init_ctl(ctl))
        return 1;
    return (0);
}

/// args could be 5 - 6; must check the type
int main(int argc, char **argv)
{
    t_control_philo0 ctl;
    if (parse_args(&ctl, argc, argv))
        return (1);
    if (init_simulation(&ctl))
        return (1);

    start_simulation(&ctl);

    cleanup(&ctl);
    return (0);
}
