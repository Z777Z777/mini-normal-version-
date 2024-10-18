/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 07:33:16 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/17 17:49:56 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//reagit en fonction du caractere rencontre
int	count_chars_cmd(char *str, int *i, int *count, int n)
{
	int	chars;

	chars = 0;
	if ((*count) == n)
		chars++;
	if (is_end_of_string(str[(*i) + 1]))
		(*count)++;
	(*i)++;
	return (chars);
}

int	count_chars_redir(char *str, int *i, int *count, int n)
{
	int	chars;

	chars = 0;
	if ((*count) == n)
		chars++;
	if (str[(*i) + 1] == str[(*i)])
	{
		if ((*count) == n)
			chars++;
		(*i)++;
	}
	(*count)++;
	(*i)++;
	return (chars);
}

int	count_chars_pipe(int *i, int *count, int n)
{
	int	chars;

	chars = 0;
	if ((*count) == n)
		chars++;
	(*count)++;
	(*i)++;
	return (chars);
}
