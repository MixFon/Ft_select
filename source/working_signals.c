
#include "../include/ft_select.h"


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
