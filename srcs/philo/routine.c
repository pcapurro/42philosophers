/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:34:11 by pcapurro          #+#    #+#             */
/*   Updated: 2023/05/01 19:34:12 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	ft_take_forks(t_philo_info *philo_str)
{
	ft_starve_if_necessary(philo_str);
	if (ft_simulation_state(philo_str) != 0)
		return ;
	if (philo_str->id % 2 != 0)
		pthread_mutex_lock(&philo_str->mutex_table[philo_str->l_fork]);
	else
		pthread_mutex_lock(&philo_str->mutex_table[philo_str->r_fork]);
	philo_str->forks_taken++;
	if (ft_print_state_change(philo_str, 1) == 1)
		return ;
	while (philo_str->r_fork == philo_str->l_fork)
		if (ft_simulation_state(philo_str) != 0)
			return ;
	if (philo_str->id % 2 != 0)
		pthread_mutex_lock(&philo_str->mutex_table[philo_str->r_fork]);
	else
		pthread_mutex_lock(&philo_str->mutex_table[philo_str->l_fork]);
	philo_str->forks_taken++;
	ft_print_state_change(philo_str, 1);
}

void	ft_eat(t_philo_info *philo_str)
{
	if (ft_simulation_state(philo_str) != 0)
		return ;
	pthread_mutex_lock(&philo_str->global_auth[0]);
	philo_str->last_meal = ft_get_actual_time();
	pthread_mutex_unlock(&philo_str->global_auth[0]);
	if (ft_print_state_change(philo_str, 2) == 1)
		return ;
	ft_freeze_thread(philo_str, (philo_str->time_to_eat * 1000));
	ft_release_forks(philo_str);
	philo_str->forks_taken = 0;
	philo_str->meals_nb++;
}

void	ft_sleep(t_philo_info *philo_str)
{
	if (ft_print_state_change(philo_str, 3) == 1)
		return ;
	ft_freeze_thread(philo_str, philo_str->time_to_sleep * 1000);
}

void	ft_think(t_philo_info *philo_str)
{
	if (ft_print_state_change(philo_str, 4) == 1)
		return ;
}

void	*ft_philosophize(void *old_philo_str)
{
	t_philo_info	*philo_str;

	philo_str = (t_philo_info *)old_philo_str;
	while (ft_simulation_state(philo_str) == 0)
	{
		ft_take_forks(philo_str);
		ft_eat(philo_str);
		ft_sleep(philo_str);
		ft_think(philo_str);
	}
	ft_release_forks(philo_str);
	pthread_mutex_lock(&philo_str->global_auth[0]);
	philo_str->im_out++;
	pthread_mutex_unlock(&philo_str->global_auth[0]);
	return (NULL);
}
