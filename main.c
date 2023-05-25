#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int global_var = 10;

int main() {
    int local_var = 2;
    fprintf(stdout, "Global var address = %p\n", &global_var);
    fprintf(stdout, "Local var address = %p\n", &local_var);
    fprintf(stdout, "Global var = %d\n", global_var);
    fprintf(stdout, "Local var = %d\n", local_var);
    int fork_pid = fork();
    if (fork_pid == -1) {
        fprintf(stderr, "error in fork()");
        return 1;
    }
    // child
    else if (fork_pid == 0) {
        fflush(stdout);
        fprintf(stdout, "Child:\n");
        fprintf(stdout, "\tpid = %d, ppid = %d\n", getpid(), getppid());
        fprintf(stdout, "\tGlobal var address = %p\n", &global_var);
        fprintf(stdout, "\tLocal var address = %p\n", &local_var);
        local_var = 5;
        global_var = 6;
        fprintf(stdout, "\tGlobal var = %d\n", global_var);
        fprintf(stdout, "\tLocal var = %d\n", local_var);
        sleep(10);
        exit(5);
    }
        // parent
    else if (fork_pid > 0) {
        fflush(stdout);
        fprintf(stdout, "Parent:\n");
        fprintf(stdout, "\tGlobal var address = %p\n", &global_var);
        fprintf(stdout, "\tLocal var address = %p\n", &local_var);
        fprintf(stdout, "\tGlobal var = %d\n", global_var);
        fprintf(stdout, "\tLocal var = %d\n", local_var);
        sleep(20);
        int child_status;
        pid_t wait_pid_result = waitpid(fork_pid, &child_status, 0);
        if (wait_pid_result == -1) {
            fprintf(stderr, "Error in waitpid()\n");
            return 1;
        }
        if (WIFEXITED(child_status)) {
            printf("Child process exited with code: %d\n", WEXITSTATUS(child_status));
        }
    }
    sleep(1);
    return 0;
}
