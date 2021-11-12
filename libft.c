/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:28:01 by lajudy            #+#    #+#             */
/*   Updated: 2021/11/11 17:54:19 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
}

void	free_after_split(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
	{
		free(argv[i]);
		argv[i] = NULL;
		i++;
	}
	free(argv);
}

// char	*ft_strchr(const char *s, int c)
// {
// 	char	*str;

// 	str = (char *)s;
// 	c = (unsigned char)c;
// 	while (*str != '\0')
// 	{
// 		if (*str == c)
// 			return (str);
// 		str++;
// 	}
// 	if (*str == '\0' && c == '\0')
// 		return (str);
// 	else
// 		return (NULL);
// }
