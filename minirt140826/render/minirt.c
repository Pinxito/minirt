/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:08:40 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/10 17:25:42 by hcostoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
	{
		write(2, "Error\n", 6);
		write(2, "Usage: ./minirt <scene.rt>\n", 27);
		exit(1);
	}
	parse_scene(&scene, argv[1]);
	render_scene(&scene);
	mlx_loop(scene.mlx.mlx);
	return (0);
}
