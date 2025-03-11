#include "philo.h"


long get_time()
{
    struct timeval  beghin_time;

    gettimeofday(&beghin_time, NULL);
    return (beghin_time.tv_sec * 1000 + beghin_time.tv_usec / 1000);
}

int print_mutex(t_philo *philo, char *str, int n)
{

    pthread_mutex_lock(&philo->alive_mutex);
    if (philo->alive == 0)
        return (pthread_mutex_unlock(&philo->alive_mutex), 0);
    pthread_mutex_unlock(&philo->alive_mutex);
    if (n == 1)
    {
        pthread_mutex_lock(&philo->table->print);
        printf(BLUE"%ld %d %s\n", get_time() - philo->table->begin_time, philo->id + 1, str);
    }
    if (n == 2)
    {
        pthread_mutex_lock(&philo->table->print);
        printf(PURPLE"%ld %d %s\n", get_time() - philo->table->begin_time, philo->id + 1, str);
    }
    if (n == 3)
    {
        pthread_mutex_lock(&philo->table->print);
        printf(RED"%ld %d %s\n", get_time() - philo->table->begin_time, philo->id + 1, str);
    }
    pthread_mutex_unlock(&philo->table->print);
    printf(RESET_COLOR);
    return (1);
}

int eat(t_philo *philo)
{
    if (philo->id % 2)
        usleep(400);
    if (philo->fork_l < philo->fork_r)
    {
        pthread_mutex_lock(philo->fork_l);
        print_mutex(philo, "has taken a fork ", 1);
        pthread_mutex_lock(philo->fork_r);
        print_mutex(philo, "has taken a fork ", 1);
    }
    else
    {
        pthread_mutex_lock(philo->fork_r);
        print_mutex(philo, "has taken a fork ", 1);
        pthread_mutex_lock(philo->fork_l);
        print_mutex(philo, "has taken a fork ", 1);
    }
    print_mutex(philo, "is eating", 1);
    pthread_mutex_lock(&philo->last_meal_mutex);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->last_meal_mutex);
    usleep(philo->table->time_to_eat * 1000);
    pthread_mutex_unlock(philo->fork_l);
    pthread_mutex_unlock(philo->fork_r);
    return (1);
}

void *philo_exec(void *struc)
{
    t_philo *philo;
    int i;

    philo = (t_philo *)struc;
    i = philo->table->n_of_eat;
    if (i == -1)
        i = 1;
    while (i--)
    {
        pthread_mutex_lock(&philo->alive_mutex);
        if (philo->alive == 0)
        {
            pthread_mutex_unlock(&philo->alive_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->alive_mutex);
        eat(philo);
        print_mutex(philo, "is sleeping", 2);
        usleep(philo->table->time_to_shit * 1000);
        print_mutex(philo, "is thinking", 2);
        i += philo->table->n_of_eat == -1;
    }
    pthread_mutex_lock(&philo->alive_mutex);
    philo->alive = 0;
    pthread_mutex_unlock(&philo->alive_mutex);
    return (NULL);
}

void kill_philos(t_philo *philos)
{
    int i;

    i = -1;
    while (i++, i < philos->table->n_philos)
    {
        pthread_mutex_lock(&philos[i].alive_mutex);
        philos[i].alive = 0;
        pthread_mutex_unlock(&philos[i].alive_mutex);
    }
}