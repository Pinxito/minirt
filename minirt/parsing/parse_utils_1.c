/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:51:45 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/14 12:51:46 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_count_fields(char **fields)
{
	int	n;

	n = 0;
	if (!fields)
		return (0);
	while (fields[n])
		n++;
	return (n);
}

void	ft_free_fields(char **fields)
{
	int	i;

	if (!fields)
		return ;
	i = 0;
	while (fields[i])
		free(fields[i++]);
	free(fields);
}

int			ft_isspace_c(char c);

static int	count_words(char *s)
{
	int	n;
	int	in;

	n = 0;
	in = 0;
	while (*s)
	{
		if (!ft_isspace_c(*s) && !in)
		{
			in = 1;
			n++;
		}
		else if (ft_isspace_c(*s))
			in = 0;
		s++;
	}
	return (n);
}

static char	*extract_word(char *s, int *pos)
{
	int		start;
	int		len;
	char	*word;
	int		i;

	while (s[*pos] && ft_isspace_c(s[*pos]))
		(*pos)++;
	start = *pos;
	while (s[*pos] && !ft_isspace_c(s[*pos]))
		(*pos)++;
	len = *pos - start;
	if (len == 0)
		return (NULL);
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[start + i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

char	**ft_split_spaces(char *line)
{
	int		nwords;
	char	**fields;
	int		pos;
	int		i;

	nwords = count_words(line);
	fields = malloc((nwords + 1) * sizeof(char *));
	if (!fields)
		return (NULL);
	pos = 0;
	i = 0;
	while (i < nwords)
	{
		fields[i] = extract_word(line, &pos);
		if (!fields[i])
		{
			while (i > 0)
				free(fields[--i]);
			free(fields);
			return (NULL);
		}
		i++;
	}
	fields[nwords] = NULL;
	return (fields);
}
