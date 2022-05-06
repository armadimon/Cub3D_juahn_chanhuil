/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:25:55 by juahn             #+#    #+#             */
/*   Updated: 2022/05/06 15:27:52 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"

int		load_image(t_game *game, int *texture, char *path, t_img *img)
{
	int y;
	int x;

	y = -1;
	img->img = mlx_xpm_file_to_image(game->mlx, path, &(img->img_width), &(img->img_height));
	if (!img->img)
		return (0);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
	}
	mlx_destroy_image(game->mlx, img->img);
	return (1);
}
