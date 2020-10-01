/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 09:51:36 by widraugr          #+#    #+#             */
/*   Updated: 2020/10/01 09:55:39 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "../libft/libft.h"
# include "termcap.h"
# include "unistd.h"
# include "termios.h"
# include "stdlib.h"
# include "sys/ioctl.h"

# define TERM_SMAL	"The terminal size is too small to display.\n"
# define INCREASE	"Increase the size of the terminal."

# define K_LEFT		186
# define K_RIGHT	185
# define K_DOWN		184
# define K_UP		183
# define K_ENTER	10
# define K_SPACE	32
# define K_BSPACE	127
# define K_DELETE	126
# define K_ESC		27

typedef struct		s_elem
{
	char			*title;
	int				choosed		: 2;
	int				cursor		: 2;
	struct s_elem	*next;
	struct s_elem	*prev;
}					t_elem;

typedef struct		s_select
{
	char			*name_term;
	int				w_term;
	int				h_term;
	int				max_len;
	int				columns;
	int				bl_err_size	: 2;
	int				count_elem;
	struct termios	old_term;
	struct termios	new_term;
	t_elem			*elem;
	t_elem			*elem_cursor;
}					t_select;

/*
** Данная глобальная переменная используется при отправке сигналов:
**	- прехода в фоновый режим.
**	- выхода из фонового режима.
**	- изменения размера экрана.
**	- принудительного завершения программы.
*/

t_select			*g_sel;

void				press_esc(t_select *sel);
void				set_signals(void);
void				working_signals(int sig);
/*
** File new_elem.c
*/
t_elem				*new_elem(char *title);
void				to_loop_elements(t_select *sel);
void				removing_unnecessary_elements(t_select *sel);
void				infill_args(t_select *sel, int ac, char **av);
void				print_elem(t_elem *elem);
/*
** File check_arguments.c
*/
void				check_arguments(t_select *sel, int ac, char **av);
int					hash_sum(char *buf);
void				press_esc(t_select *sel);
void				press_right(t_select *sel);
void				press_left(t_select *sel);
/*
** File press_space.c
*/
void				press_space(t_select *sel);
void				press_up(t_select *sel);
void				press_down(t_select *sel);
void				press_enter(t_select *sel);
void				calculate_max_len(t_select *sel);
/*
** File press_delete.c
*/
void				press_delete(t_select *sel);
void				working_key(t_select *sel, int key);
void				print_title(t_elem *elem, int max_len);
void				print_elements(t_select *sel);
int					calculate_colum(t_select *sel);
/*
** File print_elem_or_error_size.c
*/
void				print_elem_or_error_size(t_select *sel);
void				work(t_select *sel);
void				seve_temp(t_select *sel);
void				background_mode(void);
void				standart_mode(void);
/*
** File working_signals.c
*/
void				working_signals(int sig);
void				set_signals(void);
int					main(int ac, char **av);
#endif
