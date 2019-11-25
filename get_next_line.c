/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:56:20 by jcueille          #+#    #+#             */
/*   Updated: 2019/11/25 18:04:52 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

int ft_buffcheck(char** buff, char** line, char** tmp, size_t i)
{
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
		//free(buff);
		*buff = NULL;
	}
	return (0);
}

int				get_next_line(int fd, char **line)
{
	int			ret;
	static char	*buff = NULL;
	char		*str;
	char		*tmp;
	size_t		i;

	i = 0;
	tmp = NULL;
	if (line == NULL || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	if (!(line[0] = ft_strdup("")))
		return (-1);
	if (ft_buffcheck(&buff, line, &tmp, i) == 1)
		return (1);
	str = ft_calloc((BUFFER_SIZE + 1), 1);
	while ((ret = read(fd, str, BUFFER_SIZE)))
	{
		if (ret == -1)
			return (-1);
		str[ret] = '\0';
		tmp = ft_strdup(line[0]);
		free(line[0]);
		line[0] = ft_strjoin(tmp, str);
		free(tmp);
		if (ft_strchr(line[0], '\n'))
		{
			i = 0;
			while (line[0][i] != '\n')
				i++;
			buff = ft_strdup(ft_strchr(line[0], '\n') + 1);
			tmp = ft_strdup(line[0]);
			free(line[0]);
			line[0] = ft_substr(tmp, 0, i);
			free(tmp);
			free(str);
			return (1);
		}
	}
	free(str);
	if (ret > 0)
		return (1);
	return (0);
}

/*int main(void)
{
	int fd;
	fd = open("tests.txt", O_RDWR);
	char **line;
	line = malloc(sizeof(line) * 10);
	int n = 1;
	//while (n > 0)
	//{
	n = get_next_line(fd, line);
	printf("%s\n",line[0]);
	free(line[0]);
	//}
	close(fd);
	while(1);
	return (0);
}*/
/*
void    sigcatch()
{
        write(2, "Your GNL got killed because it got stuck \n", 42);
        exit(-1);
}

void
        test_fd(char **buffer, char const *filename, int fd)
{
        int     r;

        alarm(5);
        signal(SIGALRM, sigcatch);
        if (fd == STDIN_FILENO)
                printf("Reading stdin...\n---\n");
        else
                printf("Reading %s...\n---\n", filename);

        while ((r = get_next_line(fd, buffer)) > 0)
        {
                printf("%2d-%s\n", r, *buffer);
                if (*buffer)
                {
                        free(*buffer);
                        *buffer = NULL;
                }
        }

        if (r >= 0)
                printf("%2d-%s\n---\n", r, *buffer);
        else
                printf("%2d#error\n---\n", r);

        if (*buffer)
        {
                free(*buffer);
                *buffer = NULL;
        }
        alarm(0);
}

int main(void)
{
        char            *buffer = NULL;
        int                     i, fd;
        int                     test_count;
        char const      *tests[100] = {
				"tests.txt",
                NULL
        };

        test_count = 0;
        while (tests[test_count])
                test_count++;
        i = 0;
        while (i < test_count)
        {
                fd = open(tests[i], O_RDONLY);
                test_fd(&buffer, tests[i++], fd);
                close(fd);
        }
        test_fd(&buffer, "Invalid file descriptor", 42);
        test_fd(&buffer, NULL, STDIN_FILENO);
        return (0);
}*/