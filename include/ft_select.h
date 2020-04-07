#ifndef FT_SELECT_H
# define FT_SELECT_H

# define BUF 0

# include "../libft/libft.h"
# include "termcap.h"
# include "unistd.h"
# include <stdlib.h>

typedef struct		s_elem
{
	char			*title;
	int				choosed		: 2;
	//int				underline	: 2;
	int				cursor		: 2;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_select
{
	char			*name_term;
	int				w_term;
	int				h_term;
	int				max_len;;
	t_elem			*elem;
}					t_select;

#endif
