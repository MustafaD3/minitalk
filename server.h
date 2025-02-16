#ifndef SERVER_H

# define SERVER_H

# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include "./ft_printf/ft_printf.h"
# define ERR_TOO_MANY_ARGUMENTS "too many arguments"
# define ERR_SIGNAL "sigaction error"
# define ERR_KILL "kill error, signal cannot be sent"

typedef struct c_info
{
	pid_t				pid;
	unsigned char				c;
	int					i;
}	s_info;
#endif