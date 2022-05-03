#include "../include/game.h"
#include <errno.h>

t_list	*get_map_list(t_game *game, t_list *map_buffer, int fd)
{
	t_list	*new;
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		temp = ft_strtrim(line, "\n");
		if (!temp[0])
			new = ft_lstnew(0);
		else
			new = ft_lstnew(ft_strdup(temp));
		ft_lstadd_back(&map_buffer, new);
		free(temp);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	game->map_height = i;
	return (map_buffer);
}

t_list	*read_map(t_game *game, t_list *map_buffer, char *argv)
{
	int	fd;

	if (ft_strstr(argv, ".cub") == 0)
		return (0);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (0);
	map_buffer = get_map_list(game, map_buffer, fd);
	close(fd);
	return (map_buffer);
}

void	print_map(t_list *map_buffer)
{
	t_list	*temp;

	temp = map_buffer;
	while (temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
}

// void	load_images(t_game *game, int *texture, char *path, t_img *img)
// {
// 	printf("buf : [%s]\n", path);
// 	img->img_height = 0;
// 	img->img_width = 0;
// 	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->img_width, &img->img_height);
// 	printf("h : %d\n", img->img_height);
// 		printf("w : %d\n", img->img_width);
// 	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
// 	for (int y = 0; y < img->img_height; y++)
// 	{
// 		for (int x = 0; x < img->img_width; x++)
// 		{
// 			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
// 		}
// 	}
// 	mlx_destroy_image(game->mlx, img->img);
// }

int	read_and_parse_map(t_game *game, t_list *map_buffer, char *argv)
{
	map_buffer = read_map(game, map_buffer, argv);
	if (!map_buffer)
		return (0);
	print_map(map_buffer);
	// load_images(game, game->texture[0], "./texture/greystone.xpm", &img);
	if (!parse_map(game, map_buffer))
	{
		ft_lstclear(&map_buffer, free);
		return (0);
	}
	ft_lstclear(&map_buffer, free);
	return (1);
}
