/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 23:31:28 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/10 17:27:05 by hcostoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	update_closest_hit(t_hit *hit, t_hit *temp_hit)
{
	if (temp_hit->t >= hit->t)
		return (0);
	*hit = *temp_hit;
	return (1);
}

static int	trace_sphere_object(t_object *obj, t_ray ray, t_hit *hit)
{
	t_sphere	*sphere;
	t_hit		temp_hit;

	sphere = (t_sphere *)obj->data;
	if (!ray_sphere_intersect(ray, *sphere, &temp_hit))
		return (0);
	return (update_closest_hit(hit, &temp_hit));
}

static int	trace_plane_object(t_object *obj, t_ray ray, t_hit *hit)
{
	t_plane	*plane;
	t_hit	temp_hit;

	plane = (t_plane *)obj->data;
	if (!ray_plane_intersect(ray, *plane, &temp_hit))
		return (0);
	return (update_closest_hit(hit, &temp_hit));
}

static int	trace_cylinder_object(t_object *obj, t_ray ray, t_hit *hit)
{
	t_cylinder	*cyl;
	t_hit		temp_hit;

	cyl = (t_cylinder *)obj->data;
	if (!ray_cylinder_intersect(ray, *cyl, &temp_hit))
		return (0);
	return (update_closest_hit(hit, &temp_hit));
}

int	trace_object(t_object *obj, t_ray ray, t_hit *hit)
{
	if (obj->type == OBJ_SPHERE)
		return (trace_sphere_object(obj, ray, hit));
	if (obj->type == OBJ_PLANE)
		return (trace_plane_object(obj, ray, hit));
	if (obj->type == OBJ_CYLINDER)
		return (trace_cylinder_object(obj, ray, hit));
	return (0);
}
