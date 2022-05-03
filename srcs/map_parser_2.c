#include "../include/game.h"

void	free_strs(char **strs)
{
	int	i;

	i = -1;
	if (strs)
	{
		while (strs[++i])
			free(strs[i]);
	free(strs);
	}
}

int		load_image(t_game *game, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &(img->img_width), &(img->img_height));
	if (!img->img)
		return (0);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(game->mlx, img->img);
	return (1);
}

int	set_F_C_color(t_game *game, char *str, int flag)
{
	char	**buf;
	int		i;

	i = 0;
	buf = ft_split(str, ',');
	while (buf[i])
	{
		if (i == 0 && flag == 0)
			game->map_data.F_red = ft_atoi(buf[i]);
		else if (i == 1 && flag == 0)
			game->map_data.F_green = ft_atoi(buf[i]);
		else if (i == 2 && flag == 0)
			game->map_data.F_blue = ft_atoi(buf[i]);
		if (i == 0 && flag == 1)
			game->map_data.C_red = ft_atoi(buf[i]);
		else if (i == 1 && flag == 1)
			game->map_data.C_green = ft_atoi(buf[i]);
		else if (i == 2 && flag == 1)
			game->map_data.C_blue = ft_atoi(buf[i]);
		if (i > 2)
			return (0);
		i++;
	}
	return (1);
}

void	check_id(t_valid *vaild, char *str)
{
	if (ft_strstr(buf[0], "NO"))
		vaild->valid_no = 1;
	else if (ft_strstr(buf[0], "SO"))
		vaild->valid_so = 1;
	else if (ft_strstr(buf[0], "WE"))
		vaild->valid_we = 1;
	else if (ft_strstr(buf[0], "EA"))
		vaild->valid_ea = 1;
}

int	get_map_contents(t_game *game, char **buf, t_valid *vaild)
{
	t_img	img;

	check_id(vaild, buf[0])
	if (ft_strstr(buf[0], "NO"))
		load_image(game, game->texture[0], buf[1], &img);
	else if (ft_strstr(buf[0], "SO"))
		load_image(game, game->texture[1], buf[1], &img);
	else if (ft_strstr(buf[0], "WE"))
		load_image(game, game->texture[2], buf[1], &img);
	else if (ft_strstr(buf[0], "EA"))
		load_image(game, game->texture[3], buf[1], &img);
	else if (ft_strstr(buf[0], "F"))
		set_F_C_color(game, buf[1], 0);
	else if (ft_strstr(buf[0], "C"))
		set_F_C_color(game, buf[1], 1);
	return (1);
}

int	check_map_contents(t_game *game, t_valid *valid)
{
	if (valid->valid_ea != 1 ||
		valid->valid_no != 1 ||
		valid->valid_so != 1 ||
		valid->valid_we != 1)
		return (0);
	if (game->map_data.C_red == -1 ||
		game->map_data.C_green == -1 ||
		game->map_data.C_blue == -1 ||
		game->map_data.F_red == -1 ||
		game->map_data.F_green == -1 ||
		game->map_data.F_blue == -1 ||)
		return (0);
	return (1);
}

int	parse_map(t_game *game, t_list *map_list)
{
	t_list	*temp;
	t_valid	vaild;
	char	**buf;
	temp = map_list;
	while (temp)
	{
		buf = ft_split((char *)temp->content, ' ');
		if (buf)
			get_map_contents(game, buf, vaild);
		free_strs(buf);
		temp = temp->next;
		check_map_contents(game);
	}
	return (1);
}