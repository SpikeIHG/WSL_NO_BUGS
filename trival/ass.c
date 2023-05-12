#include<stdio.h>
int main(void)

{

    asm(
        "mov $10 %rdi"
        "mov $20 %rsi"
        "add %rdi %rsi"
        "mov %rsi %rax"
        "xor %rsi %rsi"
        "test %rax %rsi"
        "ret"
    );


}