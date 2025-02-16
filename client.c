#include "client.h"
s_info g_info;

void exit_with_error(int no, char *message) {
    ft_printf("Exit No:%d\nExit Error Message:%s\n", no, message);
    exit(no);
}

void send_bit(unsigned char bit) {
	ft_printf("%d",bit);
    if (bit == 1) {
        if (kill(g_info.pid, SIGUSR2) == -1) {
            exit_with_error(5, ERR_KILL);
        }
    } else {
        if (kill(g_info.pid, SIGUSR1) == -1) {
            exit_with_error(5, ERR_KILL);
        }
    }
    usleep(400);
}

void sigusr_cont_handler(int signum, siginfo_t *info, void *context) {
    unsigned char tmp;
    (void)signum; (void)info; (void)context;
    
    if (g_info.i > 7)
	{
        g_info.i = 0;
        g_info.str++;
		ft_printf("\n");
        if (*(g_info.str) == '\0') {
            ft_printf("Data transfer complete!\n");
            exit(0);
        }
    }
    tmp = (*(g_info.str) >> (7 - g_info.i)) & 1;
    send_bit(tmp);
    g_info.i++;
}

int main(int ac, char **av) {
    if (ac < 3) exit_with_error(1, ERR_ARGUMENT);
    if (ac > 3) exit_with_error(2, ERR_TOO_MANY_ARGUMENTS);
    
    ft_printf("Client PID: %d\n", getpid());
    g_info.pid = ft_atoi(av[1]);
    g_info.str = av[2];
    g_info.i = 1;
    
    g_info.sa.sa_flags = SA_SIGINFO;
    g_info.sa.sa_sigaction = sigusr_cont_handler;
    
    
    if (sigaction(SIGUSR1, &(g_info.sa), NULL) == -1) 
        exit_with_error(4, ERR_SIGNAL);
    if (sigaction(SIGUSR2, &(g_info.sa), NULL) == -1) 
        exit_with_error(4, ERR_SIGNAL);
    
    while (*(g_info.str) != '\0') {
        usleep(400); 
        send_bit((*(g_info.str) >> 7) & 1);  
        g_info.i++; 
    }
    
    while (1) pause();  
    return 0;
}