// ===========================
// File: src/stumpy.h
// ===========================
#ifndef STUMPY_H
#define STUMPY_H

#include <stdint.h>
#include <stddef.h>

#define BUF_SIZE 16
#define CANARY_VALUE 0xDEADBEEF

void check_buffer_overflow(uint32_t* canary);
void dump_stack(void* start, size_t bytes);
void log_overflow(const char* function, uint32_t expected, uint32_t found);
void print_backtrace();
void trigger_real_time_alert();

#endif // STUMPY_H