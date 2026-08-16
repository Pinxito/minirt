/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:51:57 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/14 12:51:59 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		ft_strlen_p(char *s);

void	parse_error(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen_p(msg));
	write(2, "\n", 1);
	exit(1);
}

int	ft_isspace_c(char c)
{
	return (c == ' ' || c == '\t' || c == '\r');
}

int	check_extension(char *file)
{
	int	len;

	len = 0;
	while (file[len])
		len++;
	if (len < 4)
		return (0);
	return (file[len - 3] == '.' && file[len - 2] == 'r'
		&& file[len - 1] == 't');
}

int	ft_strlen_p(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
