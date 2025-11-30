/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: git <git@mart1d4.me>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:31:39 by git               #+#    #+#             */
/*   Updated: 2025/11/22 03:31:39 by git              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_strlen(const char *s);
int		ft_strlen_newline(const char *s);
char	*ft_strndup(const char *s, int n);
int		ft_has_newline(char *s);
char	*ft_strjoin_and_free_old(char *s1, char *s2);

char	*get_next_line(int fd);

#endif // !GET_NEXT_LINE_H
