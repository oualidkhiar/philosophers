/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_life.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 02:13:42 by oukhiar           #+#    #+#             */
/*   Updated: 2025/03/21 01:04:13 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philo_info *data)
{
	if (data->id % 2 == 0 && data->data_of_philo->nb_ph % 2 != 0)
		ft_usleep(data, 20);
	else if (data->id % 2 == 0 && data->data_of_philo->nb_ph % 2 == 0)
		usleep(100);
	sem_wait(data->data_of_philo->sem);
	ft_print_status(data, "has taken a fork");
	sem_wait(data->data_of_philo->sem);
	ft_print_status(data, "has taken a fork");
	ft_print_status(data, "eating");
	sem_wait(data->data_of_philo->lock_eat_check);
	data->last_time_eating = get_time_in_ms(data->data_of_philo->start_time);
	data->n_diner++;
	sem_post(data->data_of_philo->lock_eat_check);
	ft_usleep(data, data->data_of_philo->tm_eat);
	sem_post(data->data_of_philo->sem);
	sem_post(data->data_of_philo->sem);
}

void	sleeping(t_philo_info *data)
{
	ft_print_status(data, "sleeping");
	ft_usleep(data, data->data_of_philo->tm_slp);
}

void	thinking(t_philo_info *data)
{
	ft_print_status(data, "thinking");
}

void	*shinigami(void *arg)
{
	t_philo_info	*data;
	int				count;

	data = (t_philo_info *)arg;
	while (1)
	{
		sem_wait(data->data_of_philo->lock_eat_check);
		if (data->flag)
		{
			sem_post(data->data_of_philo->lock_eat_check);
			sem_post(data->data_of_philo->sem_check);
			return (NULL);
		}
		if ((get_time_in_ms((data->data_of_philo->start_time)) - \
		(data->last_time_eating)) > (data->data_of_philo->tm_die))
		{
			count = -1;
			ft_print_status(data, "is died");
			while (++count < data->data_of_philo->nb_ph)
				sem_post(data->data_of_philo->sem_check);
			return (NULL);
		}
		sem_post(data->data_of_philo->lock_eat_check);
		usleep(100);
	}
}

void	routine(t_philo_info *data)
{
	pthread_t	tid;
	int			count;

	count = -1;
	while (++count < data->data_of_philo->nb_ph)
		sem_wait(data->data_of_philo->sem_check);
	pthread_create(&tid, NULL, &shinigami, data);
	while (1)
	{
		eating(data);
		if (data->data_of_philo->check)
		{
			sem_wait(data->data_of_philo->lock_eat_check);
			if (data->n_diner >= data->data_of_philo->nb_meal)
			{
				data->flag = 1;
				sem_post(data->data_of_philo->lock_eat_check);
				while (1)
					usleep(100000);
			}
			sem_post(data->data_of_philo->lock_eat_check);
		}
		sleeping(data);
		thinking(data);
	}
}
