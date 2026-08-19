/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:45:48 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/14 12:45:50 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	parse_plane_data(t_scene *scene, t_plane *pl, char **fields)
{
	if (!parse_vec3(fields[1], &pl->point))
	{
		free(pl);
		parse_error(scene, "Invalid plane point");
	}
	if (!parse_norm_vec3(fields[2], &pl->normal))
	{
		free(pl);
		parse_error(scene, "Invalid plane normal (must be unit vector)");
	}
	if (!parse_rgb(fields[3], &pl->color))
	{
		free(pl);
		parse_error(scene, "Invalid plane RGB value");
	}
	return (1);
}

int	parse_plane(t_scene *scene, char **fields, int nfields)
{
	t_plane	*pl;

	if (nfields != 4)
		parse_error(scene, "Invalid plane format");
	pl = malloc(sizeof(t_plane));
	if (!pl)
		parse_error(scene, "Memory allocation failed");
	parse_plane_data(scene, pl, fields);
	add_object(scene, new_object(scene, OBJ_PLANE, pl));
	return (1);
}

static int	parse_cylinder_dimensions(t_scene *scene, t_cylinder *cy,
		char **fields)
{
	double	diam;
	double	height;

	if (!parse_double(fields[3], &diam) || diam <= 0.0)
	{
		free(cy);
		parse_error(scene, "Invalid cylinder diameter (must be > 0)");
	}
	cy->radius = diam / 2.0;
	if (!parse_double(fields[4], &height) || height <= 0.0)
	{
		free(cy);
		parse_error(scene, "Invalid cylinder height (must be > 0)");
	}
	cy->height = height;
	return (1);
}

static int	parse_cylinder_data(t_scene *scene, t_cylinder *cy, char **fields)
{
	if (!parse_vec3(fields[1], &cy->base))
	{
		free(cy);
		parse_error(scene, "Invalid cylinder center");
	}
	if (!parse_norm_vec3(fields[2], &cy->axis))
	{
		free(cy);
		parse_error(scene, "Invalid cylinder axis (must be unit vector)");
	}
	parse_cylinder_dimensions(scene, cy, fields);
	cy->base = vec3_sub(cy->base, vec3_scale(cy->axis, cy->height / 2.0));
	if (!parse_rgb(fields[5], &cy->color))
	{
		free(cy);
		parse_error(scene, "Invalid cylinder RGB value");
	}
	return (1);
}

int	parse_cylinder(t_scene *scene, char **fields, int nfields)
{
	t_cylinder	*cy;

	if (nfields != 6)
		parse_error(scene, "Invalid cylinder format");
	cy = malloc(sizeof(t_cylinder));
	if (!cy)
		parse_error(scene, "Memory allocation failed");
	parse_cylinder_data(scene, cy, fields);
	add_object(scene, new_object(scene, OBJ_CYLINDER, cy));
	return (1);
}
