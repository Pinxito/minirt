/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 09:59:57 by gguillen          #+#    #+#             */
/*   Updated: 2026/08/17 16:19:07 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ray_plane_intersect(t_ray ray, t_plane plane, t_hit *hit)
{
	double	denom;
	double	t;
	t_vec3	oc;

	denom = vec3_dot(plane.normal, ray.dir);
	if (denom > -EPSILON && denom < EPSILON)
		return (0);
	oc = vec3_sub(plane.point, ray.origin);
	t = vec3_dot(oc, plane.normal) / denom;
	if (t < EPSILON)
		return (0);
	hit->t = t;
	hit->point = vec3_add(ray.origin, vec3_scale(ray.dir, t));
	if (denom < 0)
		hit->normal = plane.normal;
	else
		hit->normal = vec3_scale(plane.normal, -1.0);
	hit->color = plane.color;
	return (1);
}
