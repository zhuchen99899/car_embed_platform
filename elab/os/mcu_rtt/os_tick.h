/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * CMSIS-OS tick interface for RT-Thread
 */

#ifndef OS_TICK_H
#define OS_TICK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifndef __STATIC_INLINE
#define __STATIC_INLINE static inline
#endif

/// IRQ Handler type
typedef void (*IRQHandler_t)(void);

/// Initialize RTOS Kernel for creating objects
/// \return execution status
__STATIC_INLINE int32_t OS_Tick_Setup(uint32_t ticks, IRQHandler_t handler)
{
    (void)ticks;
    (void)handler;
    return 0;
}

/// Enable OS Tick
void OS_Tick_Enable(void);

/// Disable OS Tick
void OS_Tick_Disable(void);

/// Acknowledge OS Tick IRQ
__STATIC_INLINE void OS_Tick_AcknowledgeIRQ(void)
{
    return;
}

/// Get OS Tick IRQ number
__STATIC_INLINE int32_t OS_Tick_GetIRQn(void)
{
    return -1;
}

/// Get OS Tick Clock
__STATIC_INLINE uint32_t OS_Tick_GetClock(void)
{
    return 0;
}

/// Get OS Tick Interval
__STATIC_INLINE uint32_t OS_Tick_GetInterval(void)
{
    return 0;
}

/// Get OS Tick Count
__STATIC_INLINE uint32_t OS_Tick_GetCount(void)
{
    return 0;
}

/// Get OS Tick Overflow
__STATIC_INLINE uint32_t OS_Tick_GetOverflow(void)
{
    return 0;
}

#ifdef __cplusplus
}
#endif

#endif /* OS_TICK_H */
