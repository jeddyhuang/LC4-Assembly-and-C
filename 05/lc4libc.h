/*
 * lc4libc.h
 */

typedef int lc4int; 
typedef unsigned int lc4uint;
typedef char lc4char;

lc4int lc4_getc_echo();

void lc4_puts(lc4uint *str);
void lc4_draw_rect(lc4int x, lc4int y, lc4int width, lc4int height, lc4uint color);
void lc4_draw_sprite(lc4int x, lc4int y, lc4uint color, lc4uint *sprite);

void lc4_halt();
void lc4_reset_vmem();
void lc4_blt_vmem();
