/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 11:59:53 by jcueille          #+#    #+#             */
/*   Updated: 2019/11/01 17:16:44 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		*ft_calloc(size_t count, size_t size)
{
	int		i;
	void	*res;

	i = 0;
	if (!(res = malloc(count * size)))
		return (NULL);
	while (i < (int)count * (int)size)
	{
		*(char*)(res + i) = '\0';
		i++;
	}
	return (res);
}

size_t		ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char		*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	s_len;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (!(res = (char *)ft_calloc(len + 1, sizeof(*res))))
		return (NULL);
	if (start < s_len)
		while (i < len && s[start])
			res[i++] = s[start++];
	return (res);
}

char		*ft_strdup(const char *s1)
{
	char	*res;
	int		i;

	i = 0;
	if (!(res = malloc(ft_strlen(s1) + 1)))
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char		*ft_strndup(const char *s1, size_t len)
{
	char	*res;
	int		i;

	i = 0;
	if (!(res = malloc(len + 1)))
		return (NULL);
	while (s1[i] && len)
	{
		res[i] = s1[i];
		i++;
		len--;
	}
	res[i] = '\0';
	return (res);
}
