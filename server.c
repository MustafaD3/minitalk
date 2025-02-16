#include "server.h"
s_info g_info;

void exit_with_error(int no, char *message) {
    ft_printf("Exit No:%d\nExit Error Message:%s\n", no, message);
    exit(no);
}

void sigusr_handler(int signum, siginfo_t *info, void *context) {
    (void)context;

    if (info->si_pid != 0)
        g_info.pid = info->si_pid;

    if (signum == SIGUSR2)
        g_info.c |= (1 << 7 - g_info.i);
    g_info.i++;

    if (g_info.i > 7) {
        ft_printf("Character: %c\n", g_info.c);
        g_info.i = 0;
        g_info.c = 0;
    }

    if (kill(g_info.pid, SIGUSR1) == -1) {
        exit_with_error(5, ERR_KILL);
    }
}

int main(int ac, char **av) {
    struct sigaction sa;

    g_info.i = 0;
    g_info.c = 0;
    if (ac != 1) 
        exit_with_error(1, ERR_TOO_MANY_ARGUMENTS);
    (void)av;
    ft_printf("Server PID: %d\n", getpid());
    sa.sa_sigaction = sigusr_handler;
    sa.sa_flags = SA_SIGINFO;
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
        exit_with_error(2, ERR_SIGNAL);
    if (sigaction(SIGUSR2, &sa, NULL) == -1)
        exit_with_error(3, ERR_SIGNAL);

    while (1)
        pause();

    return 0;
}