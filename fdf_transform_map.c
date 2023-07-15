/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 21:57:31 by bcastelo          #+#    #+#             */
/*   Updated: 2023/07/15 20:16:27 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plain_map(t_params *params, t_point start, int scale)
{
	int	i;
	int	j;
	int	color;

	color = create_trgb(0, 255, 255, 255);
	i = 0;
	while (i < params->map_lines)
	{
		j = 0;
		while (j < params->map_cols)
		{
			params->map_2d[i][j].x = start.x + j * scale;
			params->map_2d[i][j].y = start.y + i * scale;
			params->map_2d[i][j].color = color;
			j++;
		}
		i++;
	}
}

void	rotate_2d(t_params *params, t_point start, double angle)
{
	int		i;
	int		j;
	double	r[2];
	int		n[2];
	int		d[2];

	i = 0;
	while (i < params->map_lines)
	{
		j = 0;
		while (j < params->map_cols)
		{
			d[0] = params->map_2d[i][j].x - start.x;
			d[1] = params->map_2d[i][j].y - start.y;
			r[0] = d[0] * cos(angle) - d[1] * sin(angle);
			r[1] = d[0] * sin(angle) + d[1] * cos(angle);
			n[0] = round(r[0]) + start.x;
			n[1] = round(r[1]) + start.y;
			params->map_2d[i][j].x = n[0];
			params->map_2d[i][j].y = n[1];
			j++;
		}
		i++;
	}
}

void	iso_proj(t_params *params, t_point start, double angles[2])
{
	int		i;
	int		j;
	double	r[2];
	int		d[2];

	i = 0;
	while (i < params->map_lines)
	{
		j = 0;
		while (j < params->map_cols)
		{
			d[0] = params->map_2d[i][j].x - start.x;
			d[1] = params->map_2d[i][j].y - start.y;
			r[0] = d[0] * cos(angles[1]) - sin(angles[1])
				* params->map_3d[i][j] * params->map_scale;
			r[1] = -d[0] * sin(angles[0]) * sin(angles[1])
				+ cos(angles[0]) * d[1] - sin(angles[0]) * cos(angles[1])
				* params->map_3d[i][j] * params->map_scale;
			params->map_2d[i][j].x = round(r[0]) + start.x;
			params->map_2d[i][j++].y = round(r[1]) + start.y;
		}
		i++;
	}
}
