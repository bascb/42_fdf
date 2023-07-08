/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 19:22:06 by bcastelo          #+#    #+#             */
/*   Updated: 2023/07/08 15:06:58 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <mlx.h>

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	close_window(int keycode, t_vars *vars)
{
	ft_printf("Key pressed: %i - %#x\n", (unsigned int) keycode, (unsigned int) keycode);
	if (keycode == XK_Escape)
		ft_printf("Macro: %#x keymap: %#x\n", XK_Escape, keycode);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	mlx_hook(vars.win, 2, 1L<<0, close_window, &vars);
	mlx_loop(vars.mlx);
	exit(0);
}
