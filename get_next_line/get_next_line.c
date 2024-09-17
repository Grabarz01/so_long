/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:13:59 by fgrabows          #+#    #+#             */
/*   Updated: 2024/09/13 13:35:40 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_cut_buf(char *full)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (full[i] && full[i] != '\n')
		i++;
	if (full[i] == '\n')
		i++;
	if (!full[i])
	{
		free(full);
		return (NULL);
	}
	new = malloc(sizeof(char) * (ft_strlen(full) - i + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (full[i])
		new[j++] = full[i++];
	new[j] = '\0';
	free(full);
	return (new);
}

static char	*ft_set_new_line(char *full)
{
	char	*line;
	int		i;

	i = 0;
	if (!full[i])
		return (NULL);
	while (full[i] && full[i] != '\n')
		i++;
	if (full[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = -1;
	while (full[++i] && full[i] != '\n')
		line[i] = full[i];
	if (full[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_read_line(int fd, char *full)
{
	char	*buff;
	int		rbytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	rbytes = 1;
	while (rbytes != 0 && !ft_strchr(full, '\n'))
	{
		rbytes = read(fd, buff, BUFFER_SIZE);
		if (rbytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rbytes] = '\0';
		full = ft_strjoin_2(full, buff);
	}
	free(buff);
	return (full);
}

char	*get_next_line(int fd)
{
	static char	*buff[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff[fd] = ft_read_line(fd, buff[fd]);
	if (!buff[fd])
		return (NULL);
	line = ft_set_new_line(buff[fd]);
	buff[fd] = ft_cut_buf(buff[fd]);
	return (line);
}

// int main()
// {
// 	fd = open("./sth.txt", O_RDONLY);
// 	fd1 = open("./sth1.txt", O_WRONLY);
// }
/*int main()
{
    char *str;
    int fd, fd1, fd2;
    fd = open("./sth.txt", O_RDONLY);
	fd1 = open("./sth1.txt", O_RDONLY);
	fd2 = open("./sth2.txt", O_RDONLY);
	int i = 0;
	while(i++<9)
    {
		str = get_next_line(fd);
		printf("\n%d.RESULT:%s END_OF RESULT",i,str);
		free(str);
	}
	i = 0;
	while(i++<9)
    {
		str = get_next_line(fd1);
		printf("\n%d.RESULT:%s END_OF RESULT",i,str);
		free(str);
	}
	i = 0;
	while(i++<9)
    {
		str = get_next_line(fd2);
		printf("\n%d.RESULT:%s END_OF RESULT",i,str);
		free(str);
	}
	return(0);
}*/
/*int main() {
    // Test dla standardowego wejścia (stdin)
    printf("Testowanie czytania z stdin:\n");
    printf("Proszę wprowadzić kilka linii tekstu. Wpisz '0', aby zakończyć.\n");
    char *line;
    while ((line = get_next_line(0)) != NULL && line[0] != '0') {
        printf("Odczytano linię: %s\n", line);
        free(line);
    }
	printf("Proszę wprowadzić kilka linii tekstu. Wpisz '0', aby zakończyć.\n");
	while ((line = get_next_line(1)) != NULL && line[0] != '0') {
        printf("Odczytano linię: %s\n", line);
        free(line);
    }
	printf("Proszę wprowadzić kilka linii tekstu. Wpisz '0', aby zakończyć.\n");
	while ((line = get_next_line(2)) != NULL && line[0] != '0') {
        printf("Odczytano linię: %s\n", line);
        free(line);
    }
	printf("Proszę wprowadzić kilka linii tekstu. Wpisz '0', aby zakończyć.\n");
	while ((line = get_next_line(3)) != NULL && line[0] != '0') {
        printf("Odczytano linię: %s\n", line);
        free(line);
    }
}*/
