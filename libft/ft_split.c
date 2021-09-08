/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:39:43 by lflorrie          #+#    #+#             */
/*   Updated: 2020/11/13 19:23:42 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	long long	count;
	char		*point;

	count = 0;
	point = (char *)s;
	while (*point == c && *point)
		++point;
	if (c == '\0' && *point)
		return (1);
	if (!(*point))
		return (0);
	while (*point)
	{
		while (*point != c && *point)
			++point;
		count++;
		while (*point == c && *point)
			++point;
	}
	return (count);
}

static char	*make_word(char const *s, int *begin, char c)
{
	int	j;

	j = 0;
	while (s[*begin] == c && s[*begin])
		(*begin)++;
	while (s[(*begin) + j] != c && s[(*begin) + j])
		j++;
	(*begin) += j;
	return (ft_substr(s, (*begin) - j, j));
}

char	**ft_split(char const *s, char c)
{
	int		words;
	int		i;
	int		arr;
	char	**res;

	i = 0;
	arr = -1;
	if (!s)
		return (NULL);
	words = count_words(s, c);
	res = (char **)malloc((words + 1) * sizeof(char *));
	if (!(res))
		return (NULL);
	while (++arr < words)
	{
		res[arr] = make_word(s, &i, c);
		if (!res[arr])
		{
			while (--arr >= 0)
				free(res[arr]);
			free(res);
		}
	}
	res[words] = NULL;
	return (res);
}
