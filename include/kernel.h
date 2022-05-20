#ifndef VOID32_TTY_H
#define VOID32_TTY_H

#define MEM_BEGIN 0x00000000
#define MEM_END (MEM_BEGIN + 0x40000000)
#define TTY_BEGIN MEM_END
#define TTY_END (TTY_BEGIN + 0x10000000)
#define HDD_BEGIN TTY_END
#define HDD_END (HDD_BEGIN + 0x80000000)

#define HDD_R_IDLE  0x10
#define HDD_W_IDLE  0x11
#define TTY_IDLE  0x20

#endif
