#include "philo_bonus.h"
typedef struct s_parent
{
    int num_eater;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int must_eat_count;
    int finished_eater;
    int stop_flag;
    long start_time_abs;
} t_parent;

int init_mom(t_parent *mom)
{
    mom->finished_eater = 0;
    mom->stop_flag = 0;
    mom->start_time_abs = get_current_absolute_time_in_ms();
    return 0;
}

int generate_processes(t_parent* mom)
{
    
}
int main(int argc, char* argv[])
{
    t_parent mom;
    if (parse_args(&mom , argc , argv))
        return 1;
    init_mom(&mom);
    generate_processes(&mom);
    wait_for_return(&mom);
    return 0 ;
}