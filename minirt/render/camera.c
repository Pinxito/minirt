/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:00:36 by gguillen          #+#    #+#             */
/*   Updated: 2026/01/23 18:14:17 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_camera_basis(t_camera *camera)
{
	t_vec3	up_world;

	camera->forward = vec3_normalize(camera->dir);
	if (fabs(camera->forward.y) > 0.999)
		up_world = vec3_new(0.0, 0.0, 1.0);
	else
		up_world = vec3_new(0.0, 1.0, 0.0);
	camera->right = vec3_normalize(vec3_cross(camera->forward, up_world));
	camera->up = vec3_cross(camera->right, camera->forward);
}

t_ray	generate_ray(t_camera camera, int i, int j)
{
	t_ray	ray;
	double	u;
	double	v;
	double	tan_half_fov;

	u = (2.0 * (i + 0.5) / WIDTH - 1.0) * ((double)WIDTH / HEIGHT);
	v = 1.0 - 2.0 * (j + 0.5) / HEIGHT;
	tan_half_fov = tan(camera.fov * 0.5 * M_PI / 180.0);
	ray.origin = camera.pos;
	ray.dir = vec3_new(camera.forward.x + u * tan_half_fov * camera.right.x + v
			* tan_half_fov * camera.up.x, camera.forward.y + u * tan_half_fov
			* camera.right.y + v * tan_half_fov * camera.up.y, camera.forward.z
			+ u * tan_half_fov * camera.right.z + v * tan_half_fov
			* camera.up.z);
	ray.dir = vec3_normalize(ray.dir);
	return (ray);
}
