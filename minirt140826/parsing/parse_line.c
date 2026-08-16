/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:45:30 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/14 12:45:31 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	id_eq(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i])
	{
		if (a[i] != b[i])
			return (0);
		i++;
	}
	return (a[i] == '\0' && b[i] == '\0');
}

static int	is_known_id(char *id)
{
	return (id_eq(id, "A") || id_eq(id, "C") || id_eq(id, "L") || id_eq(id,
			"sp") || id_eq(id, "pl") || id_eq(id, "cy"));
}

int	parse_line(t_scene *scene, t_parse_flags *flags, char **fields, int nfields)
{
	if (nfields == 0)
		return (1);
	if (fields[0][0] == '#')
		return (1);
	if (!is_known_id(fields[0]))
		parse_error("Unknown identifier in scene file");
	if (id_eq(fields[0], "A"))
		return (parse_ambient(scene, flags, fields, nfields));
	if (id_eq(fields[0], "C"))
		return (parse_camera(scene, flags, fields, nfields));
	if (id_eq(fields[0], "L"))
		return (parse_light(scene, flags, fields, nfields));
	if (id_eq(fields[0], "sp"))
		return (parse_sphere(scene, fields, nfields));
	if (id_eq(fields[0], "pl"))
		return (parse_plane(scene, fields, nfields));
	if (id_eq(fields[0], "cy"))
		return (parse_cylinder(scene, fields, nfields));
	return (1);
}
