/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:51:01 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/14 12:51:02 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_vec3(char *str, t_vec3 *v)
{
	double	vals[3];

	if (!parse_vec3_components(str, vals))
		return (0);
	v->x = vals[0];
	v->y = vals[1];
	v->z = vals[2];
	return (1);
}

static int	is_normalized(t_vec3 v)
{
	double	len2;

	len2 = v.x * v.x + v.y * v.y + v.z * v.z;
	if (len2 < NORM_TOL * NORM_TOL)
		return (0);
	if (len2 < (1.0 - NORM_TOL) * (1.0 - NORM_TOL))
		return (0);
	if (len2 > (1.0 + NORM_TOL) * (1.0 + NORM_TOL))
		return (0);
	return (1);
}

int	parse_norm_vec3(char *str, t_vec3 *v)
{
	if (!parse_vec3(str, v))
		return (0);
	if (!is_normalized(*v))
		return (0);
	return (1);
}
