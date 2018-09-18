/* GPLv2 (c) Airbus */
#include <debug.h>
#include <info.h>

extern info_t *info;
extern uint32_t __kernel_start__;
extern uint32_t __kernel_end__;
multiboot_memory_map_t *mmap_start;
multiboot_memory_map_t *mmap_end;
int *p;

void tp()
{
   debug("kernel mem [0x%x - 0x%x]\n", &__kernel_start__, &__kernel_end__);
   debug("MBI flags 0x%x\n", info->mbi->flags);


    mmap_start = (multiboot_memory_map_t *)info->mbi->mmap_addr;
    mmap_end = (multiboot_memory_map_t *)(info->mbi->mmap_addr + info->mbi->mmap_length);

    while(mmap_start < mmap_end) {
      debug("Ox%lx\n", mmap_start->addr);
      debug("0x%llx\n", mmap_start->len);
      debug("0x%x\n", mmap_start->type);
      debug("_________\n");
      *p = mmap_start->addr;
      debug("Reading at Ox%lx : %d\n", mmap_start->addr, p); //q3
      // Pas de seg fault puisque la mmu n'est pas intiialisée

      mmap_start++;
    }
}
