#include <stdio.h>

void hello_world() {
    int total = 0;
    int i, j;
    printf("Hello, World!\n");
    for (i = 0; i < 1000000; i++) {
        for (j = 0; j < 1000000; j++) {
            total++;
        }
    }
}

int main() {
    hello_world();
    hello_world();
    hello_world();
    return 0;
}
