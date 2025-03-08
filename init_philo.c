#include"philo.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	long	n;
	int		sign;

	i = 0;
	n = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		n = (n * 10) + str[i++] - '0';
    return (n * sign);
}
	
void    free_table(t_table *table, int n)
{
    int i;

    i = -1;
    while (i++, i < n) 
        pthread_mutex_destroy(&table->fork[i]);
    pthread_mutex_destroy(&table->print);
    free(table->fork);
}

t_table init_table(int n, char **av)
{
    t_table table;
    int i;

    table.fork = malloc(sizeof(pthread_mutex_t) * n);
    if (!table.fork)
        return (table);
    i = -1;
    table.n_philos = n;
    table.time_to_die = ft_atoi(av[2]);
    table.time_to_eat = ft_atoi(av[3]);
    table.time_to_shit = ft_atoi(av[4]);
    if (av[5])
        table.n_of_eat = ft_atoi(av[5]);
    else
        table.n_of_eat = -1;
    pthread_mutex_init(&table.print, NULL);
    while (i++, i < n)
        pthread_mutex_init(&table.fork[i], NULL);
    return (table);
}


t_philo *init_philo_tab(t_table *table, int n)
{
    t_philo *philo;
    int i;

    philo = malloc(sizeof(t_philo) * n);
    if (!philo)
        return (NULL);
    i = -1;
    while(i++, i < n)
    {
        pthread_mutex_init(&philo->alive_mutex, NULL);
        pthread_mutex_init(&philo->last_meal_mutex, NULL);
        philo[i].last_meal = 0;
        philo[i].alive = 1;
        philo[i].table = table;
        philo[i].id = i;
        philo[i].fork_l = &table->fork[i];
        if ((i + 1) < n)
            philo[i].fork_r = &table->fork[i + 1];
        else
            philo[i].fork_r = &table->fork[0];
    }
    return (philo);
}
