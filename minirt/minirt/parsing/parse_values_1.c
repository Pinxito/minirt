/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:51:16 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/14 12:51:17 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	parse_vec3_value(char *buf, double *value)
{
	if (!parse_double(buf, value))
		return (0);
	return (1);
}

static int	add_vec3_char(t_vec3_parse *p, char c)
{
	if (p->pos >= 127)
		return (0);
	p->buf[p->pos] = c;
	p->pos++;
	return (1);
}

static int	store_vec3_part(t_vec3_parse *p)
{
	p->buf[p->pos] = '\0';
	if (!parse_vec3_value(p->buf, &p->vals[p->part]))
		return (0);
	p->part++;
	p->pos = 0;
	return (1);
}

static int	handle_vec3_char(char c, t_vec3_parse *p)
{
	if (c == ',')
		return (store_vec3_part(p));
	return (add_vec3_char(p, c));
}

int	parse_vec3_components(char *str, double vals[3])
{
	t_vec3_parse	p;
	int				i;

	i = 0;
	p.part = 0;
	p.pos = 0;
	while (str[i] && p.part < 3)
	{
		if (!handle_vec3_char(str[i], &p))
			return (0);
		i++;
	}
	if (p.part != 2 || str[i] != '\0')
		return (0);
	p.buf[p.pos] = '\0';
	if (!parse_vec3_value(p.buf, &p.vals[2]))
		return (0);
	vals[0] = p.vals[0];
	vals[1] = p.vals[1];
	vals[2] = p.vals[2];
	return (1);
}
