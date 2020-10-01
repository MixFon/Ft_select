/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 09:47:07 by widraugr          #+#    #+#             */
/*   Updated: 2020/10/01 09:47:35 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_select.h"

void	press_delete(t_select *sel)
{
	t_elem	*elem;
	int		size;

	elem = sel->elem_cursor;
	if (sel->elem == sel->elem->next)
		press_esc(sel);
	if (elem == sel->elem)
		sel->elem = elem->next;
	sel->elem_cursor = sel->elem_cursor->next;
	sel->elem_cursor->prev = elem->prev;
	elem->prev->next = sel->elem_cursor;
	sel->elem_cursor->cursor = 1;
	sel->count_elem--;
	size = ft_strlen(elem->title);
	if (size == sel->max_len - 2)
		calculate_max_len(sel);
	free(elem->title);
	free(elem);
}

/*
** Обработка нажатия клавиш.
*/

void	working_key(t_select *sel, int key)
{
	if (key == K_ESC)
		press_esc(sel);
	else if (sel->bl_err_size)
		return ;
	else if (key == K_RIGHT)
		press_right(sel);
	else if (key == K_LEFT)
		press_left(sel);
	else if (key == K_SPACE)
		press_space(sel);
	else if (key == K_UP)
		press_up(sel);
	else if (key == K_DOWN)
		press_down(sel);
	else if (key == K_BSPACE || key == K_DELETE)
		press_delete(sel);
	else if (key == K_ENTER)
		press_enter(sel);
}

/*
** Определяем колличество необходимых пробелов.
** Подчеркиваем или выделяем.
** И дополняем пробелами.
*/

void	print_title(t_elem *elem, int max_len)
{
	int		spaces;
	char	*line;

	spaces = max_len - ft_strlen(elem->title);
	line = ft_strnew(spaces);
	ft_memset(line, ' ', spaces);
	if (elem->cursor)
		ft_putstr_fd(tgetstr("us", NULL), STDERR_FILENO);
	if (elem->choosed)
		ft_putstr_fd(tgetstr("so", NULL), STDERR_FILENO);
	ft_putstr_fd(elem->title, STDERR_FILENO);
	ft_putstr_fd(tgetstr("ue", NULL), STDERR_FILENO);
	ft_putstr_fd(tgetstr("se", NULL), STDERR_FILENO);
	write(2, line, spaces);
	free(line);
}

/*
** Печатаем все элементы.
*/

void	print_elements(t_select *sel)
{
	t_elem	*elem;
	int		i;

	i = 0;
	elem = sel->elem;
	while (21)
	{
		print_title(elem, sel->max_len);
		if (++i == sel->columns)
		{
			ft_putchar_fd('\n', STDERR_FILENO);
			i = 0;
		}
		elem = elem->next;
		if (elem == sel->elem)
			return ;
	}
}

/*
** Вычисление размеров колонны.
*/

int		calculate_colum(t_select *sel)
{
	if (!(tgetent(NULL, sel->name_term)))
		sys_err("Error terminal.\n");
	sel->w_term = tgetnum("co");
	sel->h_term = tgetnum("li");
	if (sel->max_len >= sel->w_term)
		return (1);
	sel->columns = 1;
	while (sel->columns * sel->max_len < sel->w_term)
		sel->columns++;
	if (sel->count_elem * sel->max_len < sel->w_term)
		sel->columns = sel->count_elem;
	else
		sel->columns -= 1;
	if (sel->h_term < sel->count_elem / sel->columns)
		return (1);
	return (0);
}
