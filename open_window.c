/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:45:38 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/14 22:25:00 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	window_size(t_prm *prm)
{
	int	temp1;
	int	temp2;

	prm->win_x = prm->scale_xyz[0] * prm->xyz[0][X] * 3;
	prm->win_y = prm->scale_xyz[1] * prm->xyz[0][Y] * 3;
	if (prm->win_x > 1920)
		prm->win_x = 1920;
	if (prm->win_y > 1080)
		prm->win_y = 1080;
	if (prm->win_x < 240)
		prm->win_x = 240;
	if (prm->win_y < 240)
		prm->win_y = 240;
	temp1 = prm->xyz[0][X] * prm->scale_xyz[0];
	temp2 = prm->xyz[0][Y] * prm->scale_xyz[1];
	if (temp1 > prm->win_x || temp2 > prm->win_y)
	{
		prm->scale_xyz[X] = 4;
		prm->scale_xyz[Y] = 4;
		prm->scale_xyz[Z] = 2;
	}
}

void	open_window(t_prm *prm)
{
	double	pyth;
	t_mlx	*mlx;

	mlx = prm->mlx;
	window_size(prm);
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, prm->win_x, prm->win_y, "win");
	mlx->image_ptr = mlx_new_image(mlx->mlx_ptr, prm->win_x, prm->win_y);
	mlx->image_add = \
	mlx_get_data_addr(mlx->image_ptr, &prm->bpp, &prm->size_line, &prm->erdian);
	prm->z_buffer = (int *)malloc(sizeof(int) * prm->win_x * prm->win_y);
	mlx_loop_hook(mlx->mlx_ptr, mlx_window_loop, prm);
	mlx_key_hook(mlx->win_ptr, keycode_hook, prm);
	mlx_loop(mlx->mlx_ptr);
}
