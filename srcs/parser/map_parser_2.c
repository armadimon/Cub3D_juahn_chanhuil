#include "../../include/game.h"

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

int	check_valid_color(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (!ft_isdigit(buf[i]))
			return (0);
		i++;
	}
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
		if (!check_valid_color(buf[i]) || i > 2)
			return (0);
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
		i++;
	}
	return (1);
}

int	check_floor_data(t_game *game)
{
	if (game->map_data.F_red == -1)
		return (0);
	if (game->map_data.F_green == -1)
		return (0);
	if (game->map_data.F_blue == -1)
		return (0);
	return (1);
}

int	check_ceiling_data(t_game *game)
{
	if (game->map_data.C_red == -1)
		return (0);
	if (game->map_data.C_green == -1)
		return (0);
	if (game->map_data.C_blue == -1)
		return (0);
	return (1);
}

int	check_id(t_valid *valid, char *str)
{
	if (ft_strstr(str, "NO") && valid->valid_no == 0)
		valid->valid_no = 1;
	else if (ft_strstr(str, "SO") && valid->valid_so == 0)
		valid->valid_so = 1;
	else if (ft_strstr(str, "WE") && valid->valid_we == 0)
		valid->valid_we = 1;
	else if (ft_strstr(str, "EA") && valid->valid_ea == 0)
		valid->valid_ea = 1;
	else if (ft_strstr(str, "F") && valid->valid_f == 0)
		valid->valid_f = 1;
	else if (ft_strstr(str, "C") && valid->valid_c == 0)
		valid->valid_c = 1;
	else
		return (0);
	return (1);
}

int	check_id_rule(char **buf)
{
	int i;

	i = 0;
	while (buf[i])
		i++;
	if (i == 2)
		return (1);
	return (0);
}

int	get_map_contents(t_game *game, char **buf, t_valid *valid)
{
	t_img	img;
	int		ret;

	ret = 0;
	if	(!check_id(valid, buf[0]))
		return (ret);
	if (ft_strstr(buf[0], "NO") && ft_strcmp(buf[0], "NO") && check_id_rule(buf))
		ret = load_image(game, game->texture[0], buf[1], &img);
	else if (ft_strstr(buf[0], "SO") && ft_strcmp(buf[0], "SO") && check_id_rule(buf))
		ret = load_image(game, game->texture[1], buf[1], &img);
	else if (ft_strstr(buf[0], "WE") && ft_strcmp(buf[0], "WE") && check_id_rule(buf))
		ret = load_image(game, game->texture[2], buf[1], &img);
	else if (ft_strstr(buf[0], "EA") && ft_strcmp(buf[0], "EA") && check_id_rule(buf))
		ret = load_image(game, game->texture[3], buf[1], &img);
	else if (ft_strstr(buf[0], "F") && ft_strcmp(buf[0], "F") && check_id_rule(buf))
		ret = set_F_C_color(game, buf[1], 0);
	else if (ft_strstr(buf[0], "C") && ft_strcmp(buf[0], "C") && check_id_rule(buf))
		ret = set_F_C_color(game, buf[1], 1);
	else
		return (0);
	return (ret);
}

int	check_map_contents(t_game *game, t_valid *valid)
{
	if (valid->valid_ea == 0 ||
		valid->valid_no == 0 ||
		valid->valid_so == 0 ||
		valid->valid_we == 0)
		return (0);
	if (game->map_data.C_red < 0 || game->map_data.C_red > 255)
		return (0);
	if (game->map_data.C_green < 0 || game->map_data.C_green > 255)
		return (0);
	if (game->map_data.C_blue < 0 || game->map_data.C_blue > 255)
		return (0);
	if (game->map_data.F_red < 0 || game->map_data.F_red > 255)
		return (0);
	if (game->map_data.F_green < 0 || game->map_data.F_green > 255)
		return (0);
	if (game->map_data.F_blue < 0 || game->map_data.F_blue > 255)
		return (0);
	return (1);
}

int	parse_map(t_game *game, t_list *map_list)
{
	t_list	*temp;
	t_valid	valid;
	char	**buf;
	int		ret;

	ret = 1;
	temp = map_list;
	init_valid(&valid);
	while (temp && ret)
	{
		if (temp->content == NULL)
		{
			temp = temp->next;
			continue ;
		}
		if (check_map_contents(game, &valid))
			return (get_map_arr(game, temp));
		buf = ft_split((char *)temp->content, ' ');
		if (buf)
			ret = get_map_contents(game, buf, &valid);
		free_strs(buf);
		temp = temp->next;
	}
	if (!ret || !check_map_contents(game, &valid) || !game->map)
		return (0);
	return (1);
}