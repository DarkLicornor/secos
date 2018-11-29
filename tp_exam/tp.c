/* GPLv2 (c) Airbus */
#include <debug.h>
#include <info.h>
#include <gdt.h>

extern uint32_t __kernel_start__;
extern uint32_t __kernel_end__;
extern info_t *info;

// __attribute__((section(".user")));

void user1(){

}

void user2(){

}

void tp0()
{
   debug("kernel mem [0x%x - 0x%x]\n", &__kernel_start__, &__kernel_end__);
   debug("MBI flags 0x%x\n", info->mbi->flags);

   mbi_t *mbi;
   multiboot_memory_map_t *start;
   multiboot_memory_map_t *end;

   mbi   = info->mbi;
   start = (multiboot_memory_map_t*) mbi->mmap_addr;
   end   = (multiboot_memory_map_t*)(mbi->mmap_addr + mbi->mmap_length);

   while(start < end) {
      debug("mmap 0x%llx - 0x%llx (%d)\n",
            start->addr, start->addr+start->len, start->type);
      start++;
   }
 }

void init_kernel() {
  init_gdt();
  //activate_pagination();
  //init_interruptions();
}
void tp()
{
  init_kernel()
}
