/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 02:42:15 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/11/05 13:51:23 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int	prompt_read_lcd(t_client *c, char *cmd)
{
	char	**tab;
	char	*str;

	str = ft_mprintf("[local CMD]>%s", cmd);
	writemsg(c, str);
	free(str);
	tab = ft_strsplit(cmd, ' ');
	if (ft_tablen(tab) > 1)
	{
		if (chdir(tab[1]) == 0)
		{
			getcwd(c->pwd, PATH_MAX);
			writemsg(c, "====SUCCESS Change localdir");
		}
		else
		{
			writemsg(c, "====ERROR folder not found");
		}
		view(c);
	}
	else
		writemsg(c, "====ERROR syntax \"lcd folderName\"");
	ft_tabfree(tab);
	return (1);
}
