/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:33:41 by pcapurro          #+#    #+#             */
/*   Updated: 2024/09/25 13:33:44 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	ft_monitor_out(t_info *m_str)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	while (i < m_str->philo_nb)
	{
		if (m_str->philo_array[i].im_out != 0)
			value++;
		i++;
	}
	if (value == m_str->philo_nb)
		return (1);
	return (0);
}

int	ft_monitor_sim(t_info *m_str, pthread_t *philo_ids)
{
	if (ft_detach_philos(m_str, philo_ids) != 0)
		return (1);
	pthread_mutex_lock(&(m_str->global_auth));
	while (ft_monitor_out(m_str) == 0)
	{
		ft_all_knowing_checker(m_str);
		pthread_mutex_unlock(&(m_str->global_auth));
		usleep(25);
		pthread_mutex_lock(&(m_str->global_auth));
	}
	pthread_mutex_unlock(&(m_str->global_auth));
	return (0);
}

int	ft_all_knowing_checker(t_info *m_str)
{
	int		i;
	time_t	time;
	time_t	start_time;

	i = 0;
	time = ft_get_actual_time();
	start_time = m_str->philo_array[0].start_time;
	if (time == -1)
		return (m_str->end_status = 1);
	while (i < m_str->philo_nb)
	{
		if (m_str->philo_array[i].im_out == 0
			&& (time - m_str->philo_array[i].last_meal)
			>= m_str->time_to_die)
		{
			if (m_str->end_status != 1)
				printf("%ld (%d) died\n", (time - start_time), i + 1);
			m_str->end_status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
