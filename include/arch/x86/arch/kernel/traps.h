/*
 * Copyright 2016, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#ifndef __KERNEL_X86_TRAPS_H
#define __KERNEL_X86_TRAPS_H

#include <config.h>
#include <util.h>

static inline void arch_c_entry_hook(void)
{
#ifdef CONFIG_FSGSBASE_INST
    tcb_t *tcb = NODE_STATE(ksCurThread);
    x86_save_fsgs_base(tcb, SMP_TERNARY(getCurrentCPUIndex(), 0));
#endif
}

static inline void arch_c_exit_hook(void)
{
    /* Restore the values ofthe FS and GS base. */
    tcb_t *tcb = NODE_STATE(ksCurThread);
    x86_load_fsgs_base(tcb,  SMP_TERNARY(getCurrentCPUIndex(), 0));
}

void c_handle_syscall(word_t cptr, word_t msgInfo, syscall_t syscall)
VISIBLE NORETURN;

void restore_user_context(void)
VISIBLE NORETURN;

void c_nested_interrupt(int irq)
VISIBLE;

void c_handle_interrupt(int irq, int syscall)
VISIBLE NORETURN;

void c_handle_vmexit(void)
VISIBLE NORETURN;

#endif /* __KERNEL_X86_TRAPS_H */
