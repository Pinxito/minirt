/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:46:59 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/14 12:47:34 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	parse_double_sign(char *str, t_double_parse *parse)
{
	parse->i = 0;
	parse->sign = 1;
	parse->res = 0.0;
	parse->frac = 0.1;
	parse->has_dot = 0;
	if (str[parse->i] == '-')
	{
		parse->sign = -1;
		parse->i++;
	}
	else if (str[parse->i] == '+')
		parse->i++;
	if (!str[parse->i])
		return (0);
	return (1);
}

static int	process_double_char(char c, t_double_parse *parse)
{
	if (c >= '0' && c <= '9')
	{
		if (!parse->has_dot)
			parse->res = parse->res * 10.0 + (c - '0');
		else
		{
			parse->res += (c - '0') * parse->frac;
			parse->frac *= 0.1;
		}
	}
	else if (c == '.' && !parse->has_dot)
		parse->has_dot = 1;
	else
		return (0);
	return (1);
}

static int	parse_double_loop(char *str, t_double_parse *parse)
{
	while (str[parse->i])
	{
		if (!process_double_char(str[parse->i], parse))
			return (0);
		parse->i++;
	}
	return (1);
}

int	parse_double(char *str, double *out)
{
	t_double_parse	parse;

	if (!str || !str[0])
		return (0);
	if (!parse_double_sign(str, &parse))
		return (0);
	if (!parse_double_loop(str, &parse))
		return (0);
	*out = parse.res * parse.sign;
	return (1);
}
