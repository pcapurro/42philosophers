#include "../include/philo.h"

void	ft_destroy_everything(t_info *m_str)
{
	int	i;

	i = 0;
	while (m_str->mutex_table && i < m_str->philo_nb)
		if (pthread_mutex_destroy(&m_str->mutex_table[i++]) != 0)
			ft_putstr_fd("Error! A mutex could not be destroyed.\n", 2);
	i = 0;
	if (m_str->mutex_table)
		free(m_str->mutex_table);
	pthread_mutex_destroy(&m_str->global_auth);
	pthread_mutex_destroy(&m_str->print_auth);
	if (m_str->philo_array)
		free(m_str->philo_array);
}
