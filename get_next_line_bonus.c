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

#include "get_next_line_bonus.h"

char	*read_and_stash(int fd, char *stash)
{
	char	*temp_buf;
	int		bytes_read;

	temp_buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!temp_buf)
		free(stash);
	if (!temp_buf)
		return (NULL);
	bytes_read = 1;
	while (!ft_has_newline(stash) && bytes_read != 0)
	{
		bytes_read = read(fd, temp_buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp_buf);
			free(stash);
			return (NULL);
		}
		temp_buf[bytes_read] = '\0';
		stash = ft_strjoin_and_free_old(stash, temp_buf);
		if (!stash)
			return (NULL);
	}
	free(temp_buf);
	return (stash);
}

char	*extract_line(char *stash)
{
	char	*str;
	int		len;

	len = ft_strlen_newline(stash);
	str = ft_strndup(stash, len);
	return (str);
}

char	*keep_rest(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	i++;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffers[512];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 511)
		return (NULL);
	buffers[fd] = read_and_stash(fd, buffers[fd]);
	if (!buffers[fd])
		return (NULL);
	if (buffers[fd][0] == '\0')
	{
		free(buffers[fd]);
		buffers[fd] = NULL;
		return (NULL);
	}
	line = extract_line(buffers[fd]);
	buffers[fd] = keep_rest(buffers[fd]);
	return (line);
}

// int	main(int argc, char **argv)
//{
//	int		fd;
//	int		max;
//	int		run;
//	char	*cur_line;
//
//	if (argc < 2)
//		return (1);
//	fd = open(argv[1], O_RDONLY);
//	if (fd < 0)
//		return (1);
//	run = 1;
//	max = 7;
//	while (run)
//	{
//		cur_line = get_next_line(fd);
//		if (!cur_line || !max--)
//			run = 0;
//		else
//			printf("%s", cur_line);
//	}
//	return (0);
//}
