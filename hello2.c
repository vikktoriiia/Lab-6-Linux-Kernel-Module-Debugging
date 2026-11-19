#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/bug.h>

#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Lab 6: hello2 module");

static unsigned int count = 1;
module_param(count, uint, 0444);
MODULE_PARM_DESC(count, "Number of hello messages");

static int __init hello2_init(void)
{
    unsigned int i;

    pr_info("hello2: Module loading, count=%u\n", count);

    if (count == 0 || (count >= 5 && count <= 10))
        pr_warn("hello2: Warning! count=%u\n", count);

    // Checking for an invalid parameter value
    BUG_ON(count > 10);

    for (i = 0; i < count; i++)
        print_hello();

    return 0;
}

static void __exit hello2_exit(void)
{
    pr_info("hello2: Module unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

