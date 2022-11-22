/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:28:32 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/26 15:13:00 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_path_cmd2(char *cmd)
{
	int	j;

	j = -1;
	if (ft_strchr(cmd, '/'))
	{
		while (cmd[++j])
		{
			if (cmd[j] == '.')
				return (1);
		}
		if (access(cmd, F_OK | R_OK | X_OK) == 0)
			return (0);
		return (1);
	}
	return (2);
}

int	path_builtins(t_shell *shell, t_cmd *cmd, int active)
{
	if (!ft_strncmp(cmd->full_cmd[0], "export", ft_strlen(cmd->full_cmd[0])))
	{
		if (active)
			export_var(shell, shell->envp);
		return (1);
	}
	if (!ft_strncmp(cmd->full_cmd[0], "unset", ft_strlen(cmd->full_cmd[0])))
	{
		if (active)
			unset_envp(shell, cmd->full_cmd[1]);
		return (3);
	}
	if (ft_strchr(cmd->full_cmd[0], '='))
	{
		if (active)
			fake_export(cmd->full_cmd[0], shell);
		return (5);
	}
	return (0);
}

int	is_it_builtin(t_shell *shell, t_cmd *cmd, int active)
{
	if (path_builtins(shell, cmd, active))
		return (1);
	if (path_builtins_bis(shell, cmd, active))
		return (1);
	if (!ft_strncmp(cmd->full_cmd[0], "env", ft_strlen(cmd->full_cmd[0])))
	{
		if (active)
			print_envp(shell->envp, cmd, shell);
		return (2);
	}
	if (!ft_strncmp(cmd->full_cmd[0], "pwd", ft_strlen(cmd->full_cmd[0])))
		return (print_pwd(active, shell), 3);
	if (!ft_strncmp(cmd->full_cmd[0], "echo", ft_strlen(cmd->full_cmd[0])))
		return (echo_cmd(cmd, active), 3);
	return (0);
}

void	run_cmd(t_shell *shell, char **envp, t_envp **env)
{	
	get_nbr_cmds(shell);
	while (shell->cmds)
	{
		if (shell->cmds->next == NULL)
			break ;
		shell->cmds = shell->cmds->next;
	}
	rewind_cmd(&shell->cmds, 1);
	if (ft_strlen(shell->env[0]) > 1)
	{
		if (!double_cmd(&shell->token, 0) && !shell->unclosed_q
			&& !is_it_builtin(shell, shell->cmds, 0))
			error_msg(shell, shell->cmds, envp, 1);
		signalisation(1);
		if (shell->n_cmds == 1 && is_it_builtin(shell, shell->cmds, 0))
			is_it_builtin(shell, shell->cmds, 1);
		else
			pipex(shell, envp, env);
	}
}
