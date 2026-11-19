#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>

#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Lab 6: hello1 module");

struct hello_event {
    struct list_head list;
    ktime_t start;
    ktime_t end;
};

static LIST_HEAD(hello_list);
static unsigned int call_count = 0;

void print_hello(void)
{
    struct hello_event *event;

    call_count++;

    // Simulate memory allocation failure on the fifth call
    if (call_count == 5)
        event = NULL;
    else
        event = kmalloc(sizeof(*event), GFP_KERNEL);

    // Check memory allocation
    if (!event) {
        pr_err("hello1: Memory allocation failed at message %u\n",
               call_count);
        return;
    }

    event->start = ktime_get();
    pr_info("Hello, world!\n");
    event->end = ktime_get();

    list_add_tail(&event->list, &hello_list);
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
    pr_info("hello1: Module loaded\n");
    return 0;
}

static void __exit hello1_exit(void)
{
    struct hello_event *event, *tmp;
    int i = 1;

    list_for_each_entry_safe(event, tmp, &hello_list, list) {
        pr_info("hello1: Print %d took %lld ns\n",
                i++, (long long)ktime_to_ns(
                    ktime_sub(event->end, event->start)));

        list_del(&event->list);
        kfree(event);
    }

    pr_info("hello1: Module unloaded\n");
}

module_init(hello1_init);
module_exit(hello1_exit);

