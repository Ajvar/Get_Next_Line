/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:56:20 by jcueille          #+#    #+#             */
/*   Updated: 2019/11/28 10:55:55 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

int				ft_free(char **line, char **buff)
{
	if (line[0])
		free(line[0]);
	if (*buff)
	{
		free(*buff);
		*buff = NULL;
	}
	return (-1);
}

static int		ft_buffcheck(char **buff, char **line, char **tmp)
{
	size_t		i;

	if (*buff)
	{
		free(line[0]);
		if (ft_strchr(*buff, '\n'))
		{
			i = ft_strchr(*buff, '\n') - *buff;
			if (!(line[0] = ft_substr(*buff, 0, i)))
				return (ft_free(line, buff));
			if (!(*tmp = ft_substr(*buff, i + 1, ft_strlen(&buff[0][i + 1]))))
				return (ft_free(line, buff));
			free(*buff);
			*buff = NULL;
			if (!(*buff = ft_substr(*tmp, 0, ft_strlen(*tmp))))
				return (ft_free(line, buff));
			free(*tmp);
			return (1);
		}
		if (!(line[0] = ft_substr(*buff, 0, ft_strlen(*buff))))
			return (ft_free(line, buff));
		free(*buff);
		*buff = NULL;
	}
	return (0);
}

static int		ft_check_return(char **line, char **buff
, char **tmp, char **str)
{
	size_t		i;

	if (ft_strchr(line[0], '\n'))
	{
		i = ft_strchr(line[0], '\n') - line[0];
		if (!(*buff = ft_substr(line[0], i + 1
		, ft_strlen(&line[0][i + 1]))))
			return (ft_free(line, buff));
		if (!(*tmp = ft_substr(line[0], 0, ft_strlen(line[0]))))
			return (ft_free(line, buff));
		free(line[0]);
		if (!(line[0] = ft_substr(*tmp, 0, i)))
			return (ft_free(tmp, str));
		free(*tmp);
		free(*str);
		return (1);
	}
	return (0);
}

static int		ft_read(int fd, char **str, char **line, char **buff)
{
	int			ret;
	char		*tmp;

	*str = ft_calloc((BUFFER_SIZE + 1), 1);
	while ((ret = read(fd, *str, BUFFER_SIZE)))
	{
		if (ret == -1)
			return (-1);
		str[0][ret] = '\0';
		if (!(tmp = ft_substr(line[0], 0, ft_strlen(line[0]))))
			return (ft_free(line, buff));
		free(line[0]);
		if (!(line[0] = ft_strjoin(tmp, *str)))
			return (ft_free(&tmp, buff));
		free(tmp);
		if ((ret = ft_check_return(line, buff, &tmp, str)) != 0)
			return (ret);
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
	int			ret;

	tmp = NULL;
	if (line == NULL || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	if (!(line[0] = ft_substr("", 0, 0)))
		return (ft_free(line, &buff));
	ret = ft_buffcheck(&buff, line, &tmp);
	if (ret > 0)
		return (1);
	else if (ret == -1)
		return (-1);
	ret = ft_read(fd, &str, line, &buff);
	if (ret > 0)
		return (1);
	else if (ret == -1)
		return (-1);
	return (0);
}
