/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 10:00:09 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/14 12:47:43 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_cylinder_bounds(t_cylinder cyl, t_vec3 point, double *height)
{
	t_vec3	pa;
	double	h;

	pa = vec3_sub(point, cyl.base);
	h = vec3_dot(pa, cyl.axis);
	if (h < 0 || h > cyl.height)
		return (0);
	*height = h;
	return (1);
}

static int	solve_cylinder_quadratic(double b, double c, double *t)
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

static void	calc_cylinder_coefficients(t_ray ray, t_cylinder cyl,
		t_cyl_coef *coef)
{
	t_vec3	oc;
	t_vec3	cross_prod;

	oc = vec3_sub(ray.origin, cyl.base);
	cross_prod = vec3_cross(ray.dir, cyl.axis);
	coef->a = vec3_dot(cross_prod, cross_prod);
	coef->b = 2.0 * vec3_dot(vec3_cross(oc, cyl.axis), cross_prod);
	coef->c = vec3_dot(vec3_cross(oc, cyl.axis), vec3_cross(oc, cyl.axis))
		- cyl.radius * cyl.radius;
	coef->b /= coef->a;
	coef->c /= coef->a;
}

static void	set_hit_cylinder(t_ray ray, t_cylinder cyl, t_cyl_hit *info,
		t_hit *hit)
{
	t_vec3	normal;

	hit->t = info->t;
	hit->point = vec3_add(ray.origin, vec3_scale(ray.dir, info->t));
	normal = vec3_sub(hit->point, vec3_add(cyl.base,
				vec3_scale(cyl.axis, info->h)));
	hit->normal = vec3_normalize(normal);
	hit->color = cyl.color;
}

int	ray_cylinder_intersect(t_ray ray, t_cylinder cyl, t_hit *hit)
{
	t_cyl_coef	coef;
	t_cyl_hit	info;
	t_vec3		point;

	calc_cylinder_coefficients(ray, cyl, &coef);
	if (coef.a < EPSILON)
		return (0);
	if (!solve_cylinder_quadratic(coef.b / 2.0, coef.c, &info.t))
		return (0);
	point = vec3_add(ray.origin, vec3_scale(ray.dir, info.t));
	if (!check_cylinder_bounds(cyl, point, &info.h))
		return (0);
	set_hit_cylinder(ray, cyl, &info, hit);
	return (1);
}
