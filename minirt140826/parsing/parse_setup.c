/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:52:13 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/14 12:52:14 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	expose_hook(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	render_scene(scene);
	return (0);
}

static int	loop_hook(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	render_scene(scene);
	return (0);
}

static int	key_hook(int keycode, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keycode == 65307)
		close_window(scene);
	return (0);
}

static int	init_mlx(t_scene *scene)
{
	scene->mlx.mlx = mlx_init();
	if (!scene->mlx.mlx)
		return (0);
	scene->mlx.win = mlx_new_window(scene->mlx.mlx, WIDTH, HEIGHT, "miniRT");
	if (!scene->mlx.win)
		return (0);
	scene->mlx.img = NULL;
	mlx_hook(scene->mlx.win, 17, 0, close_window, scene);
	mlx_key_hook(scene->mlx.win, key_hook, scene);
	mlx_expose_hook(scene->mlx.win, expose_hook, scene);
	mlx_loop_hook(scene->mlx.mlx, loop_hook, scene);
	return (1);
}

int	setup_scene(t_scene *scene, t_parse_flags *flags, char *file)
{
	(void)file;
	if (!flags->has_ambient)
		parse_error("Missing ambient light (A)");
	if (!flags->has_camera)
		parse_error("Missing camera (C)");
	if (!flags->has_light)
		parse_error("Missing light (L)");
	init_camera_basis(&scene->camera);
	if (!init_mlx(scene))
	{
		free_scene_full(scene);
		parse_error("MinilibX initialization failed");
	}
	return (1);
}
