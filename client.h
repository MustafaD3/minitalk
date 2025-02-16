#ifndef CLIENT_H

# define CLIENT_H

# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include "./ft_printf/ft_printf.h"
# include "./ft_printf/libft/libft.h"
# define ERR_TOO_MANY_ARGUMENTS "too many arguments"
# define ERR_SIGNAL "sigaction error"
# define ERR_KILL "kill error, signal cannot be sent"
# define ERR_ARGUMENT "there have to be at least 2 arguments"

typedef struct info
{
	struct sigaction	sa;
	pid_t				pid;
	char				*str;
	int					i;
}	s_info;

#endif