#include <stdio.h>
#include <stdlib.h>

// --- TEST ARAÇLARI ---
#include "test_utils.h"

// --- ANA PROJE DOSYALARI (UNITY BUILD) ---
// Hepsini buraya dahil ediyoruz ki bağlama hatası olmasın.
#include "../src/utils.c"
#include "../src/grade.c"
#include "../src/course.c"
#include "../src/enrollment.c"
#include "../src/professor.c"
#include "../src/student.c" 


// --- TEST DOSYALARI ---
#include "test_student.c"
#include "test_course.c"
#include "test_professor.c"
#include "test_integration.c"

int main() {
    printf("=========================================\n");
    printf("   FULL SYSTEM TEST SUITE STARTING\n");
    printf("=========================================\n");

    
    run_student_tests();
    run_course_tests();
    run_professor_tests();
    run_integration_tests();
    
    print_test_summary();

    printf("\nAll tests were completed. Enter for exit...\n");
    getchar();

    return 0;
}

