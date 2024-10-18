/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:07:42 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/20 21:36:21 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Return le nombre de variable de l'environnement bash ou 0 si il n'y en a pas
int	env_length(char **envp)
{
	int	i; // indexe

	i = 0; 
	if (!*envp) // si il est vide, on return 0
		return (0);
	while (envp[i]) // tant qu'il y a une ligne, i++
		i++;
	return (i); // on return le nombre de ligne dabs l'env
}

// Cree un environnement minial si l'environnement de bash n'existe pas
// Return 1 si la creation a reussi, sinon 0
int	create_my_env(t_data *data)
{
	char	**tab;

	tab = ft_calloc(4, sizeof(char *)); // alloue les 42 pointeurs de la chaine
	tab[0] = ft_strndup("OLDPWD", 0); // on duplique les chainnes entree dans les case de tab
	tab[1] = ft_strndup("PWD", 0);
	tab[2] = ft_strndup("SHLVL=1", 0);
	tab[3] = 0; // la derniere case est a 0 (pour fermer le tableau)
	if (ft_export(data, tab, 1)) //!HERE3
		return (0);
	replace_pwd_my_env(data->envp); // attribue un pwd a l'env
	free_tab(tab); // libre le tableau
	return (1);
}

// Cree l'environnement dans la structure t_envp a partir de l'environnement
// bash ou de create_my_env
// Return 1 si la creation a reussie, sinon 0
int	create_env(t_d
 ata *data, char **envp)
{
	int		env_lgt;

	env_lgt = env_length(envp); // mesure la longeure de l'environnement
	if (env_lgt == 0) // si env_lgt est a 0, cela signifie que env est vide, dans ce cas,
	{
		if (!create_my_env(data))  // cree un environnement minimal si l'env bash n'existe pas, (\n)
		return (1); //           (\n) return 1 si la creation reussi, sinon 0
	}
	ft_export(data, envp, 1); //!HERE4
	data->env_path = find_path_in_env(envp); // cherche la variable PATH qui contiens tous les chemins possible de commandes dans l'env
	return (1);
}
