/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_managment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 02:16:19 by oukhiar           #+#    #+#             */
/*   Updated: 2025/03/21 01:59:45 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	ft_print_status(t_philo_info *data, char *str)
{
	sem_wait(data->data_of_philo->lock_writing);
	printf("%lld %d %s\n", get_time_in_ms(data->data_of_philo->start_time), \
	data->id, str);
	if (ft_strncmp("is died", str, 7) == 0)
		return ;
	sem_post(data->data_of_philo->lock_writing);
}

long long	get_time_in_ms(long long start_time)
{
	struct timeval		tv;
	long long			m_sec;

	gettimeofday(&tv, NULL);
	m_sec = tv.tv_sec * 1000;
	m_sec += (tv.tv_usec / 1000);
	return (m_sec - start_time);
}

void	ft_usleep(t_philo_info *data, long long mls)
{
	long long	start;

	start = get_time_in_ms(data->data_of_philo->start_time);
	while (get_time_in_ms(data->data_of_philo->start_time) - start < mls)
		usleep(500);
}
