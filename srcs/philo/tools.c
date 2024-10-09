#include "../../include/philo.h"

void	ft_starve_if_necessary(t_philo_info *philo_str)
{
	if (philo_str->philo_nb % 2 != 0 && philo_str->time_to_eat
		* (philo_str->philo_nb + 1) >= philo_str->time_to_die
		&& philo_str->meals_nb > 0)
	{
		while (ft_get_actual_time() - philo_str->last_meal
			< philo_str->time_to_die - 10)
		{
			if (ft_simulation_state(philo_str) != 0)
				return ;
		}
	}
}

int	ft_simulation_state(t_philo_info *philo_str)
{
	pthread_mutex_lock(&philo_str->global_auth[0]);
	if (*(philo_str->end_status) == 1)
	{
		pthread_mutex_unlock(&philo_str->global_auth[0]);
		return (1);
	}
	pthread_mutex_unlock(&philo_str->global_auth[0]);
	if (philo_str->notepme != 0)
	{
		if (philo_str->meals_nb == philo_str->notepme)
			return (1);
	}
	return (0);
}

void	ft_release_forks(t_philo_info *philo_str)
{
	if (philo_str->forks_taken == 1 || philo_str->forks_taken == 2)
	{
		if (philo_str->id % 2 != 0)
			pthread_mutex_unlock(&philo_str->mutex_table[philo_str->l_fork]);
		else
			pthread_mutex_unlock(&philo_str->mutex_table[philo_str->r_fork]);
	}
	if (philo_str->forks_taken == 2)
	{
		if (philo_str->id % 2 != 0)
			pthread_mutex_unlock(&philo_str->mutex_table[philo_str->r_fork]);
		else
			pthread_mutex_unlock(&philo_str->mutex_table[philo_str->l_fork]);
	}
}

int	ft_freeze_thread(t_philo_info *philo_str, int time)
{
	time_t	start_timestamp;
	time_t	actual_timestamp;

	pthread_mutex_lock(&*(philo_str->global_auth));
	start_timestamp = ft_get_actual_time() * 1000;
	actual_timestamp = ft_get_actual_time() * 1000;
	while (*(philo_str->end_status) != 1)
	{
		if (actual_timestamp - start_timestamp >= time)
			break ;
		pthread_mutex_unlock(&*(philo_str->global_auth));
		usleep(25);
		actual_timestamp = ft_get_actual_time() * 1000;
		pthread_mutex_lock(&*(philo_str->global_auth));
	}
	pthread_mutex_unlock(&*(philo_str->global_auth));
	return (0);
}

int	ft_print_state_change(t_philo_info *philo_str, int nb)
{
	time_t	time;
	time_t	timestamp;

	time = ft_get_actual_time();
	timestamp = time - philo_str->start_time;
	pthread_mutex_lock(&*(philo_str->print_auth));
	if (ft_simulation_state(philo_str) == 0)
	{
		if (nb == 1)
			printf("%ld (%d) has taken a fork\n", timestamp, philo_str->id);
		if (nb == 2)
			printf("%ld (%d) is eating\n", timestamp, philo_str->id);
		if (nb == 3)
			printf("%ld (%d) is sleeping\n", timestamp, philo_str->id);
		if (nb == 4)
			printf("%ld (%d) is thinking\n", timestamp, philo_str->id);
	}
	else
	{
		pthread_mutex_unlock(&*(philo_str->print_auth));
		return (1);
	}
	pthread_mutex_unlock(&*(philo_str->print_auth));
	return (0);
}
