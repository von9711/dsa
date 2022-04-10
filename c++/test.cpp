#include<stdio.h>
#include<stdlib.h>
//using namespace std;
//extern void _exit(register int);

void check()
{
    printf("hello world!\n");
}
void _start() {
    check();
    exit(0);
}
