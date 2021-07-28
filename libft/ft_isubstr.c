#include "libft.h"

char	*get_res(const char *s, size_t len)
{
	char	*res;

	if (s == NULL)
		return (NULL);
	res = (char *)malloc((len + 1) * sizeof(char));
	return (res);
}

char	*ft_isubstr(const char *s, unsigned int start, size_t len, char ch)
{
	char	*res;
	size_t	i;

	res = get_res(s, len);
	if (!res)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		res[0] = '\0';
		return (res);
	}
	i = 0;
	while (s[i + start] != '\0' && i < len)
	{
		if (s[i + start] != ch)
		{
			res[i] = s[i + start];
			++i;
		}
		else
			++start;
	}
	res[len] = '\0';
	return (res);
}
