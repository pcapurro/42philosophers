/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:15:42 by pcapurro          #+#    #+#             */
/*   Updated: 2023/04/29 16:15:43 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void	ft_create_sub_arrays(char **array, char *s, int counter)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i != counter)
	{
		array[j] = ft_strdup(s + i);
		if (array[j] == NULL)
		{
			j = j - 1;
			while (j != -1)
				free(array[j--]);
			return (free(array));
		}
		j++;
		while (s[i] != '\0')
			i++;
		if (i != counter)
			i = i + 1;
	}
	array[j] = NULL;
}

char	**ft_split(char *s, char c)
{
	char	**array;
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			counter++;
		i++;
	}
	array = malloc(sizeof(char *) * (counter + 1 + 1));
	if (!array)
		return (NULL);
	i = 0;
	counter = ft_strlen(s);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			s[i] = '\0';
		i++;
	}
	ft_create_sub_arrays(array, s, counter);
	return (array);
}
