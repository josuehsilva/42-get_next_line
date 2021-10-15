/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joshenri <joshenri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 10:00:54 by joshenri          #+#    #+#             */
/*   Updated: 2021/10/15 22:48:41 by joshenri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			size;
	unsigned char	slen;
	char			*substr;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (slen <= start)
		return (ft_strdup(""));
	if ((slen - start) > len)
		size = len;
	else
		size = slen - start;
	substr = (char *)malloc(size + 1);
	if (!substr)
		return (0);
	ft_strlcpy(substr, s + start, size + 1);
	return (substr);
}

char	*ft_strdup(const char *str)
{
	char	*p;
	int		strlen;

	strlen = ft_strlen(str);
	p = malloc(sizeof(char) * strlen + 1);
	if (!p)
		return (0);
	ft_strlcpy(p, str, (strlen + 1));
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	newstr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	ft_strlcpy(newstr, s1, ft_strlen(s1) + 1);
	ft_strlcat(newstr, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (newstr);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	i = 0;
	len = ft_strlen(dst);
	while (src[i] != '\0' && (len + 1) < dstsize)
		dst[len++] = src[i++];
	dst[len] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	lensrc;

	i = 0;
	lensrc = ft_strlen(src);
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (lensrc);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (0);
}
