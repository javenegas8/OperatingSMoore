#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[]) {
    // Check if the user provided a command-line argument
    if (argc < 2) {
        printf("Usage: time1 <command>\n");
        exit(1);
    }

    // Record the start time
    int start_time = uptime();

    // Create a child process
    int child_pid = fork();

    if (child_pid == 0) {
        // Child process: Execute the specified command
        exec(argv[1], argv + 1);

        // If execvp fails, print an error message
        printf("Exec failed to execute %s.\n", argv[1]);
        exit(1);
    } else if (child_pid > 0) {
        // Parent process: Wait for the child to finish
        int status;
        wait(&status);

        // Record the end time
        int end_time = uptime();

        // Calculate the elapsed time in ticks
        int elapsed_ticks = end_time - start_time;

        // Print the elapsed time
        printf("Elapsed time: %d ticks\n", elapsed_ticks);
    } else {
        // Fork failed
        printf("Fork failed\n");
    }

    exit(1);
}

