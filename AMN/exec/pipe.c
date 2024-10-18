/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:38:01 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/20 14:04:44 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Cree tous les pipes neccessaire a l'execution de la ligne de commande
// Return 1 si la creation a fonctionne, sinon 0
int	create_pipes(t_proc *proc)
{
	int	i;

	i = 0;
	while (i < proc->n_pipes)
	{
		if (pipe(proc->pipe_fd[i]) < 0)
			return (err_msg("Pipe failed", NULL, NULL, 0));
		i++;
	}
	return (1);
}

// Cree le nombre de pipe necessaire
// Return 1 si tout s'est bien passe, sinon 0 (malloc rate)
int	create_pipes_array(t_data *data)
{
	int		i;
	t_proc	*proc; // cree la structure broc

	proc = data->proc; // range la structure proc dans data
	i = 0;
	proc->n_pipes = pipe_count(data->cmd); // nombre de pipe
	if (proc->n_pipes <= 0) // si erreur ou quoi 
	{
		proc->n_pipes = 0; // on met pipe a 0 et 
		return (1); // on return une erreur 
	}
	proc->pipe_fd = ft_calloc(proc->n_pipes + 1, sizeof(int *)); // alloue la memoire pour stocker le descripteur de fichier
	if (!proc->pipe_fd) // verif le malloc
		return (0);
	while (i < proc->n_pipes) // pour chque pipe
	{
		proc->pipe_fd[i] = ft_calloc(2, sizeof(int)); // on alloue un nouveau file descriptor
		if (!proc->pipe_fd[i]) // protege le calloc
			return (free_int_tab(proc->pipe_fd, i), 0);
		i++;
	}
	proc->pipe_fd[i] = 0;
	if (!create_pipes(proc)) // cree les pipes avec pipe()
		return (free_int_tab(proc->pipe_fd, proc->n_pipes), 0); // free le tableau si c'est pas carre
	return (1);
}

// Close tous les pipes
void	close_pipes(t_proc *proc)
{
	int	i;

	i = 0;
	while (i < proc->n_pipes)
	{
		close(proc->pipe_fd[i][0]);
		close(proc->pipe_fd[i][1]);
		i++;
	}
}
