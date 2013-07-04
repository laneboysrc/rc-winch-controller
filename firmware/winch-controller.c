#include <pic12f1840.h>

char test;

extern void Init_input(void);

void main(void) {
    test=0;
    Init_input();
}

