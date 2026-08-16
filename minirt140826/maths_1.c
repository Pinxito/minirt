/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:08:48 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/14 12:47:55 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	r;

	r.x = a.x - b.x;
	r.y = a.y - b.y;
	r.z = a.z - b.z;
	return (r);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	r;

	r.x = a.x + b.x;
	r.y = a.y + b.y;
	r.z = a.z + b.z;
	return (r);
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_scale(t_vec3 v, double s)
{
	t_vec3	r;

	r.x = v.x * s;
	r.y = v.y * s;
	r.z = v.z * s;
	return (r);
}
