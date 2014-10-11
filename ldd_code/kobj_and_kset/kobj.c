#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/slab.h>

static struct kobject *parent;
static struct kobject *child;
static struct kset    *c_kset;

static unsigned long flag = 1;

/*
    @function : this function can show the private
     date of kobject to user
*/
static ssize_t att_show(struct kobject *kobj, struct attribute *attr, char *buf)
{
    ssize_t count = 0 ;
    /*printf current attr's data(from the buf)*/
    count += sprintf(&buf[count], "%lu\n", flag);
    
    return count;
}

static ssize_t att_store(struct kobject *kobj, struct attribute *attr, 
                         const char *buf, size_t count)
{
    flag = buf[0] - '0';
    switch(flag)
    {
        case 0:
            kobject_uevent(kobj,KOBJ_ADD);
            break;
        case 1:
            kobject_uevent(kobj,KOBJ_REMOVE);
            break;
        case 2:
            kobject_uevent(kobj,KOBJ_CHANGE);
            break;
            kobject_uevent(kobj,KOBJ_MOVE);
            break;
        case 4:
            kobject_uevent(kobj,KOBJ_ONLINE);
            break;
        case 5:
            kobject_uevent(kobj,KOBJ_OFFLINE);
            break;
    }
    return count;
}

/*用于创建属性文件的数据结构*/
static struct attribute cld_att = 
{
    .name = "kobj of lee",
    .mode = S_IRUGO | S_IWUSR,
};
/*用于初始化时的kobj内ktype的操作集合*/
static struct sysfs_ops att_ops =
{
    .show = att_show,
    .store = att_store,
};
/*kobj的属性数据结构*/
static struct kobj_type cld_ktype = 
{
    .sysfs_ops = &att_ops,    
};

static int kobj_demo_init(void)
{
    int err ; 
    
    /*创建一个kobj用于kset的父目录，这个kobj在根目录下*/
    parent = kobject_create_and_add("pa_obj",NULL);
    
    child = kzalloc(sizeof(*child), GFP_KERNEL);
    
    c_kset = kset_create_and_add("c_kset", NULL, parent);
    
    child->kset = c_kset;
    
    err = kobject_init_and_add(child, &cld_ktype,parent, "cld_kobj");
    
    err = sysfs_create_file(child, &cld_att);
    
    return err;
    
}

static void kobj_demo_exit(void)
{
    sysfs_remove_file(child, &cld_att);
    
    kset_unregister(c_kset);
    kobject_del(child);
    kobject_del(parent);
}

module_init(kobj_demo_init);
module_exit(kobj_demo_exit);

MODULE_AUTHOR("LK");
MODULE_LICENSE("GPL");



