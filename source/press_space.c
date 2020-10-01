
#include "../include/ft_select.h"


void	press_space(t_select *sel)
{
	sel->elem_cursor->choosed = !sel->elem_cursor->choosed;
	press_right(sel);
}

void	press_up(t_select *sel)
{
	int i;

	i = -1;
	sel->elem_cursor->cursor = 0;
	while (++i < sel->columns)
		sel->elem_cursor = sel->elem_cursor->prev;
	sel->elem_cursor->cursor = 1;
}

void	press_down(t_select *sel)
{
	int i;

	i = -1;
	sel->elem_cursor->cursor = 0;
	while (++i < sel->columns)
		sel->elem_cursor = sel->elem_cursor->next;
	sel->elem_cursor->cursor = 1;
}

void	press_enter(t_select *sel)
{
	t_elem	*elem;
	int		i;

	i = -1;
	elem = sel->elem;
	ft_putstr_fd(tgetstr("cl", NULL), STDERR_FILENO);
	while (21)
	{
		if (elem->choosed)
			ft_printf("%s ", elem->title);
		elem = elem->next;
		if (elem == sel->elem)
		{
			ft_putstr_fd(tgetstr("le", NULL), STDERR_FILENO);
			ft_putstr_fd(tgetstr("ve", NULL), STDERR_FILENO);
			tcsetattr(STDERR_FILENO, TCSANOW, &sel->old_term);
			exit(0);
		}
	}
}

/*
** Обновляет максимально длинное слово.
*/

void	calculate_max_len(t_select *sel)
{
	t_elem	*elem;
	int		temp;

	elem = sel->elem;
	sel->max_len = ft_strlen(elem->title);
	while (21)
	{
		elem = elem->next;
		temp = ft_strlen(elem->title);
		if (temp > sel->max_len)
			sel->max_len = temp;
		if (elem == sel->elem)
			break ;
	}
	sel->max_len += 2;
}
