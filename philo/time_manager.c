/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 05:42:21 by oukhiar           #+#    #+#             */
/*   Updated: 2025/03/18 11:17:28 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_in_ms(void)
{
	struct timeval		tv;
	long long			m_sec;

	gettimeofday(&tv, NULL);
	m_sec = tv.tv_sec * 1000;
	m_sec += (tv.tv_usec / 1000);
	return (m_sec);
}

void	ft_usleep(t_philo_info *data, long long mls)
{
	long long	start;

	start = (get_time_in_ms() - data->date_of_birth);
	while ((get_time_in_ms() - data->date_of_birth) - start < mls)
	{
		pthread_mutex_lock(&(data->data_of_philo->wr_eat[1]));
		if (data->data_of_philo->philo_die)
		{
			pthread_mutex_unlock(&(data->data_of_philo->wr_eat[1]));
			return ;
		}
		pthread_mutex_unlock(&(data->data_of_philo->wr_eat[1]));
		usleep(500);
	}
}
