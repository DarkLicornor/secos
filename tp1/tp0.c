/* GPLv2 (c) Airbus */
#include <debug.h>
#include <info.h>
#include <segmem.h>

extern info_t *info;
// seg_desc_t : descripteur de segments
// gdt_reg_t : global descriptor table register
// get_gdr(aLocation) :
seg_desc_t GDT[6];


void showGdt() {
  gdt_reg_t gdtr;
  get_gdtr(gdtr);
  unsigned int numberEntries = (gdtr.limit + 1) / sizeof(seg_desc_t);

  printf("Ox%x\n", gdtr.addr); //la on a la gdt

  seg_desc_t * seg;
  for(unsigned int i = 0; i<numberEntries; i++) {
    seg = &gdtr.desc[i];
    printf("%d : Ox%x\n", i, seg->dpl);
    printf("%d : Ox%x\n", i, seg->type); //docs intel
  }
}

void initGdt() {
  //Creating GTDR
  gdt_reg_t gdtr;

  gdtr.limit = (5 * sizeof(seg_desc_t) ) - 1;
  gdtr.addr = 0x0000;

  //Creating code segment
  seg_desc_t * segCode;
  segCode->s = SEG_DESC_CODE_XR;
  segCode->dpl = 0;

  //Creating data segment
  seg_desc_t * segData;
  segCode->s = SEG_DESC_DATA_RW;
  segCode->dpl = 0;

  //Adding segments to my GTDR
  gdtr.desc[0] = NULL;
  gdtr.desc[1] = * segCode;
  gdtr.desc[2] = * segData;

  //Add
  set_gdtr(gdtr);

}

void tp() {
  //1 Show gdtr
  showGdt();
  initGdt();
}
