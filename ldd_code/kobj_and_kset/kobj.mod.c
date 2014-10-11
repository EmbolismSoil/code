#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xfd5f6819, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x5bdb88fb, __VMLINUX_SYMBOL_STR(kobject_del) },
	{ 0xc327e564, __VMLINUX_SYMBOL_STR(kset_unregister) },
	{ 0x1635798d, __VMLINUX_SYMBOL_STR(sysfs_remove_file_ns) },
	{ 0xac02b43c, __VMLINUX_SYMBOL_STR(sysfs_create_file_ns) },
	{ 0xb92d6b13, __VMLINUX_SYMBOL_STR(kobject_init_and_add) },
	{ 0x56694a69, __VMLINUX_SYMBOL_STR(kset_create_and_add) },
	{ 0xe344f121, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9b29ea68, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xe0c4c876, __VMLINUX_SYMBOL_STR(kobject_create_and_add) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xc0dffd79, __VMLINUX_SYMBOL_STR(kobject_uevent) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "E0751AC950EDD1E43523F19");
