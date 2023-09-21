#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int t;
    t = uptime();
    printf("Uptime: %d ticks\n", t);
    exit(0); // Provide an exit status (0 in this case)
}


