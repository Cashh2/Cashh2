#include "../src/stumpy.h"

int main() {
    launch_dashboard();  // Optional UI
    vulnerable_function("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");  // Overflows buffer
    return 0;
}