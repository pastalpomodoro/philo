#include "philo.h"

int     all_alive(t_philo *philos)
{
    int i;

    i = -1;
    while (i++, i < philos->table->n_philos)
    {
        pthread_mutex_lock(&philos[i].alive_mutex);
        if (philos[i].alive == 0)
            return (pthread_mutex_unlock(&philos[i].alive_mutex), 0);
        pthread_mutex_unlock(&philos[i].alive_mutex);
    }
    return (1);
}

void *shugar_daddy_exec(void *strc)
{
    t_philo *philos;
    int i;
    long lm;

    philos = (t_philo *)strc;
    while (all_alive(philos))
    {
        i = -1;
        while (i++, i < philos->table->n_philos)
        {
            pthread_mutex_lock(&philos[i].last_meal_mutex);
            lm = philos[i].last_meal;
            pthread_mutex_unlock(&philos[i].last_meal_mutex);
            if ((get_time() - lm) > philos->table->time_to_die)
            {
                kill_philos(philos);
                print_mutex(&philos[i], "dead");
                break;
            }
        }
    }
    return (NULL);
}

void   *create_philos(t_philo *philos, int n)
{
    int i;
    pthread_t       shugar_daddy;
    
    i = -1;
    while (i++, i < (n + 1))
    {
        if (i == n)
        {
            if (pthread_create(&shugar_daddy, NULL, shugar_daddy_exec, philos) != 0)
                return (free(philos), NULL);
        }
        else if (pthread_create(&philos[i].philo, NULL, philo_exec, &philos[i]) != 0)
            return (free(philos), NULL);
    }
    i = -1;
    pthread_join(shugar_daddy, NULL);
    while (i++, i < n)
        pthread_join(philos[i].philo, NULL);
    i = -1;
    while (i++, i < n)
    {
        pthread_mutex_destroy(&philos[i].alive_mutex);
        pthread_mutex_destroy(&philos[i].last_meal_mutex);
    }
    free(philos);
    return (philos);
}

int main(int ac, char **av)
{
    t_philo *philos;
    t_table table;

    if (ac > 6 || ac < 5)
        return (printf("Missing argument!\n"), 0);
    
    table = init_table(ft_atoi(av[1]), av);
    philos = init_philo_tab(&table, ft_atoi(av[1]));
    philos->table->begin_time = get_time();
    create_philos(philos, ft_atoi(av[1]));
    free_table(&table, ft_atoi(av[1]));
    return (0);
}
