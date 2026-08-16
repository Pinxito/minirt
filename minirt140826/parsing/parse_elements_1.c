/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:53:11 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/14 12:53:12 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_object	*new_object(t_obj_type type, void *data)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		parse_error("Memory allocation failed");
	obj->type = type;
	obj->data = data;
	obj->next = NULL;
	return (obj);
}

void	add_object(t_scene *scene, t_object *obj)
{
	t_object	*cur;

	if (!scene->objects)
	{
		scene->objects = obj;
		return ;
	}
	cur = scene->objects;
	while (cur->next)
		cur = cur->next;
	cur->next = obj;
}

static int	parse_sphere_data(t_sphere *sp, char **fields)
{
	double	diam;

	if (!parse_vec3(fields[1], &sp->center))
	{
		free(sp);
		parse_error("Invalid sphere center");
	}
	if (!parse_double(fields[2], &diam) || diam <= 0.0)
	{
		free(sp);
		parse_error("Invalid sphere diameter (must be > 0)");
	}
	sp->radius = diam / 2.0;
	if (!parse_rgb(fields[3], &sp->color))
	{
		free(sp);
		parse_error("Invalid sphere RGB value");
	}
	return (1);
}

int	parse_sphere(t_scene *scene, char **fields, int nfields)
{
	t_sphere	*sp;

	if (nfields != 4)
		parse_error("Invalid sphere format");
	sp = malloc(sizeof(t_sphere));
	if (!sp)
		parse_error("Memory allocation failed");
	parse_sphere_data(sp, fields);
	add_object(scene, new_object(OBJ_SPHERE, sp));
	return (1);
}
