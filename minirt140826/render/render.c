/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 23:31:28 by gguillen          #+#    #+#             */
/*   Updated: 2026/01/23 16:27:22 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_scene(t_scene *scene)
{
	int		x;
	int		y;
	int		color;
	t_ray	ray;
	t_hit	hit;

	prepare_render_scene(scene);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = generate_ray(scene->camera, x, y);
			if (trace_ray(scene, ray, &hit))
				color = lambert_modele(scene, hit);
			else
				color = create_trgb(0, 0, 0, 0);
			put_pixel_to_image(&scene->mlx, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win, scene->mlx.img, 0,
		0);
}

void	prepare_render_scene(t_scene *scene)
{
	if (scene->mlx.img)
		mlx_destroy_image(scene->mlx.mlx, scene->mlx.img);
	scene->mlx.img = mlx_new_image(scene->mlx.mlx, WIDTH, HEIGHT);
	scene->mlx.addr = mlx_get_data_addr(scene->mlx.img, &scene->mlx.bpp,
			&scene->mlx.line_length, &scene->mlx.endian);
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

int	trace_ray(t_scene *scene, t_ray ray, t_hit *hit)
{
	t_object	*obj;
	int			found;

	obj = scene->objects;
	found = 0;
	hit->t = 1e30;
	while (obj)
	{
		if (trace_object(obj, ray, hit))
			found = 1;
		obj = obj->next;
	}
	return (found);
}
