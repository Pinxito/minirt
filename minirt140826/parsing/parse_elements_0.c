/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:52:59 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/14 12:53:01 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_ambient(t_scene *scene, t_parse_flags *flags, char **fields,
		int nfields)
{
	if (flags->has_ambient)
		parse_error("Ambient light declared more than once");
	if (nfields != 3)
		parse_error("Invalid ambient light format");
	if (!parse_ratio(fields[1], &scene->ambient.ratio))
		parse_error("Invalid ambient ratio (must be in [0.0, 1.0])");
	if (!parse_rgb(fields[2], &scene->ambient.color))
		parse_error("Invalid ambient RGB value");
	flags->has_ambient = 1;
	return (1);
}

int	parse_camera(t_scene *scene, t_parse_flags *flags, char **fields,
		int nfields)
{
	double	fov;

	if (flags->has_camera)
		parse_error("Camera declared more than once");
	if (nfields != 4)
		parse_error("Invalid camera format");
	if (!parse_vec3(fields[1], &scene->camera.pos))
		parse_error("Invalid camera position");
	if (!parse_norm_vec3(fields[2], &scene->camera.dir))
		parse_error("Invalid camera orientation (must be unit vector)");
	if (!parse_double(fields[3], &fov) || fov < 0.0 || fov > 180.0)
		parse_error("Invalid camera FOV (must be in [0, 180])");
	scene->camera.fov = fov;
	flags->has_camera = 1;
	return (1);
}

int	parse_light(t_scene *scene, t_parse_flags *flags, char **fields,
		int nfields)
{
	int	dummy_color;

	if (flags->has_light)
		parse_error("Light declared more than once");
	if (nfields != 4)
		parse_error("Invalid light format");
	if (!parse_vec3(fields[1], &scene->light.pos))
		parse_error("Invalid light position");
	if (!parse_ratio(fields[2], &scene->light.intensity))
		parse_error("Invalid light brightness (must be in [0.0, 1.0])");
	if (!parse_rgb(fields[3], &dummy_color))
		parse_error("Invalid light RGB value");
	flags->has_light = 1;
	return (1);
}
