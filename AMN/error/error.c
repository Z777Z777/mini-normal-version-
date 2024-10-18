/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:19:29 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/20 20:49:14 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
char *start: Un pointeur vers une chaîne de caractères qui sera affichée en premier dans le message d'erreur.
char *str: Un pointeur vers une chaîne de caractères qui sera affichée après start dans le message d'erreur.
char *end: Un pointeur vers une chaîne de caractères qui sera affichée après str.
int ret: La valeur qui sera retournée par la fonction après l'affichage du message.
*/

// Affiche un message d'erreur sur STDERR
// Return la valeur de retour ret
int	err_msg(char *start, char *str, char *end, int ret)
{
	if (start)
		write(STDERR_FILENO, start, ft_strlen(start));
	if (str)
		write(STDERR_FILENO, str, ft_strlen(str));
	if (end)
		write(STDERR_FILENO, end, ft_strlen(end));
	write(STDERR_FILENO, "\n", 1);
	return (ret);
}

// Affiche le message d'erreur correspondant a l'erreur
// Return la valeur de retour selon l'erreur 
int	error_cmd(char **cmd)
{	
	int	fd;
	DIR	*dir;
	int	ret;

	ret = 1;
	if (!cmd || !cmd[0])
		return (err_msg("minishell: ", NULL, ": command not found", 127));
	if (ft_strchr(cmd[0], '/'))
		return (err_msg("minishell: ", cmd[0], ": command not found", 127));
	fd = open(cmd[0], O_WRONLY);
	dir = opendir(cmd[0]);
	if (fd == -1 && dir == NULL)
		ret = err_msg("minishell: ", cmd[0], ": No such file or directory",
				127);
	else if (fd == -1 && dir != NULL)
		ret = err_msg("minishell: ", cmd[0], ": is a directory", 126);
	else if (fd != -1 && dir == NULL)
		ret = err_msg("minishell: ", cmd[0], ": Permission denied", 127);
	if (fd > 0)
		close(fd);
	if (dir)
		closedir(dir);
	return (ret);
}
