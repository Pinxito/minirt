/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 09:56:50 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/10 17:23:53 by hcostoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_in_shadow(t_scene *scene, t_vec3 p, t_vec3 normal)
{
	t_ray	ray;
	t_hit	hit;
	t_vec3	to_light;
	double	light_dist;

	to_light = vec3_sub(scene->light.pos, p);
	light_dist = sqrt(vec3_dot(to_light, to_light));
	ray.dir = vec3_normalize(to_light);
	if (vec3_dot(normal, ray.dir) < 0.0)
		normal = vec3_scale(normal, -1.0);
	ray.origin = vec3_add(p, vec3_scale(normal, EPSILON * 10.0));
	if (trace_ray(scene, ray, &hit) && hit.t > EPSILON && hit.t < light_dist)
		return (1);
	return (0);
}

int	lambert_modele(t_scene *scene, t_hit hit)
{
	t_light_info	li;
	t_vec3			l;
	int				r;
	int				g;
	int				b;

	l = vec3_sub(scene->light.pos, hit.point);
	l = vec3_normalize(l);
	li.diffuse = vec3_dot(hit.normal, l);
	if (li.diffuse < 0.0)
		li.diffuse = 0.0;
	li.intensity = scene->light.intensity * li.diffuse;
	li.ambient = scene->ambient.ratio;
	if (is_in_shadow(scene, hit.point, hit.normal))
		li.intensity = 0.0;
	r = ((hit.color >> 16) & 0xFF) * (li.intensity + li.ambient);
	g = ((hit.color >> 8) & 0xFF) * (li.intensity + li.ambient);
	b = (hit.color & 0xFF) * (li.intensity + li.ambient);
	r = clamp(r, 0, 255);
	g = clamp(g, 0, 255);
	b = clamp(b, 0, 255);
	return (create_trgb(0, r, g, b));
}
