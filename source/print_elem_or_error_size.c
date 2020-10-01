
#include "../include/ft_select.h"


/*
** Выбирает печатать элементы или сообшение об ошибке
** или элементы.
*/

void	print_elem_or_error_size(t_select *sel)
{
	ft_putstr_fd(tgetstr("cl", NULL), STDERR_FILENO);
	if (calculate_colum(sel))
	{
		ft_putstr_fd(TERM_SMAL, STDERR_FILENO);
		ft_putstr_fd(INCREASE, STDERR_FILENO);
		sel->bl_err_size = 1;
	}
	else
	{
		sel->bl_err_size = 0;
		print_elements(sel);
	}
}

/*
** Основная программа в которой происходит чтение одного символа
** обработка команд и петать элемнтов.
*/

void	work(t_select *sel)
{
	int		key;
	char	buf[4];

	while (21)
	{
		key = hash_sum(buf);
		working_key(sel, key);
		print_elem_or_error_size(sel);
		ft_memset(buf, 0, 4);
		read(0, buf, 3);
	}
}

/*
** Сохроняет параметры терминала. Отключает видимость курсора.
** Создает переменную параметров терминала, переводит терминал
** в конанический режим (ввод не виден), отключает эхо ввод, устанавливает
** колличество вводимых символов в единицу.
*/

void	seve_temp(t_select *sel)
{
	if (tcgetattr(STDERR_FILENO, &sel->old_term) < 0)
		sys_err("Error tcgetattr");
	ft_putstr_fd(tgetstr("vi", NULL), STDERR_FILENO);
	sel->new_term = sel->old_term;
	sel->new_term.c_lflag &= (~ICANON);
	sel->new_term.c_lflag &= (~ECHO);
	sel->new_term.c_cc[VTIME] = 0;
	sel->new_term.c_cc[VMIN] = 1;
	if (tcsetattr(STDERR_FILENO, TCSANOW, &sel->new_term) < 0)
		sys_err("Error tcsetattr");
}

/*
** Переводим программу в фоновый режим с помощью SIG_DEF
** SIG_DEF - стандартная реакция на сигнал, которая
** предусмотрена системой.
*/

void	background_mode(void)
{
	ft_putstr_fd(tgetstr("ve", NULL), STDERR_FILENO);
	tcsetattr(STDERR_FILENO, TCSANOW, &g_sel->old_term);
	ft_putstr_fd(tgetstr("cl", NULL), STDERR_FILENO);
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
}

/*
** Функция вызыватеся при получении сигнала перехода из
** фонового режима.
*/

void	standart_mode(void)
{
	ft_printf("Print elements\n");
	signal(SIGTSTP, working_signals);
	if (tcsetattr(STDERR_FILENO, TCSANOW, &g_sel->new_term) < 0)
		sys_err("Error tcsetattr");
	ft_putstr_fd(tgetstr("cl", NULL), STDERR_FILENO);
	ft_putstr_fd(tgetstr("vi", NULL), STDERR_FILENO);
	print_elem_or_error_size(g_sel);
}
