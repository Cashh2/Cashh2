// ===========================
// File: src/helper.c
// ===========================
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include <fcntl.h>
#include <string.h>
#include "helper.h"
#include "stumpy.h"

void dump_stack(void* start, size_t bytes) {
    printf("🧵 Stack dump (%zu bytes):\n", bytes);
    unsigned char* ptr = (unsigned char*)start;
    for (size_t i = 0; i < bytes; i++) {
        if (i % 16 == 0) printf("\n0x%p: ", ptr + i);
        printf("%02X ", ptr[i]);
    }
    printf("\n\n");
}

void log_overflow(const char* function, uint32_t expected, uint32_t found) {
    FILE* log = fopen("../reports/overflow_log.txt", "a");
    if (!log) return;

    time_t now = time(NULL);
    fprintf(log, "[%s] Overflow in %s: Expected=0x%X, Found=0x%X\n",
            ctime(&now), function, expected, found);
    fclose(log);
}

void print_backtrace() {
    void* callstack[128];
    int frames = backtrace(callstack, 128);
    char** strs = backtrace_symbols(callstack, frames);

    printf("📍 Backtrace:\n");
    for (int i = 0; i < frames; ++i) {
        printf("%s\n", strs[i]);
    }
    free(strs);
}

void trigger_real_time_alert() {
    printf("🔔 Real-time alert: Buffer overflow occurred!\n");
    // Optional: sound a beep or write to system log
    fprintf(stderr, "\a");
    system("notify-send 'stumpy-segfa' '🚨 Buffer Overflow Detected'");
}

void check_buffer_overflow(uint32_t* canary) {
    if (*canary != CANARY_VALUE) {
        printf("\n🚨 stumpy-segfa: Buffer overflow detected!\n");
        printf("Expected: 0x%X, Found: 0x%X\n", CANARY_VALUE, *canary);
        log_overflow("vulnerable_function", CANARY_VALUE, *canary);
        dump_stack((void*)canary - 32, 64);
        print_backtrace();
        trigger_real_time_alert();
        exit(EXIT_FAILURE);
    }
}

void launch_dashboard() {
    initscr();
    noecho();
    cbreak();
    WINDOW* win = newwin(10, 50, 1, 1);
    box(win, 0, 0);
    mvwprintw(win, 1, 2, "🪵 stumpy-segfa Monitor");
    mvwprintw(win, 3, 2, "Status: Monitoring stack...");
    mvwprintw(win, 5, 2, "Press any key to exit.");
    wrefresh(win);
    getch();
    endwin();
}
