/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 09:56:50 by gguillen          #+#    #+#             */
/*   Updated: 2026/08/16 17:44:54 by gguillen         ###   ########.fr       */
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

static double	compute_specular(t_scene *scene, t_hit hit, t_vec3 l)
{
	t_vec3	view;
	t_vec3	reflected;
	double	spec_dot;

	view = vec3_normalize(vec3_sub(scene->camera.pos, hit.point));
	reflected = vec3_reflect(vec3_scale(l, -1.0), hit.normal);
	spec_dot = vec3_dot(reflected, view);
	if (spec_dot < 0.0)
		return (0.0);
	return (pow(spec_dot, SHININESS) * scene->light.intensity);
}

static void	compute_light_info(t_scene *scene, t_hit hit, t_vec3 l,
		t_light_info *li)
{
	li->diffuse = vec3_dot(hit.normal, l);
	if (li->diffuse < 0.0)
		li->diffuse = 0.0;
	li->ambient = scene->ambient.ratio;
	li->intensity = scene->light.intensity * li->diffuse;
	li->specular = compute_specular(scene, hit, l);
	if (is_in_shadow(scene, hit.point, hit.normal))
	{
		li->intensity = 0.0;
		li->specular = 0.0;
	}
}

int	lambert_modele(t_scene *scene, t_hit hit)
{
	t_light_info	li;
	t_vec3			l;
	int				r;
	int				g;
	int				b;

	l = vec3_normalize(vec3_sub(scene->light.pos, hit.point));
	compute_light_info(scene, hit, l, &li);
	r = ((hit.color >> 16) & 0xFF) * (li.intensity + li.ambient) + 255
		* li.specular;
	g = ((hit.color >> 8) & 0xFF) * (li.intensity + li.ambient) + 255
		* li.specular;
	b = (hit.color & 0xFF) * (li.intensity + li.ambient) + 255 * li.specular;
	r = clamp(r, 0, 255);
	g = clamp(g, 0, 255);
	b = clamp(b, 0, 255);
	return (create_trgb(0, r, g, b));
}
