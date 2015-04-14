/*
    Copyright � 2013-2015, The AROS Development Team. All rights reserved.
    $Id$
*/

#ifndef KERNEL_INTERN_H_
#define KERNEL_INTERN_H_

#include <aros/libcall.h>
#include <inttypes.h>
#include <exec/lists.h>
#include <exec/execbase.h>
#include <exec/memory.h>
#include <utility/tagitem.h>
#include <stdio.h>
#include <stdarg.h>

#include "kernel_arm.h"

#undef KernelBase
struct KernelBase;

/* Use system timer 3 for our scheduling heartbeat */
#define VBLANK_TIMER            3
#define VBLANK_INTERVAL         (1000000 / 50)

#define KERNEL_PHYS_BASE        0x07800000
#define KERNEL_VIRT_BASE        0xff800000

#define VFPEnable               (1 << 30) 
#define VFPSingle               (3 << 20) 
#define VFPDouble               (3 << 22)

void cpu_Probe(struct ARM_Implementation *);
void cpu_Init(struct ARM_Implementation *, struct TagItem *);

void platform_Init(struct ARM_Implementation *, struct TagItem *);

void core_SetupMMU(struct TagItem *msg);
void core_SetupIntr(void);

void *KrnAddSysTimerHandler(struct KernelBase *);

intptr_t krnGetTagData(Tag tagValue, intptr_t defaultVal, const struct TagItem *tagList);
struct TagItem *krnFindTagItem(Tag tagValue, const struct TagItem *tagList);
struct TagItem *krnNextTagItem(const struct TagItem **tagListPtr);

struct KernelBase *getKernelBase();

#ifdef bug
#undef bug
#endif
#ifdef D
#undef D
#endif
#if DEBUG
#define D(x) x
#define DALLOCMEM(x)
#else
#define D(x)
#define DALLOCMEM(x)
#endif

#define __STR(x) #x
#define STR(x) __STR(x)

AROS_LD2(int, KrnBug,
         AROS_LDA(const char *, format, A0),
         AROS_LDA(va_list, args, A1),
         struct KernelBase *, KernelBase, 12, Kernel);

static inline void bug(const char *format, ...)
{
    struct KernelBase *kbase = getKernelBase();
    va_list args;
    va_start(args, format);
    AROS_SLIB_ENTRY(KrnBug, Kernel, 12)(format, args, kbase);
    va_end(args);
}

// NB - we use sizeof(ExceptionContext) on the stack

#define VECTCOMMON_START \
    "           sub     sp, sp, #6*4           \n" \
    "           stmfd   sp!, {r0-r12}          \n" \
    "           mov     r0, sp                 \n" \
    "           mrs     r1, spsr               \n" \
    "           str     r1, [r0, #16*4]        \n" \
    "           str     lr, [r0, #15*4]        \n"

#define VECTCOMMON_END \
    "           ldr     r1, [sp, #16*4]        \n" \
    "           msr     spsr, r1               \n" \
    "           and     r1, r1, #31            \n" \
    "           cmp     r1, #16                \n" \
    "           cmpne   r1, #31                \n" \
    "           bne     1f                     \n" \
    "           add     r1, sp, #13*4          \n" \
    "           ldm     r1, {sp}^              \n" \
    "           add     r1, sp, #14*4          \n" \
    "           ldm     r1, {lr}^              \n" \
    "1:         ldr     lr, [sp, #15*4]        \n" \
    "           ldmfd   sp!, {r0-r12}          \n" \
    "           add     sp, sp, #6*4           \n" \
    "           movs    pc, lr                 \n"

#define STORE_TASKSTATE(task, regs)                                             \
    struct ExceptionContext *ctx = task->tc_UnionETask.tc_ETask->et_RegFrame;   \
    int __task_reg_no;                                                          \
    for (__task_reg_no = 0; __task_reg_no < 12; __task_reg_no++)                \
    {                                                                           \
        ctx->r[__task_reg_no] = ((uint32_t *)regs)[__task_reg_no];              \
    }                                                                           \
    ctx->ip = ((uint32_t *)regs)[12];                                           \
    ctx->sp = task->tc_SPReg = ((uint32_t *)regs)[13];                          \
    ctx->lr = ((uint32_t *)regs)[14];                                           \
    ctx->pc = ((uint32_t *)regs)[15];                                           \
    ctx->cpsr = ((uint32_t *)regs)[16];

#define RESTORE_TASKSTATE(task, regs)                                           \
    struct ExceptionContext *ctx = task->tc_UnionETask.tc_ETask->et_RegFrame;   \
    int __task_reg_no;                                                          \
    for (__task_reg_no = 0; __task_reg_no < 12; __task_reg_no++)                \
    {                                                                           \
        ((uint32_t *)regs)[__task_reg_no] = ctx->r[__task_reg_no];              \
    }                                                                           \
    ((uint32_t *)regs)[12] = ctx->ip;                                           \
    ((uint32_t *)regs)[13] = ctx->sp = task->tc_SPReg;                          \
    ((uint32_t *)regs)[14] = ctx->lr;                                           \
    ((uint32_t *)regs)[15] = ctx->pc;                                           \
    ((uint32_t *)regs)[16] = ctx->cpsr;

#endif /*KERNEL_INTERN_H_*/