/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:08:48 by gguillen          #+#    #+#             */
/*   Updated: 2026/08/19 13:36:05 by edgar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3_new(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3	vec3_normalize(t_vec3 v)
{
	double	len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len == 0)
		return (v);
	v.x /= len;
	v.y /= len;
	v.z /= len;
	return (v);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

t_vec3	vec3_reflect(t_vec3 incident, t_vec3 normal)

{
	double	factor;

	factor = 2.0 * (incident.x * normal.x + incident.y * normal.y
			+ incident.z * normal.z);
	return (vec3_new(incident.x - factor * normal.x,
			incident.y - factor * normal.y, incident.z - factor * normal.z));
}
