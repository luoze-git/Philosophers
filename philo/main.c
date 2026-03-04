#include "philo.h"


// void start_simulation(t_control_philo *ctl);
// {

// }

// /// args could be 5 - 6; must check the type
int main(int argc, char **argv)
{
    t_control_philo ctl;
    if (parse_args(&ctl, argc, argv))
        return (1);
    if (init_philos_struct(&ctl))
        return (1);

    start_simulation(&ctl);

    cleanup(&ctl);
    return (0);
}
