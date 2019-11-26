/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo <jo@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:56:20 by jcueille          #+#    #+#             */
/*   Updated: 2019/11/26 16:51:57 by jo               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

static int		ft_buffcheck(char** buff, char** line, char** tmp)
{
	size_t i;

	i = 0;
	if (*buff)
	{
		free(line[0]);
		if (ft_strchr(*buff, '\n'))
		{
			while (buff[0][i] != '\n' && buff[0][i])
				i++;
			line[0] = ft_substr(*buff, 0, i);
			*tmp = ft_strdup(ft_strchr(*buff, '\n') + 1);
			free(*buff);
			*buff = NULL;
			*buff = ft_substr(*tmp, 0, ft_strlen(*tmp));
			free(*tmp);
			return (1);
		}
		line[0] = strdup(*buff);
		free(*buff);
		*buff = NULL;
	}
	return (0);
}

int ft_read(int fd, char** str, char** line, char** buff)
{
	size_t i;
	int ret;
	char *tmp;
	
	i = 0;
	*str = ft_calloc((BUFFER_SIZE + 1), 1);
	while ((ret = read(fd, *str, BUFFER_SIZE)))
	{
		if (ret == -1)
			return (-1);
		str[0][ret] = '\0';
		tmp = ft_strdup(line[0]);
		free(line[0]);
		line[0] = ft_strjoin(tmp, *str);
		free(tmp);
		if (ft_strchr(line[0], '\n'))
		{
			while (line[0][i] != '\n')
				i++;
			if (!(*buff = ft_strdup(ft_strchr(line[0], '\n') + 1)))
				return (-1);
			if(!(tmp = ft_strdup(line[0])))
				return (-1);
			free(line[0]);
			line[0] = ft_substr(tmp, 0, i);
			free(tmp);
			free(*str);
			return (1);
		}
	}
	if (str)
		free(*str);
	return (ret);
}

int				get_next_line(int fd, char **line)
{
	static char	*buff = NULL;
	char		*str;
	char		*tmp;
	int 		ret;

	tmp = NULL;
	if (line == NULL || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	if (!(line[0] = ft_strdup("")))
		return (-1);
	if (ft_buffcheck(&buff, line, &tmp) == 1)
		return (1);
	ret = ft_read(fd, &str, line, &buff);
	if (ret > 0)
		return (1);
	else if (ret == -1)
		return -1;
	return (0);
}
