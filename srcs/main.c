#include "../include/philo.h"

void	ft_init_struct(t_info *m_str, char **args)
{
	m_str->philo_nb = ft_atoi(args[0]);
	m_str->time_to_die = ft_atoi(args[1]);
	m_str->time_to_eat = ft_atoi(args[2]);
	m_str->time_to_sleep = ft_atoi(args[3]);
	if (args[4] == NULL)
		m_str->notepme = 0;
	else
		m_str->notepme = ft_atoi(args[4]);
	m_str->end_status = 0;
	m_str->philo_array = NULL;
	m_str->mutex_table = NULL;
	m_str->print_auth = NULL;
	m_str->global_auth = NULL;
	m_str->top_start = NULL;
}

int	main(int argc, char **argv)
{
	t_info	*m_str;
	char	**args;

	args = ft_clean_input(argc, argv);
	if (args == NULL)
		return (1);
	if (!args[4] || ft_atoi(args[4]) != 0)
	{
		m_str = malloc(sizeof(t_info));
		if (!m_str)
		{
			ft_print_malloc_error();
			ft_free_double(args);
			return (1);
		}
		ft_init_struct(m_str, args);
		if (ft_init_sim(m_str) != 0)
		{
			ft_destroy_everything(m_str);
			ft_free_double(args);
			return (1);
		}
		ft_destroy_everything(m_str);
	}
	ft_free_double(args);
	return (0);
}
