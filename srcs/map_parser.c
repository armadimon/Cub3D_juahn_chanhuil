#include "../include/game.h"

t_list	*get_map_list(t_list *map_buffer, int fd)
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
	return (map_buffer);
}

t_list	*read_map(t_list *map_buffer, char *argv)
{
	int	fd;

	if (ft_strstr(argv, ".cub") == 0)
		return (0);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (0);
	map_buffer = get_map_list(map_buffer, fd);
	close(fd);
	return (map_buffer);
}

void	print_map(t_game *game, t_list *map_buffer)
{
	t_list	*temp;
	int		i;

	temp = map_buffer;
	while (temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	i = -1;
	while (game->map[++i])
		printf("map : [%s]\n", game->map[i]);
	printf("width : %d\n", game->map_width);
	printf("height : %d\n", game->map_height);
	vec_print(game->p.dir);
	vec_print(game->p.pos);
	vec_print(game->p.plane);
}

int	read_and_parse_map(t_game *game, t_list *map_buffer, char *argv)
{
	map_buffer = read_map(map_buffer, argv);
	if (!map_buffer)
		return (0);
	if (!parse_map(game, map_buffer) ||
		!check_map(game))
	{
		ft_lstclear(&map_buffer, free);
		return (0);
	}
	print_map(game, map_buffer);
	ft_lstclear(&map_buffer, free);
	return (1);
}
