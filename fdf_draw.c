/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:35:38 by bcastelo          #+#    #+#             */
/*   Updated: 2023/07/15 20:12:23 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_point(t_params *params, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > MAX_WIDTH)
		return ;
	if (y < 0 || y > MAX_HEIGHT)
		return ;
	dst = params->addr + (y * params->line_length
			+ x * (params->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	draw_point2(int err[2], int d[2], int index[2], int sum[2])
{
	err[1] = 2 * err[0];
	if (err[1] > -d[1]) 
	{
		err[0] -= d[1];
		index[0] += sum[0];
	}
	if (err[1] < d[0])
	{
		err[0] += d[0];
		index[1] += sum[1];
	}
}

void	draw_line(t_params *params, t_point start, t_point end)
{
	int	d[2];
	int	index[2];
	int	err[2];
	int	sum[2];

	d[0] = abs(end.x - start.x);
	d[1] = abs(end.y - start.y);
	index[0] = start.x;
	index[1] = start.y;
	sum[0] = -1;
	sum[1] = -1;
	if (start.x < end.x)
		sum[0] = 1;
	if (start.y < end.y)
		sum[1] = 1;
	err[0] = d[0] - d[1];
	while (index[0] != end.x || index[1] != end.y)
	{
		draw_point(params, index[0], index[1], start.color);
		draw_point2(err, d, index, sum);
	}
}

void	draw_map(t_params *params)
{
	int	i;
	int	j;

	i = 0;
	while (i < params->map_lines - 1)
	{
		j = 0;
		while (j < params->map_cols - 1)
		{
			draw_line(params, params->map_2d[i][j], params->map_2d[i][j + 1]);
			draw_line(params, params->map_2d[i][j], params->map_2d[i + 1][j]);
			j++;
		}
		draw_line(params, params->map_2d[i][j], params->map_2d[i + 1][j]);
		i++;
		j = 0;
		while (j < params->map_cols - 1)
		{
			draw_line(params, params->map_2d[i][j], params->map_2d[i][j + 1]);
			j++;
		}
	}
}
