#include "philo_bonus.h"

// todo: you will check all the open failed detection. Clean strategy. 
int setup_semaphore(t_parent *mama)
{
    sem_unlink ("\fork");
    sem_unlink("\printf");
    sem_unlink("\waiter");
    
    mama->sem_forks = sem_open ("\fork" , O_CREAT, 0644, 
    mama->num_eater);
    if (mama->sem_forks == SEM_FAILED)
        return 1;
    mama->sem_printf = sem_open("\printf" ,O_CREAT, 0644 , 1);
    if (mama->sem_printf = SEM_FAILED)
    mama->sem_waiter = sem_open ("\waiter", O_CREAT, 0644, mama->num_eater - 1);
    return 0;
}

int init_mama(t_parent *mama)
{
    if (setup_semaphore(mama))
        return 1 ; 
    mama->finished_eater = 0;
    mama->start_time_abs = get_curr_time_absolute_in_ms();
    // here no need to clean anything
    mama->eater_pid = malloc(mama->num_eater * sizeof(*(mama->eater_pid)));
    if (mama->eater_pid == NULL)
        return 1;
    return 0;
}

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

void kill_cruelly_n_post_printf(t_parent *mama , pid_t died_prc)
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