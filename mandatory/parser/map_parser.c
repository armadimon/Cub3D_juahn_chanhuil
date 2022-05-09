/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:33:36 by juahn             #+#    #+#             */
/*   Updated: 2022/05/07 11:24:43 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"

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

int	read_and_parse_map(t_game *game, t_list *map_buffer, char *argv)
{
	map_buffer = read_map(map_buffer, argv);
	if (!map_buffer)
		return (0);
	if (!parse_map(game, map_buffer) || !check_map(game))
	{
		ft_lstclear(&map_buffer, free);
		return (0);
	}
	ft_lstclear(&map_buffer, free);
	return (1);
}
