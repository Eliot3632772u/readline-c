/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-05 12:54:21 by irabhi            #+#    #+#             */
/*   Updated: 2024-11-05 12:54:21 by irabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define MAX_FD 10240

char	*get_next_line(int fd);
int		fill_buffer(char *read_line, int fd);
int		find_new_line(char *next_line);
char	*duplicate(char *str, size_t start, size_t end);
size_t	str_len(char *str);
char	*join_strs(char *next_line, char *read_line);
char	*strip_line(char **next_line);
void	*fail_free(char **next_line, int fd);
#endif