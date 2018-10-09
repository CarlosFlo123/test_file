/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 18:53:48 by mikim             #+#    #+#             */
/*   Updated: 2018/10/07 18:00:24 by cflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_new_line(char **file, char **line, int fd, int read_bits)
{
	char	*tmp;
	int		len;

	len = 0;
	while (file[fd][len] != '\n' && file[fd][len] != '\0')
		len++;
	if (file[fd][len] == '\n')
	{
		*line = ft_strsub(file[fd], 0, len);
		tmp = ft_strdup(file[fd] + len + 1);
		free(file[fd]);
		file[fd] = tmp;
		if (file[fd][0] == '\0')
			ft_strdel(&file[fd]);
	}
	else if (file[fd][len] == '\0')
	{
		if (read_bits == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(file[fd]);
		ft_strdel(&file[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*file[255];
	char		buf[BUFF_SIZE + 1];
	char		*tmp;
	int			read_bits;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((read_bits = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[read_bits] = '\0';
		if (file[fd] == NULL)
			file[fd] = ft_strnew(1);
		tmp = ft_strjoin(file[fd], buf);
		free(file[fd]);
		file[fd] = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (read_bits < 0)
		return (-1);
	else if (read_bits == 0 && (file[fd] == NULL || file[fd][0] == '\0'))
		return (0);
	return (ft_new_line(file, line, fd, read_bits));
}
