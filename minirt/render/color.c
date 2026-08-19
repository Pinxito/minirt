/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 22:02:48 by gguillen          #+#    #+#             */
/*   Updated: 2026/08/16 09:37:40 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

void	put_pixel_to_image(t_mlx *mlx_struct, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = mlx_struct->addr + (y * mlx_struct->line_length + x * (mlx_struct->bpp
				/ 8));
	*(unsigned int *)dst = color;
}

int	get_pixel_color(int r, int g, int b, t_light_info *t_light_info)
{
	int	ri;
	int	gi;
	int	bi;

	ri = (int)(r * t_light_info->diffuse * t_light_info->intensity);
	gi = (int)(g * t_light_info->diffuse * t_light_info->intensity);
	bi = (int)(b * t_light_info->diffuse * t_light_info->intensity);
	ri = clamp(ri, 0, 255);
	gi = clamp(gi, 0, 255);
	bi = clamp(bi, 0, 255);
	return (create_trgb(0, ri, gi, bi));
}

int	close_window(t_scene *scene)
{
	if (scene && scene->mlx.mlx)
		mlx_loop_end(scene->mlx.mlx);
	return (0);
}
