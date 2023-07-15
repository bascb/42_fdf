/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_process_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:12:08 by bcastelo          #+#    #+#             */
/*   Updated: 2023/07/15 19:00:56 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_line(int *col_number, char **points)
{
	int	i;

	i = 0;
	while (points[i] != NULL)
		i++;
	if (*col_number == 0)
		*col_number = i;
	else if (*col_number < i)
		*col_number = i;
	free_matrix((void **) points);
}

int	*get_map_line(t_params *params, char *line)
{
	int		*map_line;
	char	**points;
	int		i;

	map_line = ft_calloc(params->map_cols, sizeof(int));
	if (!map_line)
	{
		free(line);
		clean_exit(params, "Unable to alloc memory for int array", 1);
	}
	points = ft_split(line, ' ');
	i = 0;
	while (points[i] != NULL)
	{
		map_line[i] = ft_atoi(points[i]);
		i++;
	}
	free_matrix((void **) points);
	return (map_line);
}

void	check_map(t_params *params, char *file_path)
{
	int		fd;
	int		lines_number;
	int		col_number;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		clean_exit(params, file_path, 1);
	lines_number = 0;
	col_number = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines_number++;
		check_line(&col_number, ft_split(line, ' '));
		free(line);
		if (col_number == 0)
			break ;
		line = get_next_line(fd);
	}
	close(fd);
	if (!lines_number || !col_number)
		clean_exit(params, "Incorrect file format", 0);
	params->map_lines = lines_number;
	params->map_cols = col_number;
}

void	get_map(t_params *params, char *file_path)
{
	int		i;
	char	*line;

	params->fd = open(file_path, O_RDONLY);
	if (params->fd == -1)
		clean_exit(params, file_path, 1);
	params->map_3d = ft_calloc(params->map_lines + 1, sizeof(int *));
	if (!params->map_3d)
		clean_exit(params, "Unable to create 3d matrix", 1);
	i = 0;
	while (i < params->map_lines)
	{
		line = get_next_line(params->fd);
		params->map_3d[i] = get_map_line(params, line);
		free(line);
		i++;
	}
	close(params->fd);
	params->fd = -1;
	init_2d_map(params);
}

void	init_2d_map(t_params *params)
{
	int	i;

	params->map_2d = ft_calloc(params->map_lines + 1, sizeof(t_point *));
	if (!params->map_2d)
		clean_exit(params, "Unable to create 2d matrix", 1);
	i = 0;
	while (i < params->map_lines)
	{
		params->map_2d[i] = ft_calloc(params->map_cols, sizeof(t_point));
		if (!params->map_2d[i])
			clean_exit(params, "Unable to create 2d array", 1);
		i++;
	}
}
