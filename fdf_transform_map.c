/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 21:57:31 by bcastelo          #+#    #+#             */
/*   Updated: 2023/07/15 15:26:10 by bcastelo         ###   ########.fr       */
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

void	rotate_2d(t_params *params, t_point start, double alpha, double beta)
{
	int		i;
	int		j;
	double	rx;
	double	ry;
	int		nx;
	int		ny;
	int		dx;
	int		dy;

	i = 0;
	while (i < params->map_lines)
	{
		j = 0;
		while (j < params->map_cols)
		{
			dx = params->map_2d[i][j].x - start.x;
			dy = params->map_2d[i][j].y - start.y;
			rx = dx * cos(alpha) - dy * sin(alpha);
			ry = dx * sin(beta) + dy * cos(beta);
			nx = round(rx) + start.x;
			ny = round(ry) + start.y;
			params->map_2d[i][j].x = nx;
			params->map_2d[i][j].y = ny;
			j++;
		}
		i++;
	}
}

void	iso_proj(t_params *params, t_point start, double alpha, double beta)
{
	int		i;
	int		j;
	double	rx;
	double	ry;
	int		nx;
	int		ny;
	int		dx;
	int		dy;

	i = 0;
	while (i < params->map_lines)
	{
		j = 0;
		while (j < params->map_cols)
		{
			dx = params->map_2d[i][j].x - start.x;
			dy = params->map_2d[i][j].y - start.y;
			rx = dx * cos(beta) - sin(beta) *  params->map_3d[i][j] * params->map_scale;// / (params->map_cols - 1);
			ry = -dx * sin(alpha) * sin(beta) + cos(alpha) * dy - sin(alpha) * cos(beta) * params->map_3d[i][j] * params->map_scale;// / (params->map_lines - 1);
			nx = round(rx) + start.x;
			ny = round(ry) + start.y;
			params->map_2d[i][j].x = nx;
			params->map_2d[i][j].y = ny;
			j++;
		}
		i++;
	}
}
