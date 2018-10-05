/* GPLv2 (c) Airbus */
#include <debug.h>
#include <info.h>
#include <segmem.h>
#include <string.h>


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

void initFlatDesc(seg_desc_t * desc, uint64_t type) {
  desc->raw     = 0;
  desc->limit_1 = 0xffff;
  desc->limit_2 = 0xf;
  desc->type    = type;
  desc->dpl     = 0; //Niveau de privilège
  desc->d       = 1;
  desc->g       = 1;
  desc->s       = 1;
  desc->p       = 1;
}

void initWithBaseDesc(seg_desc_t * desc, uint64_t type, uint64_t base1, uint64_t base2) {
  desc->raw     = 0;
  desc->type    = type;
  desc->dpl     = 0;
  desc->d       = 1;
  desc->g       = 0;
  desc->s       = 1;
  desc->p       = 1;
  desc->base_1  = base1;
  desc->base_2  = base2;
}

void initGdt() {

  gdt_reg_t gdtr;
  GDT[0].raw = 0ULL;

  initFlatDesc(&GDT[1], SEG_DESC_CODE_XR);
  initFlatDesc(&GDT[2], SEG_DESC_DATA_RW);

  gdtr.desc = GDT;
  gdtr.limit = sizeof(GDT) - 1;
  set_gdtr(gdtr);

  set_cs(gdt_krn_seg_sel(1)); 
  set_ss( gdt_krn_seg_sel(2));
  set_ds( gdt_krn_seg_sel(2));
  set_es( gdt_krn_seg_sel(2));
  set_fs( gdt_krn_seg_sel(2));
  set_gs( gdt_krn_seg_sel(2));
}

void last() {
  initWithBaseDesc(&GDT[3], SEG_DESC_DATA_RW, 0x0, 0x60);
  set_es( gdt_krn_seg_sel(3));

  char  src[64];
  char *dst = 0;
  memset(src, 0xff, 64);

  set_es(gdt_krn_seg_sel(3));

  //_memcpy8(dst, src, 32);
  _memcpy8(dst, src, 64);
}



void tp() {
  //1 Show gdtr
  showGdt();

  //Init gdtr
  initGdt();

  last();

}
