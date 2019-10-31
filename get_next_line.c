/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:56:20 by jcueille          #+#    #+#             */
/*   Updated: 2019/10/31 18:33:23 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

int get_next_line(int fd, char **line)
{
	int res;
	int i;
	int j;
	static char tmp[BUFFER_SIZE + 2];
	char *end;

	j = 0;
	tmp[BUFFER_SIZE + 1] = '\0';
	while (1)
	{
		if (!(read(fd, tmp, BUFFER_SIZE)))
			return (-1);
		printf("%s %lu\n", tmp, strlen(tmp));
		i = 0;
/*--------Je rentre dans mon tampon----------*/
		while (tmp[i])
		{
			printf("1");
/*----------Si je croise \n------------------*/
			if (tmp[i] == '\n')
				{	
					i++;
					j = i;
					memmove(tmp, &tmp[i], strlen(&tmp[i]));
					tmp[j] = '\0';
					printf("%s", tmp);
				}
			*line[i] = tmp[i];
			//printf
			i++;
		}

		
		break ;
	}
	
	return (res);
}

int main()
{
	int fd = open("test.txt", O_RDWR);
	char **line;
	int n = get_next_line(fd, line);
	n = get_next_line(fd, line);
}