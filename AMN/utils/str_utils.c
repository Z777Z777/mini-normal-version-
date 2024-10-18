/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:32:11 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/10 16:14:04 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

// Cherche to_find dans str
// Return l'addresse de la fin de chaine de caractere to_find 
// ou NULL si to_find n'a pas ete trouve dans str
char	*ft_strcmp(char *str, char *to_find)
{
	int	i;

	i = 0;
	while (str[i] && to_find[i] && str[i] == to_find[i])
		i++;
	if (!to_find[i])
		return (&str[i]);
	return (NULL);
}

// Duplique n caratcere de str
// Si n = 0 duplique l'entierte de str
// Return la chaine de caractere dupliquee
char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*dup;

	i = -1;
	if (!str) // si la str est vide on return NULL;
		return (NULL);
	dup = ft_calloc(ft_strlen(str) + 1, 1); // on alloue une str de la taille de la str a dupliquer
	if (!dup) // malloc protect
		return (NULL);
	if (n == 0) // si n = 0, on duplique l'entierte de la str
	{
		while (str[++i])
			dup[i] = str[i];
	}
	else // sinon on duplique que n caractere de la str
	{
		while (++i < n && str[i])
			dup[i] = str[i];
	}
	return (dup); // on retourne la chaine dupliquee
}

void	ft_putstr(char *str)
{
	if (!str)
		return ;
	write(STDOUT_FILENO, str, ft_strlen(str));
}

// Cherche le type de redir
// Return le type ou 0 si str ne correspond a aucun connu
int	redir_type(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '|')
		return (PIPE);
	if (str[0] == '<' && str[1] && str[1] == '<')
		return (HERE);
	if (str[0] == '>' && str[1] && str[1] == '>')
		return (APPEND);
	if (str[0] == '<')
		return (IN);
	if (str[0] == '>')
		return (OUT);
	else
		return (WORD);
}
