#include "get_next_line.h"

char	*join_strs(char *next_line, char *read_line)
{
	char	*tmp;
	size_t	size;
	size_t	i;
	size_t	j;

	if (!read_line)
		return (NULL);
	if (next_line == NULL)
		return (duplicate(read_line, 0, str_len(read_line)));
	size = str_len(next_line) + str_len(read_line) + 1;
	tmp = malloc(size);
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (next_line[i])
	{
		tmp[i] = next_line[i];
		i++;
	}
	j = 0;
	while (read_line[j])
		tmp[i++] = read_line[j++];
	tmp[i] = '\0';
	free(next_line);
	return (tmp);
}

char	*strip_line(char **next_line)
{
	char	*rest;
	char	*line;
	char	*tmp;
	size_t	i;

	if (!next_line || !*next_line)
		return (NULL);
	tmp = *next_line;
	i = 0;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == '\n')
		i++;
	line = duplicate(*next_line, 0, i);
	rest = duplicate(*next_line, i, str_len(*next_line));
	if (!line || !rest)
	{
		free(line);
		free(rest);
		return (NULL);
	}
	free(*next_line);
	*next_line = rest;
	return (line);
}

void	*fail_free(char **next_line)
{
	if (*next_line)
	{
		free(*next_line);
		*next_line = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*next_line;
	char		*read_line;
	ssize_t		read_bytes;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (fail_free(&next_line));
	while (!find_new_line(next_line))
	{
		read_line = malloc((size_t)BUFFER_SIZE + 1);
		read_bytes = fill_buffer(read_line, fd);
		if (read_bytes <= 0)
		{
			free(read_line);
			if (next_line && *next_line)
				return (strip_line(&next_line));
			free(next_line);
			next_line = NULL;
			return (NULL);
		}
		next_line = join_strs(next_line, read_line);
		free(read_line);
		if (!next_line)
			return (NULL);
	}
	return (strip_line(&next_line));
}
