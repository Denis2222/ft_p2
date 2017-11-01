/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 13:46:06 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/11/01 20:20:39 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftpd.h"

void	do_select(t_env *e)
{
	struct timeval tv;
	tv.tv_sec = 3;
	tv.tv_usec = 0;
	e->r = select(e->max + 1, &e->fd_read, &e->fd_write, NULL, NULL);
}

int main(int ac, char **argv)
{
	(void)ac;
	(void)argv;
	
	t_env e;

	env_init(&e);
	srv_listen(&e, ft_atoi(argv[1]));

	ft_printf("FT_PD ready on port [%d]:\n", e.port);

	while (1)
	{
		fd_init(&e);
		do_select(&e);
		fd_check(&e);
	}
	return (0);
}

void	printfd(t_fd *fd, char *format, long long int data)
{
	char *str;

	if (format)
		if (ft_strlen(format))
		{
		//	dprintf(fd->sock, format, data);
			str = ft_mprintf(format, data);
			fd_send(fd, str);
			free(str);
		}
}

void	printfw(t_fd *fd, char *format, void *data)
{
	char *str;
	
	if (format)
		if (ft_strlen(format))
		{
			//dprintf(fd->sock, format, data);
			str = ft_mprintf(format, data);
			fd_send(fd, str);
			free(str);
		}
}
