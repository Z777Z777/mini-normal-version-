/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:16:13 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/09 14:04:38 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Malloc et initialise a NULL la struct t_data
// Return pointeur sur data si la creation a reussie, sinon NULL
t_data	*create_data(char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data)); // alloue la memoire pour la structure data
	if (!data) // protege malloc
		return (NULL);
	data->env_path = NULL; // initialise tous les pointeurs de structures a NULL
	data->cmd = NULL;
	data->list = NULL;
	data->envp = NULL;
	data->proc = NULL;
	if (!create_env(data, envp)) // cree l'environnement dans la structure t_envp a partir de l'env bash ou de l'env mnimal cree
		return (free_data(data), NULL);
	data->proc = create_proc(); // cree et init a 0 la structure t_proc, return un ptr sur NULL si malloc failed
	if (!data->proc) // si l'initialisation echoue, 
		return (free_data(data), NULL); // on free et rtrn NULL
	return (data); // on retourne la structure
}