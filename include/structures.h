/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:45:41 by pcapurro          #+#    #+#             */
/*   Updated: 2024/10/01 12:45:42 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo_info
{
	int				id;

	int				l_fork;
	int				r_fork;

	int				forks_taken;

	int				philo_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				notepme;

	int				meals_nb;

	time_t			last_meal;
	time_t			start_time;

	int				im_out;
	int				*end_status;

	pthread_mutex_t	*print_auth;
	pthread_mutex_t	*global_auth;
	pthread_mutex_t	*mutex_table;

}	t_philo_info;

typedef struct s_info
{
	int				philo_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				notepme;

	t_philo_info	*philo_array;

	int				end_status;

	pthread_mutex_t	print_auth;
	pthread_mutex_t	global_auth;
	pthread_mutex_t	*mutex_table;

}	t_info;

#endif