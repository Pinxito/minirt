/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:50:43 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/14 12:50:44 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	parse_int_strict(char *str, int *out)
{
	int	res;
	int	i;

	if (!str || !str[0])
		return (0);
	res = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	*out = res;
	return (1);
}

static int	parse_rgb_value(char *buf, int *value)
{
	if (!parse_int_strict(buf, value) || *value > 255)
		return (0);
	return (1);
}

static int	store_rgb_part(t_rgb_parse *p)
{
	p->buf[p->pos] = '\0';
	if (!parse_rgb_value(p->buf, &p->vals[p->part]))
		return (0);
	p->part++;
	p->pos = 0;
	return (1);
}

static int	handle_rgb_char(char c, t_rgb_parse *p)
{
	if (c == ',')
		return (store_rgb_part(p));
	if (p->pos >= 7)
		return (0);
	p->buf[p->pos] = c;
	p->pos++;
	return (1);
}

int	parse_rgb_components(char *str, int vals[3])
{
	t_rgb_parse	p;
	int			i;

	i = 0;
	p.part = 0;
	p.pos = 0;
	while (str[i] && p.part < 3)
	{
		if (!handle_rgb_char(str[i], &p))
			return (0);
		i++;
	}
	if (p.part != 2 || str[i] != '\0')
		return (0);
	p.buf[p.pos] = '\0';
	if (!parse_rgb_value(p.buf, &p.vals[2]))
		return (0);
	vals[0] = p.vals[0];
	vals[1] = p.vals[1];
	vals[2] = p.vals[2];
	return (1);
}
