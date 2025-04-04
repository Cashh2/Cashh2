// ===========================
// File: src/stumpy.c
// ===========================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stumpy.h"
#include "helper.h"
#include "helper.c"

void vulnerable_function(const char* input) {
    uint32_t canary = CANARY_VALUE;
    char buffer[BUF_SIZE];

    printf("\n🪵 stumpy-segfa: Writing input into buffer...\n");
    strcpy(buffer, input); // Vulnerable

    check_buffer_overflow(&canary);
    printf("✅ No overflow detected.\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input string>\n", argv[0]);
        return 1;
    }
    vulnerable_function(argv[1]);
    return 0;
}