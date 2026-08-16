/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:44:53 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/14 12:45:11 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minirt.h"

# define NORM_TOL 0.0001
# define BUFFER_SIZE 4096

typedef struct s_parse_flags
{
	int		has_ambient;
	int		has_camera;
	int		has_light;
}			t_parse_flags;

typedef struct s_double_parse
{
	double	res;
	double	frac;
	int		sign;
	int		i;
	int		has_dot;
}			t_double_parse;

typedef struct s_vec3_parse
{
	char	buf[128];
	double	vals[3];
	int		part;
	int		pos;
}			t_vec3_parse;

typedef struct s_rgb_parse
{
	char	buf[8];
	int		vals[3];
	int		part;
	int		pos;
}			t_rgb_parse;

int			parse_scene(t_scene *scene, char *file);
char		*read_one_line(int fd);
int			parse_line(t_scene *scene, t_parse_flags *flags, char **fields,
				int nfields);
int			parse_ambient(t_scene *scene, t_parse_flags *flags, char **fields,
				int nfields);
int			parse_camera(t_scene *scene, t_parse_flags *flags, char **fields,
				int nfields);
int			parse_light(t_scene *scene, t_parse_flags *flags, char **fields,
				int nfields);
int			parse_sphere(t_scene *scene, char **fields, int nfields);
int			parse_plane(t_scene *scene, char **fields, int nfields);
int			parse_cylinder(t_scene *scene, char **fields, int nfields);
t_object	*new_object(t_obj_type type, void *data);
void		add_object(t_scene *scene, t_object *obj);
int			parse_vec3_components(char *str, double vals[3]);
int			parse_vec3(char *str, t_vec3 *v);
int			parse_rgb_components(char *str, int vals[3]);
int			parse_rgb(char *str, int *color);
int			parse_ratio(char *str, double *out);
int			parse_double(char *str, double *out);
int			parse_norm_vec3(char *str, t_vec3 *v);
int			ft_count_fields(char **fields);
char		**ft_split_spaces(char *line);
void		ft_free_fields(char **fields);
int			ft_isspace_c(char c);
int			check_extension(char *file);
void		parse_error(char *msg);
void		free_scene_objects(t_scene *scene);
void		free_scene_full(t_scene *scene);
int			setup_scene(t_scene *scene, t_parse_flags *flags, char *file);

#endif
