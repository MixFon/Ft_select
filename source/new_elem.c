
#include "../include/ft_select.h"

#include "../include/ft_select.h"

/*
** Создает новый элемент листа.
*/

t_elem	*new_elem(char *title)
{
	t_elem *new;

	if (!(new = (t_elem *)malloc(sizeof(t_elem))))
		sys_err("Error malloc.\n");
	ft_memset(new, 0, sizeof(t_elem));
	new->title = ft_strdup(title);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/*
** Закольцовывает двусвязный список.
*/

void	to_loop_elements(t_select *sel)
{
	t_elem *end;

	end = sel->elem;
	while (end->next)
		end = end->next;
	end->next = sel->elem;
	sel->elem->prev = end;
}

/*
** Удаляет элементы, содержащие пустые строки.
*/

void	removing_unnecessary_elements(t_select *sel)
{
	t_elem *elem;

	if (sel->elem->title[0] == '\0')
	{
		elem = sel->elem;
		if (sel->elem->next)
			sel->elem = sel->elem->next;
		else
			exit(0);
		free(elem->title);
		free(elem);
	}
}

/*
** Создает двусвязный кольцевой список из переданных аргументов.
*/

void	infill_args(t_select *sel, int ac, char **av)
{
	t_elem	*temp;
	int		temp_len;

	sel->count_elem = 1;
	if (!sel->elem)
		sel->elem = new_elem(av[--ac]);
	sel->max_len = ft_strlen(av[ac]);
	while (--ac)
	{
		if (!(temp_len = ft_strlen(av[ac])))
			continue;
		if (temp_len > sel->max_len)
			sel->max_len = temp_len;
		temp = new_elem(av[ac]);
		temp->next = sel->elem;
		sel->elem->prev = temp;
		sel->elem = temp;
		sel->count_elem++;
	}
	removing_unnecessary_elements(sel);
	to_loop_elements(sel);
	sel->elem->cursor = 1;
	sel->elem_cursor = sel->elem;
	sel->max_len += 2;
}

void	print_elem(t_elem *elem)
{
	t_elem *start;

	start = elem;
	while (21)
	{
		ft_printf("elem = [%s]\n", elem->title);
		elem = elem->next;
		if (elem == start)
			return ;
	}
}
