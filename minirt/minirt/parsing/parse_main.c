/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:44:38 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/14 12:44:39 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*extract_line(char *buf, int start, int end)
{
	int		len;
	char	*line;
	int		i;

	len = end - start;
	if (len > 0 && buf[start + len - 1] == '\r')
		len--;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = buf[start + i];
		i++;
	}
	line[len] = '\0';
	return (line);
}

static void	shift_buffer(char *buf, int *len, int consumed)
{
	int	i;

	i = 0;
	while (consumed + i < *len)
	{
		buf[i] = buf[consumed + i];
		i++;
	}
	*len = i;
}

static int	find_newline(char *buf, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*read_buffer_line(char *buf, int *buf_len)
{
	char	*line;
	int		nl;

	nl = find_newline(buf, *buf_len);
	if (nl < 0)
		return (NULL);
	line = extract_line(buf, 0, nl);
	shift_buffer(buf, buf_len, nl + 1);
	return (line);
}

char	*read_one_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	static int	buf_len;
	char		*line;
	ssize_t		n;

	while (1)
	{
		line = read_buffer_line(buf, &buf_len);
		if (line)
			return (line);
		n = read(fd, buf + buf_len, BUFFER_SIZE - buf_len);
		if (n <= 0)
		{
			if (buf_len == 0)
				return (NULL);
			line = extract_line(buf, 0, buf_len);
			buf_len = 0;
			return (line);
		}
		buf_len += (int)n;
	}
}
