void	func(void)
{
	char *buf;
	char buffer[40];

	//buf = tparam(command, buffer, 40, parm);
	//buf = 
	tputs ("buf\n", 1, putchar);
	//if (buf != buffer)
		//free (buf);
	//ft_putstr_fd("\033[?1049h\033[H", 0);
	//ft_printf("\x1b[2J"); /* Clear the entire screen. */
	//ft_printf("\x1b[0;0f"); /* Move cursor to the top left hand corner */
	//ft_printf("\x1b[4m\x1b[34m%s\n", "Hello"); /* Move cursor to the top left hand corner */
}

void	check_temp(void)
{
	char	*name_term;
	int		bl;
	char	*buff;

	if (!(buff = (char *)malloc(sizeof(char) * 2048)))
		sys_err("Error malloc\n");
	name_term = getenv("TERM");
	ft_printf("name_term = {%s}\n", name_term);
	bl = tgetent(buff, name_term);
	if (bl == 1)
		ft_printf("Good enter. buff = [%s]\n", buff);
	else if(bl == 0)
		ft_printf("Error TERM.\n");
	else
		ft_printf("Global error.\n");
	ft_printf("md ={%s}\n", tgetstr ("md", &buff)); 
	//ft_printf("cl ={%s}\n", tgetstr ("cl", &buff)); //clear window
	//ft_printf("pc ={%s}\n", tgetstr ("pc", 0));
	//ft_printf("cm ={%s}\n", tgetstr ("cm", 0));
	//ft_printf("cb ={%s}\n", tgetstr ("cd", 0));
	//ft_printf("DL ={%s}\n", tgetstr ("DL", 0));
	//ft_printf("dl ={%s}\n", tgetstr ("dl", 0));
	ft_printf("vi ={%s}\n", tgetstr ("vi", 0));
	//ft_printf("bl ={%s}\n", tgetstr ("bl", 0));
	ft_printf("ve ={%s}\n", tgetstr ("ve", 0));
	ft_printf("le ={%s}\n", tgetstr ("le", 0));
	ft_printf("so ={%s}\n", tgetstr ("so", 0));
	//ft_printf("mr ={%s}\n", tgetstr ("mr", 0));
	//UP = tgetstr("up",0); /* сдвиг курсора на линию вверх */
	//ft_printf(UP);
	//ft_printf("2UP ={%s}", UP);
	//ft_printf("3UP ={%s}", UP);
	BC = tgetstr("le", 0);
	ft_printf("2\n");
	ft_printf("3\n");
	ft_printf("BC ={%s%s}\n", BC, BC);
	ft_printf("4\n");
	ft_printf("se ={%s}\n", tgetstr ("se", 0));
	//ft_printf("UP ={%s}\n", UP);
}
