NAME=minitalk
SERVER=server
CLIENT=client
FT_PRINTF_PATH=ft_printf
FLAGS= -Wall -Wextra -Werror
CC=cc

all:COMPILER_PRINTF_AND_LIBFT $(SERVER) $(CLIENT)

COMPILER_PRINTF_AND_LIBFT:
	cd ft_printf && make

$(SERVER):server.c
	$(CC)  -o $(SERVER) $< -L $(FT_PRINTF_PATH) -lftprintf
	
$(CLIENT):client.c
	$(CC)  -o $(CLIENT) $< -L $(FT_PRINTF_PATH) -lftprintf
clean:
	rm -f server