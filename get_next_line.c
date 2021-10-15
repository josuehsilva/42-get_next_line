/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joshenri <joshenri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 10:00:47 by joshenri          #+#    #+#             */
/*   Updated: 2021/10/16 00:45:10 by joshenri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s2;
	size_t	slen;

	i = -1;
	slen = ft_strlen(s1);
	s2 = malloc((slen + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	while (s1[++i])
		s2[i] = s1[i];
	s2[i] = '\0';
	return (s2);
}

static char	*get_line(char **text)
{
	size_t	i;
	char	*temp;
	char	*line_output;

	i = 0;
	line_output = NULL;
	while ((*text)[i] != '\n' && (*text)[i])
		i++;
	if ((*text)[i] == '\n')
	{
		line_output = ft_substr(*text, 0, i + 1);
		temp = ft_strdup(*text + i + 1);
		free(*text);
		*text = temp;
		if (!**text)
		{
			free(*text);
			*text = NULL;
		}
		return (line_output);
	}
	line_output = ft_strdup(*text);
	free(*text);
	*text = NULL;
	return (line_output);
}

static void	read_file(int fd, char *buffer, char **b_backup, ssize_t r_bytes)
{
	char	*temp_buffer;

	temp_buffer = NULL;
	while (r_bytes > 0)
	{
		buffer[r_bytes] = '\0';
		if (*b_backup == NULL)
			*b_backup = ft_strdup("");
		temp_buffer = ft_strjoin(*b_backup, buffer);
		free(*b_backup);
		*b_backup = temp_buffer;
		if (ft_strchr(buffer, '\n'))
			break ;
		r_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	free (buffer);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*b_backup = NULL;
	ssize_t		read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	read_file(fd, buffer, &b_backup, read_bytes);
	if (read_bytes < 0)
		return (NULL);
	if (!read_bytes && (!b_backup || !*b_backup))
		return (NULL);
	return (get_line(&b_backup));
}
