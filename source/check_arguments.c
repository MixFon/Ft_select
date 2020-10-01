
#include "../include/ft_select.h"


/*
** Проверяем колличество аргументов.
** Запоминаем имя теминала из переменных окружения.
** Проверяем доступность терминала.
*/

void	check_arguments(t_select *sel, int ac, char **av)
{
	int i;

	i = 0;
	if (ac < 2)
		sys_err("To many arguments.\n");
	ft_memset(sel, 0, sizeof(t_select));
	sel->name_term = getenv("TERM");
	if (!(tgetent(NULL, sel->name_term)))
		sys_err("Error terminal.\n");
	infill_args(sel, ac, av);
}

/*
** Возвращает сумму символов.
*/

int		hash_sum(char *buf)
{
	int key;

	key = 0;
	while (*buf)
		key += *(buf++);
	return (key);
}

void	press_esc(t_select *sel)
{
	ft_putstr_fd(tgetstr("ve", NULL), STDERR_FILENO);
	ft_putstr_fd(tgetstr("cl", NULL), STDERR_FILENO);
	tcsetattr(STDERR_FILENO, TCSANOW, &sel->old_term);
	exit(0);
}

void	press_right(t_select *sel)
{
	sel->elem_cursor->cursor = 0;
	sel->elem_cursor = sel->elem_cursor->next;
	sel->elem_cursor->cursor = 1;
}

void	press_left(t_select *sel)
{
	sel->elem_cursor->cursor = 0;
	sel->elem_cursor = sel->elem_cursor->prev;
	sel->elem_cursor->cursor = 1;
}
