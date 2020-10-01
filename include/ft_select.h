/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <widraugr@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 08:58:14 by widraugr          #+#    #+#             */
/*   Updated: 2020/10/01 08:58:24 by widraugr         ###   ########.fr       */
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

void	press_esc(t_select *sel);
void	set_signals(void);
void	working_signals(int sig);
#endif
