/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 10:00:09 by gguillen          #+#    #+#             */
/*   Updated: 2026/08/19 13:44:42 by edgar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_cylinder_bounds(t_cylinder cyl, t_vec3 point, double *height)
{
	t_vec3	pa;
	double	h;

	pa = vec3_sub(point, cyl.base);
	h = vec3_dot(pa, cyl.axis);
	if (h < 0.0 || h > cyl.height)
		return (0);
	*height = h;
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
}

static void	set_hit_cylinder(t_ray r, t_cylinder c, t_cyl_hit *i, t_hit *h)
{
	t_vec3	normal;

	h->t = i->t;
	h->point = vec3_add(r.origin, vec3_scale(r.dir, i->t));
	normal = vec3_sub(h->point, vec3_add(c.base,
				vec3_scale(c.axis, i->h)));
	h->normal = vec3_normalize(normal);
	h->color = c.color;
}

static int	check_valid_hit(t_ray r, t_cylinder c, double t, t_hit *h)
{
	t_cyl_hit	info;
	t_vec3		point;

	if (t > EPSILON)
	{
		point = vec3_add(r.origin, vec3_scale(r.dir, t));
		if (check_cylinder_bounds(c, point, &info.h))
		{
			info.t = t;
			set_hit_cylinder(r, c, &info, h);
			return (1);
		}
	}
	return (0);
}

int	ray_cylinder_intersect(t_ray ray, t_cylinder cyl, t_hit *hit)
{
	t_cyl_coef	coef;
	double		disc;
	double		sqrt_disc;
	double		t1;
	double		t2;

	calc_cylinder_coefficients(ray, cyl, &coef);
	if (coef.a < EPSILON)
		return (0);
	disc = coef.b * coef.b - 4.0 * coef.a * coef.c;
	if (disc < 0.0)
		return (0);
	sqrt_disc = sqrt(disc);
	t1 = (-coef.b - sqrt_disc) / (2.0 * coef.a);
	if (check_valid_hit(ray, cyl, t1, hit))
		return (1);
	t2 = (-coef.b + sqrt_disc) / (2.0 * coef.a);
	if (check_valid_hit(ray, cyl, t2, hit))
		return (1);
	return (0);
}
