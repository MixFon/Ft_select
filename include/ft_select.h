#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "../libft/libft.h"
# include "termcap.h"
# include "unistd.h"
# include "termios.h"
# include "stdlib.h"
# include "sys/ioctl.h"

# define SPACES		1000

# define STR		"                                                    "

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
	int				count_elem;
	struct termios	old_term;
	struct termios	new_term;
	t_elem			*elem;
	t_elem			*elem_cursor;
	char			spaces[1000];
}					t_select;


void	press_esc(t_select *sel);
#endif
