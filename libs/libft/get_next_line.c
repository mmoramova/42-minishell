/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:13:14 by mmoramov          #+#    #+#             */
/*   Updated: 2023/04/25 16:14:00 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gnl_free(char **text)
{
	free(*text);
	*text = NULL;
	return (NULL);
}

char	*add_buffer(int fd, char *text)
{
	char	buffer[BUFFER_SIZE + 1];
	int		len_byte;

	len_byte = 1;
	buffer[0] = '\0';
	while (len_byte > 0 && !ft_gnl_strchr(buffer, '\n'))
	{
		len_byte = read(fd, buffer, BUFFER_SIZE);
		if (len_byte > 0)
		{
			buffer[len_byte] = '\0';
			text = ft_gnl_strjoin(text, buffer);
		}
	}
	if (len_byte < 0)
		return (ft_gnl_free(&text));
	return (text);
}

char	*get_lines(char *text)
{
	char	*line;
	int		len;

	len = 0;
	while (text[len] && text[len] != '\n')
		len++;
	if (text[len] == '\n')
		len++;
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_gnl_strlcpy(line, text, len + 1);
	return (line);
}

char	*update_text(char *text)
{
	char	*new_text;
	char	*end;
	int		len;

	end = ft_gnl_strchr(text, '\n');
	if (!end)
		return (ft_gnl_free(&text));
	else
		len = (end - text) + 1;
	if (!text[len])
		return (ft_gnl_free(&text));
	new_text = ft_gnl_substr(text, len, ft_gnl_strlen(text) - len);
	ft_gnl_free(&text);
	return (new_text);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*text = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!text || !ft_gnl_strchr(text, '\n'))
		text = add_buffer(fd, text);
	if (!text)
		return (NULL);
	line = get_lines(text);
	if (!line)
		return (ft_gnl_free(&text));
	text = update_text(text);
	return (line);
}
/* int main (int argc, char **argv)
{
    int fd;

    fd = open(argv[1], O_RDONLY);
    printf("|%s|\n\n", get_next_line(fd));
    //gcc -Wall -Werror -Wextra -D BUFFER_SIZE=xyz
	// get_next_line.c get_next_line_utils.c && ./a.out
}*/
