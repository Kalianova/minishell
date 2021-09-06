#include "minishell.h"


void show_map(t_map *map)
{
	if (!map)
		return ;
	while (map)
	{
		printf("%s %s\n", map->key, map->value);
		map = map->prev;
	}
}

void ft_mapadd(t_map **map, char *key, char *value)
{
	t_map *new_elem;
	
	new_elem = (t_map *)malloc(sizeof(t_map));
	new_elem->key = key;
	new_elem->value = value;
	new_elem->next = NULL;
	new_elem->prev = *map;
	if (*map != NULL)
	{
		(*map)->next = new_elem;
	}
	*map = new_elem;
}

void ft_mapdel(t_map **map, char *key)
{
	t_map *tmp;

	tmp = ft_mapfind(map, key);
	free(tmp->key);
	free(tmp->value);
	if (tmp)
	{
		if (tmp->next != NULL && tmp->prev != NULL)
		{
			tmp->next->prev = tmp->prev;
			tmp->prev->next = tmp->next;
			free((tmp));
		}
		else if (tmp->prev != NULL)
		{
			*map = tmp->prev;
			free(tmp);
		}
		else if (tmp->next != NULL)
		{
			tmp->next->prev = NULL;
			free(tmp);
		}
		else
		{
			*map = NULL;
			free((tmp));
		}
	}
}

int ft_mapreplace(t_map **map, char *key, char *value)
{
	t_map *tmp;

	tmp = ft_mapfind(map, key);
	if (tmp)
	{
		free(tmp->value);
		tmp->value = value;
		return (1);
	}
	return (0);
}

t_map *ft_mapfind(t_map **map, char *key)
{
	t_map *tmp;

	tmp = *map;
	while (tmp->prev)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}

void ft_mapdelall(t_map **map)
{
	t_map *tmp;

	if(!(*map))
		return ;
	while((*map)->prev)
	{
		free((*map)->key);
		free((*map)->value);
		tmp = (*map)->prev;
		free((*map));
		*map = tmp;
	}
	free((*map)->key);
	free((*map)->value);
	free((*map));
}