// ===========================
// File: src/utils.h
// ===========================
#ifndef HELPER_H
#define HELPER_H

#include <stddef.h>
#include <stdint.h>

void dump_stack(void* start, size_t bytes);
void log_overflow(const char* function, uint32_t expected, uint32_t found);
void print_backtrace();
void launch_dashboard();
void trigger_real_time_alert();

#endif // HELPER_H