/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/09 10:16:35 by cyuzbas       #+#    #+#                 */
/*   Updated: 2021/12/13 11:16:24 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*update_container(char	*container)
{
	int		i;
	int		j;
	char	*updated;

	i = 0;
	while (container[i] && container[i] != '\n')
		i++;
	if (!container[i])
	{
		free(container);
		return (NULL);
	}
	updated = (char *)ft_calloc(sizeof(char), (ft_strlen(container) - i + 1));
	j = 0;
	i++;
	while (container[i] && updated)
	{
		updated[j] = container[i];
		j++;
		i++;
	}
	free (container);
	return (updated);
}

char	*get_line(char *container)
{
	int		i;
	char	*get_line;

	i = 0;
	if (!container[i])
		return (NULL);
	while (container[i] && container[i] != '\n')
		i++;
	get_line = (char *)ft_calloc(sizeof(char), (i + 2));
	if (!get_line)
		return (NULL);
	i = 0;
	while (container[i] && container[i] != '\n')
	{
		get_line[i] = container[i];
		i++;
	}
	if (container[i] == '\n')
		get_line[i] = '\n';
	return (get_line);
}

char	*ft_read(char *container, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		check_read;

	check_read = 1;
	while (check_read != 0 && !ft_strchr(container, '\n'))
	{
		check_read = read(fd, buffer, BUFFER_SIZE);
		if (check_read < 0)
		{
			free(container);
			return (NULL);
		}
		buffer[check_read] = '\0';
		container = ft_strjoin(container, buffer);
		if (container == NULL)
			check_read = 0;
	}
	return (container);
}

char	*get_next_line(int fd)
{
	static char	*container[1025];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1025)
		return (NULL);
	container[fd] = ft_read(container[fd], fd);
	if (container[fd] == NULL)
		return (NULL);
	line = get_line(container[fd]);
	container[fd] = update_container(container[fd]);
	if (line == NULL)
	{
		free (container[fd]);
		return (NULL);
	}
	return (line);
}
