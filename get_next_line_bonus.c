/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhilda <rhilda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 12:40:17 by rhilda            #+#    #+#             */
/*   Updated: 2020/11/15 14:16:59 by rhilda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char		*next_line(char *file)
{
	char		*nextl;
	int			i;
	int			j;

	if (!file)
		return (0);
	i = 0;
	j = 0;
	while (file[i] && file[i] != '\n')
		i++;
	if (!file[i])
	{
		free(file);
		return (0);
	}
	if (!(nextl = malloc(sizeof(char) * (ft_strlen(file) - i) + 1)))
		return (0);
	i++;
	while (file[i])
		nextl[j++] = file[i++];
	nextl[j] = '\0';
	free(file);
	return (nextl);
}

static char		*getlline(char *s)
{
	char		*line;
	int			i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!(line = malloc(sizeof(char) * i + 1)))
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static int		has_linebreak(char *s)
{
	int			i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static char	*file[OPEN_MAX];
	char		*temp;
	int			readen;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	readen = 1;
	if (!(temp = malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	while (!has_linebreak(file[fd]) && readen != 0)
	{
		if ((readen = read(fd, temp, BUFFER_SIZE)) < 0)
		{
			free(temp);
			return (-1);
		}
		temp[readen] = '\0';
		file[fd] = ft_strjoin(file[fd], temp);
	}
	free(temp);
	*line = getlline(file[fd]);
	file[fd] = next_line(file[fd]);
	if (readen == 0)
		return (0);
	return (1);
}
