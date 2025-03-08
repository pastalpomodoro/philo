#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_table
{
    int             n_philos;
    int             time_to_shit;
    int             time_to_eat;
    int             time_to_die;
    int             n_of_eat;
    long            begin_time;
    pthread_mutex_t *fork;
    pthread_mutex_t print;
}               t_table;

typedef struct s_philo
{
    int             alive;
    pthread_mutex_t alive_mutex;
    int             id;
    long            last_meal;
    pthread_mutex_t last_meal_mutex;
    t_table         *table;
    pthread_mutex_t *fork_l;
    pthread_mutex_t *fork_r;
    pthread_t       philo;
}               t_philo;

int	ft_atoi(const char *str);

//          init_philo.c
void    free_table(t_table *table, int n);
t_table init_table(int n, char **av);
t_philo *init_philo_tab(t_table *table, int n);


long get_time();
int print_mutex(t_philo *philo, char *str);
int eat(t_philo *philo);
void *philo_exec(void *struc);
void kill_philos(t_philo *philos);
#endif

// philo[i]->id = i;
// philo[i]->fourchette_gauche = fourchette[i];
// philo[i]->fourchette_droite = fourchette [(i % 2)/ nbr_philo]