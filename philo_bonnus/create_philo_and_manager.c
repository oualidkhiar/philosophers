/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo_and_manager.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 03:05:47 by oukhiar           #+#    #+#             */
/*   Updated: 2025/03/21 00:46:37 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sem_open(t_philo *life_routine)
{
	life_routine->sem = sem_open(SEM_NAME, O_CREAT \
	| O_EXCL, 0666, life_routine->nb_ph);
	life_routine->lock_writing = sem_open(SEM_WRITE_NAME, O_CREAT \
	| O_EXCL, 0666, 1);
	life_routine->sem_check = sem_open(SEM_CHECK_NAME, O_CREAT \
	| O_EXCL, 0666, life_routine->nb_ph * life_routine->nb_ph);
	life_routine->lock_eat_check = sem_open(SEM_EAT_NAME, O_CREAT \
	| O_EXCL, 0666, 1);
}

t_philo_info	*init_each_philo(int count, t_philo *life_routine)
{
	t_philo_info	*ret;

	ret = malloc(sizeof(t_philo_info));
	ret->data_of_philo = life_routine;
	ret->last_time_eating = 0;
	ret->n_diner = 0;
	ret->flag = 0;
	ret->id = count + 1;
	return (ret);
}

pid_t	*ft_do_philos(t_philo *life_routine)
{
	int				count;
	t_philo_info	*data;
	pid_t			*pid;

	count = 0;
	pid = malloc(sizeof(pid_t) * life_routine->nb_ph);
	while (count < life_routine->nb_ph)
	{
		pid[count] = fork();
		if (pid[count] == -1)
		{
			kill_all(pid, count);
			free(pid);
			free(life_routine);
			printf("fork faild\n");
			exit(1);
		}
		if (pid[count] == 0)
		{
			data = init_each_philo(count, life_routine);
			routine(data);
		}
		count++;
	}
	return (pid);
}

void	philo_manager(t_philo *life_routine)
{
	pid_t			*pid;
	int				count;

	count = -1;
	unlink_prev_semaphore();
	ft_sem_open(life_routine);
	pid = ft_do_philos(life_routine);
	usleep(10000);
	while (++count < life_routine->nb_ph)
		sem_wait(life_routine->sem_check);
	kill_all(pid, life_routine->nb_ph);
	ft_clean_semaphore(life_routine);
	free(pid);
}
