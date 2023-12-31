/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 07:04:07 by akajjou           #+#    #+#             */
/*   Updated: 2023/12/31 11:55:57 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*join_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

char	*get_ready(char *buffer)
{
	int		i;
	int		j;
	char	*ret_buffer;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	ret_buffer = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		ret_buffer[j++] = buffer[i++];
	free(buffer);
	return (ret_buffer);
}

char	*clean_ret(char *buffer)
{
	char	*ret_buffer;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	ret_buffer = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		ret_buffer[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		ret_buffer[i++] = '\n';
	return (ret_buffer);
}

char	*readwithbuffer(int fd, char *buffer)
{
	char	*tmp_buffer;
	ssize_t	bytereads;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	tmp_buffer = malloc((size_t)BUFFER_SIZE + 1);
	bytereads = 1;
	while (bytereads > 0)
	{
		bytereads = read(fd, tmp_buffer, (size_t)BUFFER_SIZE);
		if (bytereads == -1)
			return (free(buffer), free(tmp_buffer), NULL);
		tmp_buffer[bytereads] = '\0';
		buffer = join_free(buffer, tmp_buffer);
		if (ft_strchr(tmp_buffer, '\n'))
			break ;
	}
	free(tmp_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*finale;

	if (fd < 0 || (size_t)BUFFER_SIZE <= 0 || fd > 1024 )
		return (NULL);
	buffer[fd] = readwithbuffer(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	finale = clean_ret(buffer[fd]);
	buffer[fd] = get_ready(buffer[fd]);
	return (finale);
}
