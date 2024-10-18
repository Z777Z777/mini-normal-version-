/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:06:50 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/20 17:25:59 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Cree et et initialise a 0 la structure t_proc
// Return un pointeur sur t_roc ou NULLL si malloc failed
t_proc	*create_proc(void)
{
	t_proc	*proc;

	proc = ft_calloc(1, sizeof(t_proc)); // allocation de la structure
	if (!proc) // malloc protection
		return (NULL);
	proc->n_pipes = 0; // initialisation des champs de la structure a 0
	proc->n_heredoc = 0;
	proc->fd_heredoc = NULL;
	proc->pipe_fd = NULL;
	proc->fd_in = STDIN_FILENO;
	proc->fd_out = STDOUT_FILENO;
	proc->pid = NULL;
	return (proc); // retourne un pointeur vers t_process
}
