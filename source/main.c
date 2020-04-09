#include "../include/ft_select.h"

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

void	to_loop_elements(t_select *sel)
{
	t_elem *end;

	end = sel->elem;
	while (end->next)
		end = end->next;
	end->next = sel->elem;
	sel->elem->prev = end;
}

void	infill_args(t_select *sel, int ac, char **av)
{
	t_elem	*temp;
	int		max;
	int		temp_len;

	temp = NULL;
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
	to_loop_elements(sel);
	sel->elem->cursor = 1;
	sel->elem_cursor = sel->elem;
	sel->max_len += 1;
	ft_printf("sel->max_len = [%d]\n", sel->max_len);
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
	print_elem(sel->elem);
}

int		hash_sum(char *buf)
{
	int key;
	
	key = 0;
	while(*buf)
		key += *(buf++);
	ft_printf("key = {%d}\n", key);
	return (key);
}

void	press_esc(t_select *sel)
{
	ft_printf(tgetstr("ve", NULL));
	tcsetattr(0, TCSANOW, &sel->old_term);
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
	while (++i <= sel->columns)
		sel->elem_cursor = sel->elem_cursor->prev;
	sel->elem_cursor->cursor = 1;
}

void	press_down(t_select *sel)
{
	int i;

	i = -1;
	sel->elem_cursor->cursor = 0;
	while (++i <= sel->columns)
		sel->elem_cursor = sel->elem_cursor->next;
	sel->elem_cursor->cursor = 1;

}

void	press_enter(t_select *sel)
{
	t_elem	*elem;
	int		i;

	i = -1;
	elem = sel->elem;
	ft_printf(tgetstr("cl", NULL));
	while (21)
	{
		if (elem->choosed)
			ft_printf("%s ", elem->title);
		elem = elem->next;
		if (elem == sel->elem)
		{
			ft_printf(tgetstr("le", NULL));
			ft_putchar('\n');
			press_esc(sel);
		}
	}
}

void	press_delete(t_select *sel)
{
	t_elem *elem;

	elem = sel->elem_cursor;
	if (sel->elem == sel->elem->next)
		press_esc(sel);
	if (elem == sel->elem)
		sel->elem = elem->next;
	sel->elem_cursor = sel->elem_cursor->next;
	sel->elem_cursor->prev = elem->prev;
	elem->prev->next = sel->elem_cursor;
	sel->elem_cursor->cursor = 1;
	free(elem);
}

void	working_key(t_select *sel, int key)
{
	if (key == K_ESC)
		press_esc(sel);
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

void	print_elements(t_select *sel)
{
	t_elem	*elem;
	int		i;

	i = -1;
	elem = sel->elem;
	while (21)
	{
		if (elem->cursor)
			ft_printf(tgetstr("us", NULL));
		if (elem->choosed)
			ft_printf(tgetstr("so", NULL));
		ft_printf("%-*s", sel->max_len, elem->title);
		if (++i == sel->columns)
		{
			ft_putchar('\n');
			i = -1;
		}
		ft_printf(tgetstr("ue", NULL));
		ft_printf(tgetstr("se", NULL));
		elem = elem->next;
		if (elem == sel->elem)
			return ;
	}
}

void	calculate_colum(t_select *sel)
{
	if (!(tgetent(NULL, sel->name_term)))
		sys_err("Error terminal.\n");
	sel->w_term = tgetnum("co");
	sel->h_term = tgetnum("li");
	sel->columns = sel->w_term / sel->max_len;
	sel->columns = 1;
	while (sel->columns * sel->max_len < sel->w_term)
		sel->columns++;
	if (sel->count_elem * sel->max_len < sel->w_term)
		sel->columns = sel->count_elem;
	else
		sel->columns -= 2;
	ft_printf("sel->count_elem = [%d]\n", sel->count_elem);
	ft_printf("w_term = [%d] h_term = [%d]\n", sel->w_term, sel->h_term);
}

void	work(t_select *sel)
{
	int		key;
	char	buf[4];

	ft_printf(tgetstr("cl", NULL));
	key = hash_sum(buf);
	calculate_colum(sel);
	working_key(sel, key);
	print_elements(sel);
	ft_memset(buf, 0, 4);
	read(0, buf, 3);
}

void	seve_temp(t_select *sel)
{
	tcgetattr(0, &sel->old_term);
	ft_printf(tgetstr("vi", NULL));
	sel->new_term = sel->old_term;
	sel->new_term.c_lflag &= (~ICANON);
	sel->new_term.c_lflag &= (~ECHO);
	sel->new_term.c_cc[VTIME] = 0;
	sel->new_term.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &sel->new_term);
}

int		main(int ac, char **av)
{
	t_select sel;

	check_arguments(&sel, ac, av);
	seve_temp(&sel);
	while (1)
		work(&sel);
	return (0);
}
