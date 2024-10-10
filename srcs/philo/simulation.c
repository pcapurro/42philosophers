#include "../../include/philo.h"

time_t	ft_get_actual_time(void)
{
	struct timeval	time;
	time_t			actual_time;

	if (gettimeofday(&time, NULL) == -1)
	{
		ft_print_function_error();
		return (-1);
	}
	actual_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (actual_time);
}

int	ft_detach_philos(t_info *m_str, pthread_t *philo_ids)
{
	int	i;

	i = 0;
	while (i < m_str->philo_nb)
	{
		if (pthread_detach(philo_ids[i++]) != 0)
		{
			sem_wait(m_str->global_auth);
			m_str->end_status = 1;
			sem_post(m_str->global_auth);
			ft_putstr_fd("Error! A thread detachment failed.\n", 2);
			return (1);
		}
	}
	free(philo_ids);
	return (0);
}

void	ft_load_time(t_info *m_str)
{
	int		i;
	time_t	time;

	i = 0;
	time = ft_get_actual_time();
	while (i < m_str->philo_nb)
	{
		m_str->philo_array[i].start_time = time;
		m_str->philo_array[i].last_meal = time;
		i++;
	}
}

int	ft_init_sim(t_info *m_str)
{
	int			i;
	pthread_t	*philo_ids;

	i = 0;
	philo_ids = malloc(sizeof(pthread_t) * m_str->philo_nb);
	if (!philo_ids || ft_init_philo_data(m_str) != 0)
		return (1);
	while (i < m_str->philo_nb)
	{
		if (pthread_create(&philo_ids[i], NULL, ft_philosophize,
				&m_str->philo_array[i]) != 0)
		{
			sem_wait(m_str->global_auth);
			m_str->end_status = 1;
			sem_post(m_str->global_auth);
			ft_putstr_fd("Error! A thread creation failed.\n", 2);
			return (1);
		}
		i++;
	}
	ft_load_time(m_str);
	pthread_barrier_wait(m_str->top_start);
	return (ft_monitor_sim(m_str, philo_ids));
}
