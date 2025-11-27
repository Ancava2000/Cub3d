/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:10:24 by acarro-v          #+#    #+#             */
/*   Updated: 2025/11/27 06:33:00 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc_gnl(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = malloc(count * size);
	if (!ptr)
	{
		return (0);
	}
	i = 0;
	while (i < (count * size))
		ptr[i++] = 0;
	return (ptr);
}

int	ft_strlen_gnl(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == c)
		return (s);
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*s;
	int		i;

	s = malloc((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1) * sizeof(char));
	if (!s || !s1 || !s2)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		s[i] = s1[i];
	i = -1;
	while (s2[++i] != '\0')
		s[ft_strlen_gnl(s1) + i] = s2[i];
	s[ft_strlen_gnl(s1) + i] = '\0';
	return (s);
}
