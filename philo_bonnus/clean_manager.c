/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 02:22:32 by oukhiar           #+#    #+#             */
/*   Updated: 2025/03/21 00:45:52 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all(pid_t *pid, int how_much)
{
	int	count;

	count = 0;
	while (count < how_much)
	{
		kill(pid[count], SIGKILL);
		count++;
	}
}

void	unlink_prev_semaphore(void)
{
	sem_unlink(SEM_CHECK_NAME);
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_WRITE_NAME);
	sem_unlink(SEM_EAT_NAME);
}

void	ft_clean_semaphore(t_philo *life_routine)
{
	sem_close(life_routine->sem_check);
	sem_close(life_routine->sem);
	sem_close(life_routine->lock_writing);
	sem_close(life_routine->lock_eat_check);
	sem_destroy(life_routine->sem_check);
	sem_destroy(life_routine->sem);
	sem_destroy(life_routine->lock_writing);
	sem_destroy(life_routine->lock_eat_check);
	sem_unlink(SEM_CHECK_NAME);
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_WRITE_NAME);
	sem_unlink(SEM_EAT_NAME);
}
