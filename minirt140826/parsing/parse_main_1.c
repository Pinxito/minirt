/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:52:33 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/14 12:52:35 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	init_parse_state(t_scene *scene, t_parse_flags *flags)
{
	flags->has_ambient = 0;
	flags->has_camera = 0;
	flags->has_light = 0;
	scene->objects = NULL;
	scene->mlx.mlx = NULL;
	scene->mlx.win = NULL;
	scene->mlx.img = NULL;
	scene->mlx.addr = NULL;
}

static void	process_line(t_scene *scene, t_parse_flags *flags, char *line)
{
	char	**fields;
	int		nfields;
	int		i;

	i = 0;
	while (line[i] && ft_isspace_c(line[i]))
		i++;
	if (!line[i])
		return ;
	fields = ft_split_spaces(line);
	if (!fields)
		parse_error("Memory allocation failed");
	nfields = ft_count_fields(fields);
	parse_line(scene, flags, fields, nfields);
	ft_free_fields(fields);
}

static void	read_scene_file(t_scene *scene, t_parse_flags *flags, int fd)
{
	char	*line;

	line = read_one_line(fd);
	while (line)
	{
		process_line(scene, flags, line);
		free(line);
		line = read_one_line(fd);
	}
}

int	parse_scene(t_scene *scene, char *file)
{
	t_parse_flags	flags;
	int				fd;

	if (!check_extension(file))
		parse_error("File must have .rt extension");
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\n", 6);
		perror(file);
		exit(1);
	}
	init_parse_state(scene, &flags);
	read_scene_file(scene, &flags, fd);
	close(fd);
	setup_scene(scene, &flags, file);
	return (1);
}
