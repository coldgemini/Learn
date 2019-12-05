#include<linux/module.h>
#include<linux/kernel.h>

int init_module(void)
{
        printk("HELLO WORLD");
        return 0;
}

void cleanup_module(void)
{
        printk("GOODBYE");
}
