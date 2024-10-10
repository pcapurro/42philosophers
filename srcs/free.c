#include "../include/philo.h"

void	ft_destroy_everything(t_info *m_str)
{
	int	i;

	i = 0;
	while (m_str->mutex_table != NULL && i < m_str->philo_nb)
		if (pthread_mutex_destroy(&m_str->mutex_table[i++]) != 0)
			ft_putstr_fd("Error! A mutex could not be destroyed.\n", 2);
	if (m_str->mutex_table != NULL)
		free(m_str->mutex_table);
	if (m_str->top_start != NULL)
	{
		pthread_barrier_destroy(m_str->top_start);
		free(m_str->top_start);
	}
	if (m_str->global_auth != NULL)
	{
		sem_close(m_str->global_auth);
		sem_unlink("/global");
	}
	if (m_str->print_auth != NULL)
	{
		sem_close(m_str->print_auth);
		sem_unlink("/print");
	}
	if (m_str->philo_array != NULL)
		free(m_str->philo_array);
	free(m_str);
}
