# include "philo_bonus.h"

void kill_cruelly_n_post_printf(t_parent *mama, pid_t died_prc)
{
    int i;
    i = 0;
    while (i < mama->num_eater)
    {
        if (mama->eater_pid[i] != died_prc)
            kill(mama->eater_pid[i]);
        i++;
    }
}
