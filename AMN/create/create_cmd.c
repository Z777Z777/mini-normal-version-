/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:53:43 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/09 18:01:18 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Calloc les char** et int* de data->cmd, return t_cmd
t_cmd	*set_up_cmd(t_data *data, int *i)
{
	t_cmd	*cmd;

	cmd = ft_cmdnew(*i);
	cmd->opt = ft_calloc(words_to_pipe(data, (*i)) + 1, sizeof(char *));
	if (!cmd->opt)
		return (NULL);
	cmd->opt[words_to_pipe(data, (*i))] = 0;
	cmd->token = ft_calloc(count_tokens(data, (*i)) + 1, sizeof(char *));
	if (!cmd->token)
		return (NULL);
	cmd->token[count_tokens(data, (*i))] = 0;
	cmd->type = ft_calloc(count_redir(data, (*i)) + 1, sizeof(int));
	if (count_tokens(data, (*i)) != count_redir(data, (*i)))
		return (free_cmd(cmd), NULL);
	return (cmd);
}

// Initialise la creation de data->cmd
int	get_cmd_struct(t_data *data)
{
	t_list	*tmp;
	t_cmd	*cmd;
	int		i;

	tmp = data->list;
	cmd = NULL;
	i = 0;
	if (!start_cmd_struct(data, tmp, cmd))
	{
		g_return_val = 2;
		return (err_msg("syntax error near unexpected token `newline'",
				NULL, NULL, 0), free_data_proc(data), 2);
	}
	data->proc->pid = ft_calloc(pipe_count(data->cmd) + 1, sizeof(pid_t));
	while (i < pipe_count(data->cmd) + 1)
	{
		data->proc->pid[i] = -1;
		i++;
	}
	return (0);
}

// Return 1 si la creation de data->cmd abouti
int	start_cmd_struct(t_data *data, t_list *tmp, t_cmd *cmd)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (tmp)
	{
		j = 0;
		k = 0;
		cmd = set_up_cmd(data, &i);
		if (!cmd)
			return (0);
		while (tmp && tmp->type != 6)
		{
			tmp = fill_cmd_struct(data, cmd, tmp, &j);
			tmp = fill_cmd_tokens(cmd, tmp, &k);
		}
		add_back(data, cmd);
		i++;
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}
