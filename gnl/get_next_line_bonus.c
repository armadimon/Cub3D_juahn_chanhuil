#include "get_next_line_bonus.h"

int ft_strchr(char *s)
{
	int i = 0;

	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int ft_strlen(char *s)
{
	int i = 0;


	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}


char	*ft_strjoin(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!left_str)
	{
		left_str = malloc(1);
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = malloc(ft_strlen(left_str) + ft_strlen(buff) + 1);
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i] != '\0')
			str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
	free(left_str);
	return (str);
}


char *get_line(char *buff)
{
	int i = 0;
	char *str;

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
	int		i = 0;
	int		j = 0;
	char	*str;


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

char *get_buff(int fd, char *left_str)
{
	char	*buff;
	int		ret;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	ret = 1;
	while (!ft_strchr(left_str) && ret != 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[ret] = '\0';
		left_str = ft_strjoin(left_str, buff);
	}
	free(buff);
	return (left_str);
}

char *get_next_line(fd)
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
