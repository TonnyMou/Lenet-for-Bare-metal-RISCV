
#ifndef TIMER_SECONDS_H
#define TIMER_SECONDS_H

#include <stdint.h>
#include "trace_io.h"

#define SIMULATOR_FREQ_HZ 83000000  // 83 MHz

#if __riscv_xlen == 64

static inline uint64_t read_cycle() {
    uint64_t c;
    asm volatile("rdcycle %0" : "=r"(c));
    return c;
}

#else

static inline uint64_t read_cycle() {
    uint32_t hi, lo, hi2;
    do {
        asm volatile("rdcycleh %0" : "=r"(hi));
        asm volatile("rdcycle  %0" : "=r"(lo));
        asm volatile("rdcycleh %0" : "=r"(hi2));
    } while (hi != hi2);
    return ((uint64_t)hi << 32) | lo;
}

#endif

static inline void report_elapsed_time_seconds(uint64_t start, uint64_t end) {
    uint64_t cycles = end - start;
    double seconds = (double)cycles / SIMULATOR_FREQ_HZ;
    trace_print("[Timer] Time elapsed: ");
    trace_print_float(seconds,3);
    trace_print(" s\n");
    trace_print("Raw cycles: ");
    trace_print_uint64(cycles);
    trace_putchar('\n');
}

#endif // TIMER_SECONDS_H

