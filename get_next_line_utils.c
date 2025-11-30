/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: git <git@mart1d4.me>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:35:42 by git               #+#    #+#             */
/*   Updated: 2025/11/22 03:51:38 by git              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	counter;

	counter = 0;
	while (s && *s++)
		counter++;
	return (counter);
}

int	ft_strlen_newline(const char *s)
{
	int	len;

	len = 0;
	while (s)
	{
		if (*s == '\0')
			return (len);
		if (*s == '\n')
			return (len + 1);
		len++;
		s++;
	}
	return (0);
}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
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

int	ft_has_newline(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

char	*ft_strjoin_and_free_old(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s1 && s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		str[j++] = s2[i++];
	str[j] = 0;
	free(s1);
	return (str);
}
