/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:44:22 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/21 14:22:16 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_return_val; // valeur de retour de la derniere commande executee

int	main(int ac, char **av, char **envp)
{
	(void)av; // confirme que av n'est pas utilisee dans la fonction
	g_return_val = 0; // init r_val a 0
	if (ac != 1) // on check le nombre d'argument 
		return (err_msg("Tuto (derien) : ./minishell", NULL, NULL, 1)); // message d'erreur si c'est pas carre 
	handle_signal(); // pour les signaux
	get_prompt(envp); //!HERE1
	return (0);
}
