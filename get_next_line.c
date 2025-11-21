/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanton <mdanton@42student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:11:21 by mdanton           #+#    #+#             */
/*   Updated: 2025/11/21 16:11:21 by mdanton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(const char *s)
{
	int	counter;

	counter = 0;
	while (*s++)
		counter++;
	return (counter);
}

int	ft_strlen_newline(const char *s, int max)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (len < max)
	{
		if (*s == '\0')
			return (len);
		if (*s == '\n')
			return (len + 1);
		len++;
		s++;
	}
	return (-1);
}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*str;

	str = (char *)malloc(ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	ft_strlcat(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	*construct_str(char *buffers[512], int fd, int max)
{
	int		len;
	char	*str;
	char	*new_buf;

	len = ft_strlen_newline(buffers[fd], max);
	if (len > 0)
	{
		str = ft_strndup(buffers[fd], len);
		ft_strlcat(buffers[fd], buffers[fd] + len, max - len);
		return (str);
	}
	new_buf = (char *)malloc(sizeof(char) * (2048 * 2));
	if (!new_buf)
		return (NULL);
	return (NULL);
}

int	init_buffer(char *buffers[512], int fd, int *offset, char **s)
{
	char	*str;

	if (!buffers[fd])
	{
		buffers[fd] = (char *)malloc(sizeof(char) * (2048));
		if (!buffers[fd])
			return (1);
		*offset = 0;
	}
	else
	{
		str = construct_str(buffers, fd, 2048);
		if (str)
			*s = str;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	int			run;
	int			offset;
	int			chars_read;
	char		*str;
	static char	*buffers[512];

	if (!fd)
		return (NULL);
	str = NULL;
	if (init_buffer(buffers, fd, &offset, &str))
		return (NULL);
	if (str)
		return (str);
	run = 1;
	while (run)
	{
		chars_read = read(fd, buffers[fd] + offset, 2047 - offset);
		if (!chars_read)
			return (NULL);
		if (chars_read == 2047)
			buffers[fd][offset + 2047] = '\0';
		str = construct_str(buffers, fd, chars_read);
		if (str)
			return (str);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*cur_line;

	if (argc < 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (!fd)
		return (1);
	cur_line = get_next_line(fd);
	while (cur_line)
	{
		printf("%s", cur_line);
		cur_line = get_next_line(fd);
	}
	return (0);
}
