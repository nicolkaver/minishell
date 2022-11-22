/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:00:56 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/22 15:59:12 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	gnd_bis(t_shell *shell, char *tmp, char *dir)
{
	char	*tmp2;

	tmp2 = ft_strjoin(tmp, dir);
	if (!tmp2)
		return (free(tmp), 2);
	shell->next_dir = tmp2;
	if (!shell->next_dir)
		return (free(tmp2), free(tmp), 2);
	return (free(tmp2), 0);
}

int	get_next_dir(t_shell *shell, char *dir)
{
	char	*tmp;

	if (access(dir, F_OK | R_OK) == 0)
	{	
		shell->next_dir = dir;
		return (0);
	}
	if (*dir != '/')
	{
		tmp = ft_strjoin(shell->cwd, "/");
		if (!tmp)
			return (1);
	}
	else
		tmp = ft_strdup(dir);
	if (gnd_bis(shell, tmp, dir))
		return (2);
	return (free(tmp), 0);
}
