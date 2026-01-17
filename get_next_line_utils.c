/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-05 12:49:08 by irabhi            #+#    #+#             */
/*   Updated: 2024-11-05 12:49:08 by irabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int	fill_buffer(char *read_line, int fd)
{
	ssize_t	read_bytes;

	if (!read_line || fd < 0)
		return (0);
	read_bytes = read(fd, read_line, BUFFER_SIZE);
	if (read_bytes <= 0)
		return (0);
	read_line[read_bytes] = 0;
	return (read_bytes);
}

int	find_new_line(char *next_line)
{
	size_t	i;

	if (next_line == NULL)
		return (0);
	i = 0;
	while (next_line[i] != '\0')
	{
		if (next_line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*duplicate(char *str, size_t start, size_t end)
{
	char	*result;
	size_t	size;
	size_t	i;

	if (!str || start > end)
		return (NULL);
	size = end - start;
	result = malloc(size + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (start < end)
	{
		result[i] = str[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}

size_t	str_len(char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
