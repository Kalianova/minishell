/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 14:15:14 by lflorrie          #+#    #+#             */
/*   Updated: 2021/06/29 14:15:19 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_cmd(const char *command)
{
	int	i;

	i = 0;
	if (command == NULL)
		return (i);
	while (command[i] != ' ' && command[i] != '\0')
	{
		++i;
	}
	return (i);
}

void	free_strings(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		++i;
	}
	free(strs);
}
