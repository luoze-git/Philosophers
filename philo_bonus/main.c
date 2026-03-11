#include "philo_bonus.h"

// todo: you will check all the open failed detection. Clean strategy. 



int spawn_children_processes(t_parent* mama)
{
    int i;
    i = 0;
    while ( i < mama->num_eater)
    {
        mama->eater_pid[i] = fork();
        if (mama->eater_pid[i] == 0)
            eater_transform(mama, i + 1);
        if (mama->eater_pid[i] == -1)
            continue;
        i++;
    }
    return 0;
}

void wait_for_children_exit(t_parent *mama)
{
    int i;
    int returnd_pid;
    int status;
    i = 0;

    // this is the loop for must_eat_count
    while (i < mama->num_eater)
    {
        returnd_pid = waitpid(-1, &status, 0);
        if (status == DEAD)
        {
            kill_cruelly(mama, returnd_pid);
            sem_post(mama->sem_printf);
            exit(0);
        }
        if (status == ERR)
        {
            kill_cruelly(mama, returnd_pid);
            exit(1);
        }
        i++;
    }
    exit(0);
}

int main(int argc, char* argv[])
{
    t_parent mama;
    if (parse_args(&mama , argc , argv))
        return 1;
    if (init_mama(&mama))
        return 1 ;
    if (spawn_children_processes(&mama))
        return 1; 
    wait_for_children_exit(&mama);
    return 0 ;
}