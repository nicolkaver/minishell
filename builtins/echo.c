/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:01:43 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/26 15:57:01 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo(t_cmd *cmd, int i)
{
	if (!cmd->full_cmd[1])
	{
		printf("\n");
		return ;
	}
	if (cmd->full_cmd[i])
	{
		while (cmd->full_cmd[i])
		{
			if (cmd->full_cmd[i + 1])
				printf("%s ", cmd->full_cmd[i]);
			else
				printf("%s", cmd->full_cmd[i]);
			i++;
		}
	}	
}

static void	echo_active(int opt, t_cmd *cmd)
{
	if (opt && cmd->full_cmd[1] && cmd->full_cmd[2])
		print_echo(cmd, 2);
	else if (!opt && cmd->full_cmd[1])
	{
		print_echo(cmd, 1);
		printf("\n");
	}
	else if (!cmd->full_cmd[1])
		printf("\n");
}

void	echo_cmd(t_cmd *cmd, int active)
{
	int	opt;
	int	i;

	i = 0;
	opt = 0;
	if (!ft_strncmp2(cmd->full_cmd[1], "-n", 2))
	{
		if (cmd->full_cmd[1][0] == '-')
			opt = 1;
		while (cmd->full_cmd[1][++i])
		{
			if (cmd->full_cmd[1][i] != 'n')
				opt = 0;
		}
	}
	if (active && cmd->full_cmd[0])
		echo_active(opt, cmd);
}
