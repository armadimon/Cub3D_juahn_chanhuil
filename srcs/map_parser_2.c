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
	if (ft_strstr(str, "NO"))
		vaild->valid_no = 1;
	else if (ft_strstr(str, "SO"))
		vaild->valid_so = 1;
	else if (ft_strstr(str, "WE"))
		vaild->valid_we = 1;
	else if (ft_strstr(str, "EA"))
		vaild->valid_ea = 1;
}

int	get_map_contents(t_game *game, char **buf, t_valid *vaild)
{
	t_img	img;

	check_id(vaild, buf[0]);
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
	// printf("no  : %d\n", valid->valid_no);
	// printf("ea  : %d\n", valid->valid_ea);
	// printf("so  : %d\n", valid->valid_so);
	// printf("we  : %d\n", valid->valid_we);
	if (valid->valid_ea == 0 ||
		valid->valid_no == 0 ||
		valid->valid_so == 0 ||
		valid->valid_we == 0)
		return (0);
	// printf ("check\n");
	// printf("C_red  : %d\n", game->map_data.C_red);
	// printf("C_red  : %d\n", game->map_data.C_green);
	// printf("C_red  : %d\n", game->map_data.C_blue);
	// printf("C_red  : %d\n", game->map_data.F_red);
	// printf("C_red  : %d\n", game->map_data.F_green);
	// printf("C_red  : %d\n", game->map_data.F_blue);
	if (game->map_data.C_red == -1 ||
		game->map_data.C_green == -1 ||
		game->map_data.C_blue == -1 ||
		game->map_data.F_red == -1 ||
		game->map_data.F_green == -1 ||
		game->map_data.F_blue == -1)
		return (0);
	return (1);
}

void	init_valid(t_valid *valid)
{
	valid->valid_ea = 0;
	valid->valid_no = 0;
	valid->valid_we = 0;
	valid->valid_so = 0;
}

int cpy_map(t_game *game, t_list *map_list, int row, int col)
{
	int i;
	int j;
	char *buf;

	i = 0;
	while (i < row)
	{
		j = -1;
		game->map[i] = (char *)malloc(sizeof(char) * col + 1);
		while (++j < col)
			game->map[i][j] = ' ';
		game->map[i][j] = '\0';
		i++;
	}
	game->map[i] = NULL;
	i = -1;
	while (++i < row)
	{
		j = -1;
		buf = map_list->content;
		while ((++j < col) && buf[j])
			game->map[i][j] = buf[j];
		map_list = map_list->next;
	}
	return (1);
}

int	get_map_arr(t_game *game, t_list *map_list)
{
	t_list	*temp;
	int		row;
	int		col;

	temp = map_list;
	row = 0;
	col = 0;
	while (temp)
	{
		row++;
		if (col < (int)ft_strlen((char *)temp->content))
			col = ft_strlen((char *)temp->content);
		temp = temp->next;
	}
	game->map = (char **)malloc(sizeof(char *) * (row + 1));
	cpy_map(game, map_list, row, col);
	return (1);
}

int	parse_map(t_game *game, t_list *map_list)
{
	t_list	*temp;
	t_valid	valid;
	char	**buf;

	temp = map_list;
	init_valid(&valid);
	while (temp)
	{
		if (check_map_contents(game, &valid))
			return (get_map_arr(game, temp));
		buf = ft_split((char *)temp->content, ' ');
		if (buf)
			get_map_contents(game, buf, &valid);
		free_strs(buf);
		temp = temp->next;
	}
	if (!check_map_contents(game, &valid))
		return (0);
	return (1);
}