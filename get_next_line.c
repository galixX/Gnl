/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbourdon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 14:06:31 by dbourdon          #+#    #+#             */
/*   Updated: 2016/02/24 11:57:03 by dbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_read(char **buff_stock, int fd)
{
	int		ret;
	char	*tmp;

	ret = 0;
	tmp = ft_strnew(BUFF_SIZE + 1);
	if (*buff_stock == NULL)
		*buff_stock = ft_strnew(BUFF_SIZE + 1);
	if (*buff_stock == NULL)
		return(-1);
	ret = read(fd, tmp, BUFF_SIZE);
	printf("Je viens de lire: %s\n Mon Buff_stock est: %s\n", tmp, *buff_stock);
	if (ret == -1)
		return(-1);
	*buff_stock = ft_strjoin(*buff_stock, tmp);
	printf("Apres mon join: %s\n", *buff_stock);
	free(tmp);
	return(ret);
}

int		ft_return(int ret, char *out, char **line, char **buff_stock, int i)
{
	*line = out;
	*buff_stock = *buff_stock + (i + 1);
	if (ret == 1)
		return(1);
	else
		return(0);
}

int		get_next_line(int fd, char **line)
{
	static char *buff_stock;
	char		*out;
	int			i;
	int			j;
	int			nb;

	i = 0;
	j = 0;
	nb = 0;
	out = ft_strnew(BUFF_SIZE);
	if (fd < 0)
		return(-1);
	if (buff_stock == NULL)
		if (ft_read(&buff_stock, fd) == -1)
			return(-1);
	while (i < BUFF_SIZE - nb)
	{
		if (buff_stock[i] == '\n')
			return(ft_return(1, out, line, &buff_stock, i));
		else if (buff_stock[i] == '\0')
		{
			nb = ft_read(&buff_stock, fd);
			if (nb == 0)
				return(ft_return(0, out, line, &buff_stock, i));
			if (nb == -1)
				return(-1);
			nb = i;
			i = -1;
			j = 0;
		}
		else if (buff_stock[i] == EOF)
			return(ft_return(0, out, line, &buff_stock, i));
		else
			out[j++] = buff_stock[i];
		i++;
	}
	return(ft_return(1, out, line, &buff_stock, i));
}
