/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:13:47 by pcapurro          #+#    #+#             */
/*   Updated: 2023/04/29 16:13:49 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	*ft_print_malloc_error(void)
{
	ft_putstr_fd("Error! Memory allocation failed.\n", 2);
	return (NULL);
}

void	*ft_print_function_error(void)
{
	ft_putstr_fd("Error! A function failed.\n", 2);
	return (NULL);
}

void	ft_free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		free(str[i++]);
	free(str);
}

int	ft_dstrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}
