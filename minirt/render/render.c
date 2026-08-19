/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 23:31:28 by gguillen          #+#    #+#             */
/*   Updated: 2026/08/17 15:21:47 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	sky_color(t_ray ray)

{
	double	t;
	int		r;
	int		g;
	int		b;

	t = 0.5 * (ray.dir.y + 1.0);
	r = (int)((1.0 - t) * 255 + t * 135);
	g = (int)((1.0 - t) * 255 + t * 206);
	b = (int)((1.0 - t) * 255 + t * 250);
	return (create_trgb(0, r, g, b));
}

static void	render_pixel(t_scene *scene, int x, int y)
{
	t_ray	ray;
	t_hit	hit;
	int		color;

	ray = generate_ray(scene->camera, x, y);
	if (trace_ray(scene, ray, &hit))
		color = lambert_modele(scene, hit);
	else
		color = sky_color(ray);
	put_pixel_to_image(&scene->mlx, x, y, color);
}

void	render_scene(t_scene *scene)
{
	int	x;
	int	y;

	prepare_render_scene(scene);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_pixel(scene, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win,
		scene->mlx.img, 0, 0);
}

void	prepare_render_scene(t_scene *scene)
{
	if (scene->mlx.img)
		mlx_destroy_image(scene->mlx.mlx, scene->mlx.img);
	scene->mlx.img = mlx_new_image(scene->mlx.mlx, WIDTH, HEIGHT);
	scene->mlx.addr = mlx_get_data_addr(scene->mlx.img, &scene->mlx.bpp,
			&scene->mlx.line_length, &scene->mlx.endian);
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
