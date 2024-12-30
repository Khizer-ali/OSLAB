#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Parent Process ID: %d\n", getpid());

    pid_t pid = fork();

    if (pid == 0) {
        printf("Child Process ID: %d\n", getpid());
        printf("Child's Parent Process ID: %d\n", getppid());
    } else if (pid > 0) {
        printf("Parent's Process ID: %d\n", getpid());
        printf("Parent's Child Process ID: %d\n", pid);
    } else {
        printf("Fork failed!\n");
        return 1;
    }

    return 0;
}
