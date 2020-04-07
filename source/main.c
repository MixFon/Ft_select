#include "../include/ft_select.h"

t_elem	*new_elem(char *title)
{
	t_elem *new;

	if (!(new = (t_elem *)malloc(sizeof(t_elem))))
		sys_err("Error malloc.\n");
	ft_memset(new, 0, sizeof(t_elem));
	new->title = ft_strdup(title);
	new->next = NULL;
	return (new);
}

void	infill_args(t_select *sel, int ac, char **av)
{
	t_elem *temp;

	temp = NULL;
	if (!sel->elem)
		sel->elem = new_elem(av[--ac]);
	while (--ac)
	{
		temp = new_elem(av[ac]);
		temp->next = sel->elem;
		sel->elem = temp;
		//ft_printf("arg = [%s]\n", av[ac]);
	}
	sel->elem->cursor = 1;
}

void	print_elem(t_elem *elem)
{
	while (elem)
	{
		ft_printf("elem = [%s]\n", elem->title);
		elem = elem->next;
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
	sel->w_term = tgetnum("co");
	sel->h_term = tgetnum("li");
	ft_printf("w_term = [%d] h_term = [%d]\n", sel->w_term, sel->h_term);
	infill_args(sel, ac, av);
	print_elem(sel->elem);
}

void	work(t_select *sel)
{
	t_elem *elem;

	elem = sel->elem;
	ft_printf(tgetstr("cl", NULL));
	while (elem)
	{
		if (elem->cursor)
			ft_printf(tgetstr("us", NULL));
		if (elem->choosed)
			ft_printf(tgetstr("so", NULL));
		ft_printf("%s\n", elem->title);
		ft_printf(tgetstr("ue", NULL));
		ft_printf(tgetstr("se", NULL));
		elem = elem->next;
	}
}

int		main(int ac, char **av)
{
	t_select sel;

	check_arguments(&sel, ac, av);
	work(&sel);
	//ft_printf("geteven = {%s}\n", getenv("TERM"));
	//func();
	//check_temp();
	return (0);
}
