/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:48:16 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/14 12:48:17 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	free_mlx_resources(t_scene *scene)
{
	if (!scene || !scene->mlx.mlx)
		return ;
	if (scene->mlx.img)
		mlx_destroy_image(scene->mlx.mlx, scene->mlx.img);
	if (scene->mlx.win)
		mlx_destroy_window(scene->mlx.mlx, scene->mlx.win);
	if (scene->mlx.mlx)
		mlx_destroy_display(scene->mlx.mlx);
	free(scene->mlx.mlx);
	scene->mlx.img = NULL;
	scene->mlx.win = NULL;
	scene->mlx.addr = NULL;
	scene->mlx.mlx = NULL;
}

void	free_scene_objects(t_scene *scene)
{
	t_object	*cur;
	t_object	*next;

	if (!scene)
		return ;
	cur = scene->objects;
	while (cur)
	{
		next = cur->next;
		if (cur->data)
			free(cur->data);
		free(cur);
		cur = next;
	}
	scene->objects = NULL;
}

void	free_scene_full(t_scene *scene)
{
	free_mlx_resources(scene);
	free_scene_objects(scene);
}
