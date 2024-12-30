#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Parent Process ID: %d\n", getpid());

    pid_t pid = fork();

    if (pid == 0) {
        printf("Child Process ID: %d\n", getpid());
    } else if (pid > 0) {
        printf("Child Process ID printed by Parent: %d\n", pid);
    } else {
        printf("Fork failed!\n");
        return 1;
    }

    return 0;
}
