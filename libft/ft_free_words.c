/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <lflorries@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 23:23:05 by lflorrie          #+#    #+#             */
/*   Updated: 2021/03/29 23:27:33 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_words(char **ar)
{
	int	i;

	i = 0;
	if (ar == NULL)
		return ;
	while (ar[i] != NULL)
	{
		free(ar[i]);
		++i;
	}
	free(ar);
}
