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
** Создает двусвязный список.
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
		if(!(temp_len = ft_strlen(av[ac])))
			continue;
		if (temp_len > sel->max_len)
			sel->max_len = temp_len;
		temp = new_elem(av[ac]);
		temp->next = sel->elem;
		sel->elem->prev = temp;
		sel->elem = temp;
		sel->count_elem++;
		//ft_printf("arg = [%s]\n", av[ac]);
	}
	removing_unnecessary_elements(sel);
	to_loop_elements(sel);
	sel->elem->cursor = 1;
	sel->elem_cursor = sel->elem;
	sel->max_len += 2;
	//ft_printf("sel->max_len = [%d]\n", sel->max_len);
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
	//print_elem(sel->elem);
}

/*
** Возвращает сумму символов.
*/

int		hash_sum(char *buf)
{
	int key;
	
	key = 0;
	while(*buf)
		key += *(buf++);
	//ft_printf("key = {%d}\n", key);
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
	while(21)
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
** в конанический режим, отключает эхо ввод, устанавливает
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

void	working_signals(int sig)
{
	if (sig == SIGWINCH)
		print_elem_or_error_size(g_sel);
	else if (sig == SIGTSTP)
		background_mode();
	else if (sig == SIGCONT)
		standart_mode();
	else if (sig == SIGINT || sig == SIGABRT || sig == SIGSTOP
			|| sig == SIGKILL || sig == SIGQUIT)
		press_esc(g_sel);
}

/*
** SIGWINCH - сигнал изменения окна.
** SIGABRT	- посылается программе в результате вызова функции abort(3)
** SIGINT	- Сигнал прерывания (Ctrl-C) с терминала. 
** SIGSTOP	- Остановка выполнения процесса
** SIGCONT	- Продолжить выполнение ранее остановленного процесса
** SIGTSTP	- Сигнал остановки с терминала (Ctrl-Z).
** SIGKILL	- Безусловное завершение
** SIGQUIT	- Сигнал «Quit» с терминала (Ctrl-\)
*/

void	set_signals(void)
{
	signal(SIGWINCH, working_signals);
	signal(SIGABRT, working_signals);
	signal(SIGINT, working_signals);
	signal(SIGSTOP, working_signals);
	signal(SIGCONT, working_signals);
	signal(SIGTSTP, working_signals);
	signal(SIGKILL, working_signals);
	signal(SIGQUIT, working_signals);
}

int		main(int ac, char **av)
{
	t_select sel;

	g_sel = &sel;
	check_arguments(&sel, ac, av);
	seve_temp(&sel);
	set_signals();
	work(&sel);
	return (0);
}
