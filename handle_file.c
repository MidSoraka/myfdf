/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:39:26 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/12 17:34:36 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	setup_settings(t_prm *prm)
{
	prm->scale_xyz[0] = 20;
	prm->scale_xyz[1] = 20;
	prm->scale_xyz[2] = 10;
	prm->isfill = 0;
}

int	open_fd(char *file, int argc, t_prm *prm)
{
	int	fd;

	if (argc != 2)
	{
		ft_putendl("usage ./fdf matrix_file");
		return (0);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl("error");
		exit (0);
	}
	setup_settings(prm);
	return (fd);
}
