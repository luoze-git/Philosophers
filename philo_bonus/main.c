#include "philo_bonus.h"

// todo: you will check all the open failed detection. Clean strategy. 



int start_simulation(t_parent* mama)
{
    int i;
    i = 0;
    while ( i < mama->num_eater)
    {
        mama->eater_pid[i] = fork();
        if (mama->eater_pid[i] == 0)
            eater_transform(mama, i + 1);
        if (mama->eater_pid[i] == -1)
            deal_with_mallocc_clean_n_pid(mama);
        i++;
    }
    return 0;
}



void wait_for_return(t_parent *mama)
{
    int i;
    int returnd_pid;
    int status;
    i = 0;

    // this is the loop for must_eat_count
    while (i < mama->num_eater)
    {
        returnd_pid = waitpid(-1, &status, 0);
        if (status == 1)
        {
            kill_cruelly_n_post_printf(mama, returnd_pid);
            return;
        }
        i++;
    }
}

int main(int argc, char* argv[])
{
    t_parent mama;
    if (parse_args(&mama , argc , argv))
        return 1;
    if (init_mama(&mama))
        return 1 ;
    if (start_simulation(&mama))
        return 1; 
    wait_for_return(&mama);
    return 0 ;
}