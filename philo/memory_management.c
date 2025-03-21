/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:26:26 by oukhiar           #+#    #+#             */
/*   Updated: 2025/03/18 11:06:27 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_philo_info **adress, int how_much)
{
	int	i;

	i = 0;
	while (i < how_much)
	{
		free(adress[i]);
		i++;
	}
	free(adress);
}

void	ft_memory_management(t_philo *life_routine, t_philo_info **data)
{
	int	count;

	count = 0;
	while (count < life_routine->nb_ph)
	{
		pthread_mutex_destroy(&(life_routine->forks[count]));
		count++;
	}
	pthread_mutex_destroy(&(life_routine->wr_eat[0]));
	pthread_mutex_destroy(&(life_routine->wr_eat[1]));
	ft_free(data, life_routine->nb_ph);
	free(life_routine->forks);
	free(life_routine);
}
