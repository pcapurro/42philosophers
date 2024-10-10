#include "../../include/philo.h"

void	*ft_init_mutex_table(t_info *m_str)
{
	int				i;
	pthread_mutex_t	*f_table;

	i = m_str->philo_nb;
	f_table = malloc(sizeof(pthread_mutex_t) * i);
	if (!f_table)
		return (ft_print_malloc_error());
	i--;
	while (i >= 0)
	{
		if (pthread_mutex_init(&f_table[i--], NULL) != 0)
		{
			m_str->mutex_table = NULL;
			i++;
			while (i < m_str->philo_nb)
				pthread_mutex_destroy(&f_table[i++]);
			free(f_table);
			return (NULL);
		}
	}
	m_str->mutex_table = f_table;
	return (f_table);
}

static void	ft_put_basic_values(t_philo_info *philo_str, t_info *m_str)
{
	philo_str->time_to_die = m_str->time_to_die;
	philo_str->time_to_eat = m_str->time_to_eat;
	philo_str->time_to_sleep = m_str->time_to_sleep;
	philo_str->notepme = m_str->notepme;
	philo_str->philo_nb = m_str->philo_nb;
	philo_str->mutex_table = m_str->mutex_table;
	philo_str->end_status = &(m_str->end_status);
	philo_str->im_out = 0;
	philo_str->meals_nb = 0;
	philo_str->global_auth = m_str->global_auth;
	philo_str->print_auth = m_str->print_auth;
	philo_str->top_start = m_str->top_start;
	philo_str->forks_taken = 0;
	if (philo_str->id == m_str->philo_nb)
		philo_str->r_fork = 0;
	else
		philo_str->r_fork = philo_str->id;
	philo_str->l_fork = philo_str->id - 1;
}

void	*ft_init_philo_strs(t_info *m_str)
{
	int				i;
	t_philo_info	*philo_array;

	i = 0;
	philo_array = malloc(sizeof(t_philo_info) * m_str->philo_nb);
	if (!philo_array)
		return (ft_print_malloc_error());
	while (i < m_str->philo_nb)
	{
		philo_array[i].id = i + 1;
		ft_put_basic_values(&philo_array[i], m_str);
		i++;
	}
	m_str->philo_array = philo_array;
	return (philo_array);
}

void	ft_init_semaphores(t_info *m_str)
{
	m_str->print_auth = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	if (m_str->print_auth == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			sem_close(m_str->print_auth);
			sem_unlink("/print");
			m_str->print_auth = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
		}
	}
	if (m_str->print_auth == SEM_FAILED)
		m_str->print_auth = NULL;
	m_str->global_auth = sem_open("/global", O_CREAT | O_EXCL, 0644, 1);
	if (m_str->global_auth == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			sem_close(m_str->global_auth);
			sem_unlink("/global");
			m_str->global_auth = sem_open("/global", O_CREAT | O_EXCL, 0644, 1);
		}
	}
	if (m_str->global_auth == SEM_FAILED)
		m_str->global_auth = NULL;
}

void	ft_init_barrier(t_info *m_str)
{
	m_str->top_start = malloc(sizeof(pthread_barrier_t));
	if (!m_str->top_start)
	{
		m_str->top_start = NULL;
		ft_print_malloc_error();
		return ;
	}
	if (pthread_barrier_init(m_str->top_start, NULL, m_str->philo_nb + 1) != 0)
	{
		ft_putstr_fd("Error! A barrier initialization failed.\n", 2);
		return ;
	}
}

int	ft_init_philo_data(t_info *m_str)
{
	ft_init_semaphores(m_str);
	if (m_str->global_auth == NULL || m_str->print_auth == NULL)
	{
		ft_putstr_fd("Error! A semaphore initialization failed.\n", 2);
		return (1);
	}
	if (ft_init_mutex_table(m_str) == NULL)
	{
		ft_putstr_fd("Error! A mutex initialization failed.\n", 2);
		return (1);
	}
	ft_init_barrier(m_str);
	if (m_str->top_start == NULL)
		return (1);
	if (ft_init_philo_strs(m_str) == NULL)
		return (1);
	return (0);
}
