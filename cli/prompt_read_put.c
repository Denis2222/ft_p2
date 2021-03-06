/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_read_put.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 22:54:10 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/11/04 05:42:58 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

static void	check_put_file_cat(t_client *c, char *str, char *filename)
{
	ft_bzero(str, PATH_MAX);
	ft_strcat(str, c->pwd);
	ft_strcat(str, "/");
	ft_strcat(str, filename);
}

static int	check_put_file(t_client *c, char *filename)
{
	char		str[PATH_MAX];
	int			fd;
	struct stat	buf;
	char		*msg;

	check_put_file_cat(c, str, filename);
	fd = open(str, O_RDONLY);
	if (fd <= 0)
	{
		writemsg(c, "====ERROR File not found OR no Read right !");
		return (0);
	}
	fstat(fd, &buf);
	close(fd);
	if ((buf.st_mode & S_IFMT) != S_IFREG)
	{
		writemsg(c, "====ERROR Special File");
		return (0);
	}
	msg = ft_mprintf("put %s:%lld\n", filename, buf.st_size);
	ft_strcat(c->bw, msg);
	free(msg);
	return (1);
}

int			prompt_read_put(t_client *c, char *cmd)
{
	char	**tab;
	char	*str;

	str = ft_mprintf("[CMD]>%s", cmd);
	writemsg(c, str);
	free(str);
	tab = ft_strsplit(cmd, ' ');
	if (ft_tablen(tab) > 1)
	{
		check_put_file(c, tab[1]);
	}
	ft_tabfree(tab);
	return (1);
}
