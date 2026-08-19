/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 08:34:31 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/10 17:25:28 by hcostoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	solve_sphere_quadratic(double b, double c, double *t)
{
	double	discriminant;
	double	t1;
	double	t2;

	discriminant = b * b - c;
	if (discriminant < 0)
		return (0);
	t1 = -b - sqrt(discriminant);
	t2 = -b + sqrt(discriminant);
	if (t1 > EPSILON)
		*t = t1;
	else if (t2 > EPSILON)
		*t = t2;
	else
		return (0);
	return (1);
}

int	ray_sphere_intersect(t_ray ray, t_sphere sphere, t_hit *hit)
{
	t_vec3	oc;
	double	b;
	double	c;
	double	t;

	oc = vec3_sub(ray.origin, sphere.center);
	b = vec3_dot(oc, ray.dir);
	c = vec3_dot(oc, oc) - sphere.radius * sphere.radius;
	if (!solve_sphere_quadratic(b, c, &t))
		return (0);
	hit->t = t;
	hit->point = vec3_add(ray.origin, vec3_scale(ray.dir, t - EPSILON));
	hit->normal = vec3_normalize(vec3_sub(hit->point, sphere.center));
	hit->color = sphere.color;
	return (1);
}
