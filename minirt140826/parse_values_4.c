/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:50:24 by gguillen          #+#    #+#             */
/*   Updated: 2026/06/14 12:50:26 by gguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_rgb(char *str, int *color)
{
	int	vals[3];

	if (!parse_rgb_components(str, vals))
		return (0);
	*color = (vals[0] << 16) | (vals[1] << 8) | vals[2];
	return (1);
}

int	parse_ratio(char *str, double *out)
{
	if (!parse_double(str, out))
		return (0);
	if (*out < 0.0 || *out > 1.0)
		return (0);
	return (1);
}
