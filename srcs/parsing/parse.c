/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:42:59 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/22 12:20:57 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_cmd_found(t_token *token, t_shell *shell)
{
	t_token	*tmp;
	int		cases;

	tmp = token;
	if (tmp->prev)
		tmp = tmp->prev;
	while (tmp->type != PIPE)
	{
		if (tmp->prev)
			tmp = tmp->prev;
		else
			break ;
	}
	if (tmp->type == PIPE)
		tmp = tmp->next;
	cases = which_case(&tmp, shell);
	if (cases == 1)
		shell->ret = 1;
	if (cases == 130)
	{
		shell->ret = 130;
		return (130);
	}
	return (0);
}

int	get_cmds(t_token **t, t_cmd **cmd, t_shell *shell)
{
	t_token	*tmp;

	tmp = *t;
	if (get_cmds_bis(tmp, shell, cmd) == 130)
		return (130);
	if (*cmd)
		return (1);
	return (0);
}

int	parse(t_token **token, t_shell *shell)
{
	char	*check;

	check = check_tokens(token);
	if (check)
	{		
		ft_printf("minishell: syntax error near unexpected token `%s'\n", check);
		shell->ret = 2;
		return (-1);
	}
	shell->ret = 0;
	if (get_cmds(token, &shell->cmds, shell))
		return (1);
	return (0);
}
