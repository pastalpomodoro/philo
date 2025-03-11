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
int parsing(char **av);

//          init_philo.c
void    free_table(t_table *table, int n);
t_table init_table(int n, char **av);
t_philo *init_philo_tab(t_table *table, int n);


long get_time();
int print_mutex(t_philo *philo, char *str, int n);
int eat(t_philo *philo);
void *philo_exec(void *struc);
void kill_philos(t_philo *philos);

# define BLACK "\033[0;30m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define PURPLE "\033[0;35m"
# define WHITE "\033[0;37m"
# define BOLD_BLACK "\033[1;30m"
# define BOLD_GREEN "\033[1;32m"
# define BOLD_RED "\033[1;31m"
# define BOLD_YELLOW "\033[1;33m"
# define BOLD_BLUE "\033[1;34m"
# define BOLD_CYAN "\033[1;36m"
# define BOLD_PURPLE "\033[1;35m"
# define BOLD_WHITE "\033[1;37m"
# define CLEAR "\033c"
# define RESET_COLOR "\e[m"

#endif
