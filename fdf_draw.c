/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:35:38 by bcastelo          #+#    #+#             */
/*   Updated: 2023/07/15 03:26:28 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_point(t_params *params, int x, int y, int color)
{
	char	*dst;

	dst = params->addr + (y * params->line_length
			+ x * (params->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	draw_y_bigger(t_params *params, t_point start, t_point end)
{
	int	dx;
	int	dy;
	int	xi;
	int	yi;
	int	d;

	dx = end.x - start.x;
	dy = end.y - start.y;
	xi = start.x;
	yi = start.y;
	d = 2 * dx - dy;
	while (yi <= end.y)
	{
		draw_point(params, xi, yi, start.color);
		if (d > 0)
		{
			xi++;
			d = d - 2 * dy;
		}
		d = d + 2 * dx;
		yi++;
	}
}

void	draw_x_bigger(t_params *params, t_point start, t_point end)
{
	int	dx;
	int	dy;
	int	xi;
	int	yi;
	int	d;

	dx = end.x - start.x;
	dy = end.y - start.y;
	xi = start.x;
	yi = start.y;
	d = 2 * dy - dx;
	while (xi <= end.x)
	{
		draw_point(params, xi, yi, start.color);
		if (d > 0)
		{
			yi++;
			d = d - 2 * dx;
		}
		d = d + 2 * dy;
		xi++;
	}
}

void	draw_line(t_params *params, t_point start, t_point end)
{
	int	dx;
	int	dy;
	int	xi;
	int	yi;
	int	err;
	int	err2;
	int	sum_x;
	int	sum_y;

	dx = abs(end.x - start.x);
	dy = abs(end.y - start.y);
	xi = start.x;
	yi = start.y;
	if (start.x < end.x)
		sum_x = 1;
	else
		sum_x = -1;
	if (start.y < end.y)
		sum_y = 1;
	else
		sum_y = -1;
	err = dx - dy;
	while (xi != end.x || yi != end.y )
	{
		draw_point(params, xi, yi, start.color);
		err2 = 2 * err;
		if (err2 > -dy) {
            err -= dy;
            xi += sum_x;
        }
        if (err2 < dx) {
            err += dx;
            yi += sum_y;
        }
	}
}

/* Using Bresenham's line algorithm */
void	draw_line2(t_params *params, t_point start, t_point end)
{
	int	dx;
	int	dy;

	dx = end.x - start.x;
	dy = end.y - start.y;
	if (dx < 0 || dy < 0) 
	{
		if (dy < dx)
			draw_y_bigger(params, end, start);
		else
			draw_x_bigger(params, end, start);
	}
	else
	{
		if (dy > dx)
			draw_y_bigger(params, start, end);
		else
			draw_x_bigger(params, start, end);
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
