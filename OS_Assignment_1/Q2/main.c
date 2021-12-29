#include <stdio.h>
#include<stdint.h>
extern void B(int64_t);

void A() {
    int64_t arg = 478560413000;
    printf("This is function A. (int_64 value: %ld)\n", arg);
    B(arg);
}

int main() {
    A();
    return 0;
}
