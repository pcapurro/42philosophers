#include "../include/philo.h"

static int	ft_limit_checker(const char *s)
{
	int				i;
	long long int	result;

	i = 0;
	result = 0;
	while (s[i] >= 48 && s[i] <= 57)
	{
		result = (result * 10) + (s[i] - 48);
		i++;
	}
	if (i > 11 || result > 2147483647)
		return (1);
	return (0);
}

static char	*ft_get_in_one(int argc, char **argv)
{
	int		i;
	char	*str;

	i = 1;
	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (i != argc)
	{
		if (i != 1)
			str = ft_strjoin(str, " ");
		str = ft_strjoin(str, argv[i]);
		i++;
	}
	return (str);
}

static int	ft_verify_limits(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_limit_checker(str[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

static char	**ft_verify_consistency(char **str)
{
	if (ft_dstrlen(str) != 4 && ft_dstrlen(str) != 5)
	{
		ft_putstr_fd("Error!\nInvalid number of arguments.\n", 2);
		ft_free_double(str);
		return (NULL);
	}
	if (ft_verify_limits(str) != 0)
	{
		ft_putstr_fd("Error!\nInteger limit reached.\n", 2);
		ft_free_double(str);
		return (NULL);
	}
	if (ft_atoi(str[0]) == 0)
	{
		ft_putstr_fd("Error!\nZero philosophers set.\n", 2);
		ft_free_double(str);
		return (NULL);
	}
	return (str);
}

char	**ft_clean_input(int argc, char **argv)
{
	char	*input;
	char	**str;
	int		i;

	i = 0;
	input = ft_get_in_one(argc, argv);
	if (!input)
		return (ft_print_malloc_error());
	while (input[i] != '\0')
	{
		if ((input[i] < 48 || input[i] > 58) && input[i] != 32)
		{
			ft_putstr_fd("Error!\nInvalid input.\n", 2);
			free(input);
			return (NULL);
		}
		i++;
	}
	str = ft_split(input, ' ');
	free(input);
	if (str == NULL)
		return (ft_print_malloc_error());
	if (ft_verify_consistency(str) == NULL)
		return (NULL);
	return (str);
}
