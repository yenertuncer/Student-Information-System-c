#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdio.h>

// Basit test sayacı
int total_tests = 0;
int passed_tests = 0;

// Test Makrosu: Eðer koşul (condition) doğruysa PASS, değilse FAIL yazar.
#define TEST_ASSERT(condition, message) do { \
    total_tests++; \
    if (condition) { \
        printf("[PASS] %s\n", message); \
        passed_tests++; \
    } else { \
        printf("[FAIL] %s (Line %d)\n", message, __LINE__); \
    } \
} while(0)

// Sonuçları gösteren fonksiyon
void print_test_summary() {
    printf("\n=========================================\n");
    printf("TEST SUMMARY\n");
    printf("=========================================\n");
    printf("Total Tests: %d\n", total_tests);
    printf("Passed:      %d\n", passed_tests);
    printf("Failed:      %d\n", total_tests - passed_tests);
    printf("=========================================\n");
}

#endif

