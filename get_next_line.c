/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joshenri <joshenri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 10:00:47 by joshenri          #+#    #+#             */
/*   Updated: 2021/10/15 23:39:47 by joshenri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char **text)
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
		temp = ft_strdup(*text + i);
		//printf("\n\n*** %s ***\n\n", temp);
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

static void	read_file(int fd, char *buffer, char **b_backup, ssize_t read_bytes)
{
	char	*temp_buffer;

	temp_buffer = NULL;
	while (read_bytes > 0)
	{
		buffer[read_bytes] = '\0';
		if (*b_backup == NULL)
			*b_backup = ft_strdup("");
		temp_buffer = ft_strjoin(*b_backup, buffer);
		free(*b_backup);
		*b_backup = temp_buffer;
		if (ft_strchr(buffer, '\n'))
			break ;
		read_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	free (buffer);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*b_backup;
	ssize_t		read_bytes;

	b_backup = NULL;
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
