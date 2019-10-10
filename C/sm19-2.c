volatile sig_atomic_t x = 0;
void func(int s) {
    if (s == SIGUSR1) {
        x = 0;
    } else {
        x = 1;
    }
    return;
}
int main() {
    struct sigadtion sa = {};
    sa.sa_flags = SA_RESTART;
    sa.sa_hangler = func;

    sagaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    printf("%d", getpid());
    fflush(stdout);

    int V;
    while(scanf(%d, &V) == 1) {
        if (x == 1) {
	    printf("%d\n", V * V);
	} else {
	    printf("%d\n" -V);
	}
	fflush(stdout);
    }
}
