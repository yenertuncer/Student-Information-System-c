#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/student.h"  // "../" demek: Bir üst klasördeki student.h'a git demek
#include "test_utils.h"

// Testleri çalýþtýran fonksiyon
void run_student_tests() {
    printf("\n--- Running Student Module Tests ---\n");

    Student *head = NULL;

    // 1. TEST: Öðrenci Ekleme
    Student s1;
    s1.id = 1001;
    strcpy(s1.first_name, "Ali");
    strcpy(s1.last_name, "Veli");
    strcpy(s1.email, "ali@univ.edu");
    strcpy(s1.phone, "555-1234");
    s1.enrollment_year = 2024;
    strcpy(s1.major, "CS");
    s1.gpa = 3.0;
    s1.next = NULL;

    int result = add_student(&head, &s1);
    TEST_ASSERT(result == 1, "Student Added Successfully");
    TEST_ASSERT(head != NULL, "List Head is not NULL");

    // 2. TEST: Ayný ID ile Ekleme (Hata vermeli)
    result = add_student(&head, &s1);
    TEST_ASSERT(result == 0, "Prevent Duplicate ID");

    // 3. TEST: Arama
    Student *found = find_student_by_id(head, 1001);
    TEST_ASSERT(found != NULL, "Student Found by ID");
    
    // 4. TEST: Silme
    result = delete_student(&head, 1001);
    TEST_ASSERT(result == 1, "Student Deleted Successfully");
    TEST_ASSERT(head == NULL, "List is Empty After Delete");

    // Temizlik
    free_all_students(&head);
}
