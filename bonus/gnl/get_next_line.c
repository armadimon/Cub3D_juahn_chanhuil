/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 11:08:47 by juahn             #+#    #+#             */
/*   Updated: 2022/05/07 11:10:56 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

char	*get_line(char *buff)
{
	int		i;
	char	*str;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	str = malloc(i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		str[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
	{
		str[i] = buff[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_new_buff(char *buff)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(buff) - i + 1));
	if (!str)
		return (NULL);
	i++;
	while (buff[i])
		str[j++] = buff[i++];
	str[j] = '\0';
	free(buff);
	return (str);
}

char	*get_buff(int fd, char *left_str)
{
	char	*buff;
	int		ret;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	ret = 1;
	while (!ft_strchr_gnl(left_str) && ret != 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[ret] = '\0';
		left_str = ft_strjoin_gnl(left_str, buff);
	}
	free(buff);
	return (left_str);
}

char	*get_next_line(int fd)
{
	static char	*left_str[500];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	left_str[fd] = get_buff(fd, left_str[fd]);
	if (!left_str[fd])
		return (NULL);
	line = get_line(left_str[fd]);
	left_str[fd] = get_new_buff(left_str[fd]);
	return (line);
}
