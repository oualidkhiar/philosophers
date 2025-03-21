/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:29:06 by oukhiar           #+#    #+#             */
/*   Updated: 2025/03/21 01:57:43 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*get_life_routine(int ac, char **av)
{
	t_philo	*ret;

	ret = malloc(sizeof(t_philo));
	if (!ret)
		return (NULL);
	ret->nb_ph = ft_atoi(av[1]);
	ret->tm_die = ft_atoi(av[2]);
	ret->tm_eat = ft_atoi(av[3]);
	ret->tm_slp = ft_atoi(av[4]);
	ret->start_time = get_time_in_ms(0);
	ret->check = 0;
	if (ac == 6)
	{
		ret->check = 1;
		ret->nb_meal = ft_atoi(av[5]);
	}
	return (ret);
}

int	main(int ac, char **av)
{
	t_philo	*life_routine;

	if (ac == 5 || ac == 6)
	{
		if (check_is_digit(av))
			return (1);
		life_routine = get_life_routine(ac, av);
		philo_manager(life_routine);
		free(life_routine);
	}
	else
		ft_putstr_fd(2, "try using 4 or 5 argument\n");
	return (0);
}
