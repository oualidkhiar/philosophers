/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:29:09 by oukhiar           #+#    #+#             */
/*   Updated: 2025/03/21 00:50:17 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <string.h>
# include <sys/wait.h>

# define SEM_NAME "/forks_philos"
# define SEM_CHECK_NAME "/checker_die_sem"
# define SEM_WRITE_NAME "/sem_write"
# define SEM_EAT_NAME "/sem_eat_check"

typedef struct s_philo
{
	int				nb_ph;
	int				tm_die;
	int				tm_eat;
	int				nb_meal;
	int				tm_slp;
	int				check;
	long long		start_time;
	sem_t			*sem_check;
	sem_t			*sem;
	sem_t			*lock_writing;
	sem_t			*lock_eat_check;
}	t_philo;

typedef struct s_philo_info
{
	int				id;
	int				n_diner;
	int				flag;
	long long		last_time_eating;
	t_philo			*data_of_philo;
}	t_philo_info;

void		ft_putstr_fd(int fd, char *str);
int			ft_atoi(const char *str);
int			ft_error(int flag);
int			check_is_digit(char **av);
long long	get_time_in_ms(long long start_time);
void		ft_print_status(t_philo_info *data, char *str);
void		ft_usleep(t_philo_info *data, long long mls);
void		eating(t_philo_info *data);
void		sleeping(t_philo_info *data);
void		thinking(t_philo_info *data);
void		*shinigami(void *arg);
void		routine(t_philo_info *data);
void		kill_all(pid_t *pid, int how_much);
void		ft_clean_semaphore(t_philo *life_routine);
void		philo_manager(t_philo *life_routine);
void		unlink_prev_semaphore(void);
#endif