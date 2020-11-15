#ifndef RISC_V_SEC_EXCEPTION_H
#define RISC_V_SEC_EXCEPTION_H

#define INST_ADDR_MISALIGNED    0
#define INST_ACCESS_FAULT       1
#define ILLEGAL_INSTRUCTION     2
#define BREAKPOINT              3
#define LOAD_ADDR_MISALIGNED    4
#define LOAD_ACCESS_FAULT       5
#define STORE_ADDR_MISALIGNED   6
#define STORE_ACCESS_FAULT      7
#define ENV_CALL_FROM_U         8
#define ENV_CALL_FROM_S         9
#define ENV_CALL_FROM_H         10
#define ENV_CALL_FROM_M         11
#define INST_PAGEFAULT          12
#define LOAD_PAGEFAULT          13
#define STORE_PAGEFAULT         15

#define USER_SOFTWARE_INT       0
#define SUPERV_SOFTWARE_INT     1
#define MACHINE_SOFTWARE_INT    3
#define USER_TIMER_INT          4
#define SUPERV_TIMER_INT        5
#define MACHINE_TIMER_INT       7
#define USER_EXTERNAL_INT       8
#define SUPERV_EXTERNAL_INT     9
#define MACHINE_EXTERNAL_INT    11

#endif
