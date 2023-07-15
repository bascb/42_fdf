/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:54:35 by bcastelo          #+#    #+#             */
/*   Updated: 2023/07/14 21:21:58 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_matrix(void **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	matrix = NULL;
}

void	print_map_3d(t_params *params)
{
	int	i;
	int	j;

	i = 0;
	while (params->map_3d[i] != NULL)
	{
		j = 0;
		while (j < params->map_cols)
		{
			ft_printf("%i ", params->map_3d[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
