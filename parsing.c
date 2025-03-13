#include "philo.h"

int is_only_digit(char *str)
{
    int  i;

    i = -1;
    while (i++, str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (0);
    }
    return (1);
}
int check_all_np(char **av)
{
    int i;

    i = 0;
    while (i++, av[i])
    {
        if (is_only_digit(av[i]) == 0)
            return (0);
    }
    return (1);
}

int parsing(char **av)
{
    if (ft_atoi(av[1]) > 200 || ft_atoi(av[1]) < 1)
        return (0);
    else if (check_all_np(av) == 0)
        return (0);
    return (1);
}