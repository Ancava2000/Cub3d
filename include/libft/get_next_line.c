/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:09:29 by acarro-v          #+#    #+#             */
/*   Updated: 2025/11/27 07:19:15 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_gnl(char *buffer, char *temp)
{
	char	*joined;

	joined = ft_strjoin_gnl(buffer, temp);
	free(buffer);
	return (joined);
}

char	*buffer_rest(char *buffer)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	temp = ft_calloc_gnl(ft_strlen_gnl(buffer) - i + 1, sizeof(char));
	i++;
	while (buffer[i] != '\0')
		temp[j++] = buffer[i++];
	free(buffer);
	return (temp);
}

char	*buffer_copy(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	line = 0;
	if (buffer[i] == '\0')
		return (0);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		line = ft_calloc_gnl((i + 2), sizeof(char));
	else
		line = ft_calloc_gnl((i + 1), sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*read_file(char *buffer, int fd)
{
	char	*temp;
	int		i;

	if (!buffer)
		buffer = ft_calloc_gnl(1, sizeof(char));
	temp = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	i = 1;
	while (i > 0)
	{
		i = read(fd, temp, BUFFER_SIZE);
		if (i == -1)
		{
			free(temp);
			free(buffer);
			return (NULL);
		}
		temp[i] = '\0';
		buffer = ft_free_gnl(buffer, temp);
		if (ft_strchr_gnl(temp, '\n'))
			break ;
	}
	free(temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0) 
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = read_file(buffer, fd);
	if (buffer == 0)
	{
		free(buffer);
		return (0);
	}
	line = buffer_copy(buffer);
	buffer = buffer_rest(buffer);
	return (line);
}
