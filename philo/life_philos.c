/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 05:45:41 by oukhiar           #+#    #+#             */
/*   Updated: 2025/03/18 11:18:51 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dining_of_odd_id(t_philo_info *data)
{
	pthread_mutex_lock(data->right_fork);
	ft_print_status(data, "has taken a fork");
	if (data->data_of_philo->nb_ph == 1)
	{
		ft_usleep(data, data->data_of_philo->tm_die + 1);
		pthread_mutex_unlock(data->right_fork);
		return ;
	}
	pthread_mutex_lock(data->left_fork);
	ft_print_status(data, "has taken a fork");
	ft_print_status(data, "is eating");
	pthread_mutex_lock(&(data->data_of_philo->wr_eat[1]));
	data->last_time_eating = (get_time_in_ms() - data->date_of_birth);
	if (data->data_of_philo->check)
		data->n_diner++;
	pthread_mutex_unlock(&(data->data_of_philo->wr_eat[1]));
	ft_usleep(data, data->data_of_philo->tm_eat);
	pthread_mutex_unlock(data->right_fork);
	pthread_mutex_unlock(data->left_fork);
}

void	dining_of_even_id(t_philo_info *data)
{
	pthread_mutex_lock(data->left_fork);
	ft_print_status(data, "has taken a fork");
	pthread_mutex_lock(data->right_fork);
	ft_print_status(data, "has taken a fork");
	ft_print_status(data, "is eating");
	pthread_mutex_lock(&(data->data_of_philo->wr_eat[1]));
	data->last_time_eating = (get_time_in_ms() - data->date_of_birth);
	if (data->data_of_philo->check)
		data->n_diner++;
	pthread_mutex_unlock(&(data->data_of_philo->wr_eat[1]));
	ft_usleep(data, data->data_of_philo->tm_eat);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
}

void	eating(t_philo_info *data)
{
	if ((data->id % 2))
		dining_of_odd_id(data);
	else
		dining_of_even_id(data);
}

void	sleeping(t_philo_info *data)
{
	ft_print_status(data, "is sleeping");
	ft_usleep(data, data->data_of_philo->tm_slp);
}

void	thinking(t_philo_info *data)
{
	ft_print_status(data, "is thinking");
}
