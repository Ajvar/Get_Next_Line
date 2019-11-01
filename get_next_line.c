/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:56:20 by jcueille          #+#    #+#             */
/*   Updated: 2019/11/01 17:25:04 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>


int get_next_line(int fd, char **line)
{
	int ret;
	static char *buff = NULL;
	char *str;
	char *tmp;
	size_t i;

	i = 0;
	if (line == NULL || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	if (!(line[0]= ft_calloc(BUFFER_SIZE, 1)))
		return (-1);

/*----------SI QQ CHOSE DANS TAMPON--------------*/
	if (buff)
		{
			if (ft_strchr(buff, '\n'))
				{
					while(buff[i] != '\n')
						i++;
					line[0] = ft_substr(buff, 0, i);
					buff = ft_strndup(&buff[i], ft_strlen(&buff[i]));
					return (1);
				}
				//line[0] = strndup(buff, ft_strlen(buff));
				//return 1;
		}
/*---------------------*/
	buff = NULL;
	str = malloc(BUFFER_SIZE);
	buff = ft_calloc(BUFFER_SIZE,1);
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
			while(line[i] != '\n')
				i++;
			buff = ft_strndup(&str[i], ft_strlen(&str[i]));
			line[0] = ft_strndup(str, i);
			i++;
			free(str);
			if (ret == 0)
				return (0);
			return (1);
		}
		line[0] = ft_strndup(str, ft_strlen(str));
		return (1);
	}
	return (0);
}

/*int main(void)
{
	int fd;
	fd = open("test.txt", O_RDWR);
	char **line;
	line = malloc(sizeof(line) * 10);
	int n;
	n = get_next_line(fd, line);
	printf("%s\n",line[0]);
	n = get_next_line(fd, line);
	printf("%s\n",line[0]);
	n = get_next_line(fd, line);
	printf("%s\n",line[0]);
	free(line);
	close(fd);
	return (0);
}*/

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

int	main(void)
{
        char            *buffer = NULL;
        int                     i, fd;
        int                     test_count;
        char const      *tests[100] = {
                "test.txt",
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
}