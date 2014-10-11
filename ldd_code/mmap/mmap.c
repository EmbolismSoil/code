#include <linux/module.h>
//#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/highmem.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gfp.h>
#include <linux/mm_types.h>
#include <linux/mm.h>
#include <linux/irqflags.h>

static struct cdev *pcdev;
static dev_t ndev;

/*physical page*/
static struct page *pg;
static struct timer_list timer;
unsigned long phys_addr = 0; 

 char *kernel_vir;
/*
 @fuction : timer_hanlder will print the data by string in 1s
*/
static void  timer_hanlder(unsigned long data)
{
	printk("timer_hanlder:%s\n", kernel_vir);
	printk("phys_addr = %u\n",page_to_phys(pg));
	timer.expires = jiffies + 2*HZ;
	add_timer(&timer);
}
/*
 @function : user's process can read the 
      physical address by this interface
*/
static ssize_t mem_read(struct file *filp, char  __user *buf,
									size_t size, loff_t  *ppos)
{
    long long unsigned int page = page_to_phys(pg);
	copy_to_user(buf,&page,sizeof(page));
	return 100;
}

static mem_open(struct inode *inodep, struct file *filep)
{
	return 0;
}

static int mem_mmap(struct file *filp, struct vm_area_struct *vma)
{
	int err = 0;
	unsigned long start = vma->vm_start;
	unsigned long size  = vma->vm_end - vma->vm_start;
	long long unsigned int page_off = vma->vm_pgoff;
	
	printk("the page_off is : %u \n",page_off<<12);
	
	local_irq_disable();
	err = remap_pfn_range(vma, start,page_off,size,vma->vm_page_prot);
	
	printk("remap finished,vma->mv_pgoff is:%u\n",vma->vm_pgoff<<12);
	local_irq_enable();
	
	kernel_vir = (char *)kmap(pg);
	return err;
}

static struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = mem_open,
	.read = mem_read,
	.mmap = mem_mmap,
};

int mymmap_init(void)
{
    int err = 0;
        /*alloc an minor by kernel*/
        alloc_chrdev_region(&ndev, 0, 1, "memap_dev");
		/*alloc an char device_struct*/
        pcdev = cdev_alloc();
        /*initialise*/
        pcdev->owner = THIS_MODULE;
        cdev_init(pcdev, &fops);
        /*add to the device_map so that we can 
        find it by default char open function*/
        cdev_add(pcdev, ndev, 1);

        /*alloc physical pages in zone HIGHMEM */
        pg = alloc_pages(GFP_HIGHUSER, 0);
        phys_addr = page_to_phys(pg);
        /*set the reserved bit to make sure 
        this page will not be swaped out*/
        SetPageReserved(pg);
        /*we got the pages from zone HIGHMEM
                  so we need to remap it */
        kernel_vir = (char *)kmap(pg);
    
        strcpy(kernel_vir,"alloc\n OK") ; 
   
   /*seting the timer*/
    init_timer(&timer);
    timer.function = timer_hanlder;
    timer.data = (unsigned long )kernel_vir;
    timer.expires = jiffies + HZ*2;
   	printk("kpa = %u",page_to_phys(pg));
   	printk("kpa = %u",page_to_phys(pg));
   	printk("kpa = %u",page_to_phys(pg)); 
    add_timer(&timer);
	

        return err;
}
int mymmap_exit(void)
{
	del_timer_sync(&timer);
	cdev_del(pcdev);
	unregister_chrdev_region(ndev,1);
	
	kunmap(pg);
	ClearPageReserved(pg);
	
	__free_pages(pg,0);
	
	return 0;
}
module_init(mymmap_init);
module_exit(mymmap_exit);

MODULE_AUTHOR("LK");
MODULE_LICENSE("GPL");

