#include <stdio.h>
#include <string.h>
#include "curriculum.h"
#include "utils.h"

/**
 * Checks if a student has successfully passed a specific course (Grade >= 50 and not FF).
 * Bir öðrencinin belirli bir dersi baþarýyla geçip geçmediðini kontrol eder (Not >= 50 ve FF deðil).
 * * @param student_id - The ID of the student to check
 * @param student_id - Kontrol edilecek öðrencinin ID'si
 * @param course_id - The ID of the course to verify
 * @param course_id - Doðrulanacak kursun ID'si
 * @param g_head - Pointer to the head of the grade list
 * @param g_head - Not listesinin baþýna iþaret eden pointer
 * @return 1 if the student passed, 0 if failed or not taken
 * @return Öðrenci geçtiyse 1, kaldýysa veya dersi almadýysa 0 döner
 */
int has_passed_course(int student_id, int course_id, Grade *g_head) {
    Grade *current = g_head;
    while (current != NULL) {
        if (current->student_id == student_id && current->course_id == course_id) {
            // Passing grade is assumed as 50 and must not be FF
            // Geçme notu 50 kabul edelim ve FF olmamalý
            if (current->numeric_grade >= 50.0 && strcmp(current->letter_grade, "FF") != 0) {
                return 1; // Passed / Geçti
            }
        }
        current = current->next;
    }
    return 0; // Not passed or not taken / Geçmedi veya hiç almadý
}

/**
 * Analyzes and displays a student's progress towards graduation, including credits and required courses.
 * Bir öðrencinin mezuniyet ilerlemesini, kredilerini ve zorunlu derslerini analiz eder ve görüntüler.
 * * @param student_id - The ID of the student to analyze
 * @param student_id - Analizi yapýlacak öðrencinin ID'si
 * @param s_head - Pointer to the head of the student list
 * @param s_head - Öðrenci listesinin baþýna iþaret eden pointer
 * @param g_head - Pointer to the head of the grade list
 * @param g_head - Not listesinin baþýna iþaret eden pointer
 * @param c_head - Pointer to the head of the course list
 * @param c_head - Kurs listesinin baþýna iþaret eden pointer
 */
void check_graduation_status(int student_id, Student *s_head, Grade *g_head, Course *c_head) {
    Student *s = find_student_by_id(s_head, student_id);
    if (s == NULL) {
        printf("Student not found.\n");
        return;
    }

    printf("\n============================================================\n");
    printf("              DEGREE PROGRESS REPORT (BONUS)\n");
    printf("============================================================\n");
    printf("Student: %s %s (ID: %d)\n", s->first_name, s->last_name, s->id);
    printf("Major:   %s\n", s->major);
    printf("------------------------------------------------------------\n");

    // --- 1. REQUIRED COURSE CHECK / ZORUNLU DERS KONTROLÜ ---
    // Example Scenario: Required courses for CS department
    // Örnek Senaryo: CS Bölümü için þu dersler zorunlu olsun:
    const char *required_codes[] = {"CS101", "CS102", "MATH101", "CS201", "CS202"};
    int num_required = 5;
    int missing_count = 0;
    int i;
    printf("\n[CHECK 1] Required Courses:\n");
    printf("%-10s %-30s %-10s\n", "Code", "Status", "Grade");
    printf("---------------------------------------------------\n");

    for (i = 0; i < num_required; i++) {
        Course *c = find_course_by_code(c_head, required_codes[i]);
        if (c == NULL) {
            printf("%-10s %-30s\n", required_codes[i], "System Error: Course def missing");
            continue;
        }

        Grade *g = find_student_course_grade(g_head, s->id, c->id);
        
        if (g != NULL && g->numeric_grade >= 50) {
            printf("%-10s %-30s %.2f (%s)\n", required_codes[i], "[OK] Completed", g->numeric_grade, g->letter_grade);
        } else {
            printf("%-10s %-30s %s\n", required_codes[i], "[MISSING] Not Passed", "-");
            missing_count++;
        }
    }

    // --- 2. CREDIT CHECK / KREDÝ KONTROLÜ ---
    // Assuming 120 credits required for graduation
    // Mezuniyet için toplam 120 kredi gerektiðini varsayalým
    int required_credits = 120; 
    int total_credits = 0;
    
    Grade *curr_g = g_head;
    while(curr_g != NULL) {
        if(curr_g->student_id == s->id && curr_g->numeric_grade >= 50) {
            Course *crs = find_course_by_id(c_head, curr_g->course_id);
            if(crs) total_credits += crs->credits;
        }
        curr_g = curr_g->next;
    }

    printf("\n[CHECK 2] Credit Requirements:\n");
    printf("Total Credits Earned: %d / %d Required\n", total_credits, required_credits);
    
    if (total_credits >= required_credits) {
        printf("Status: [OK] Credit requirement met.\n");
    } else {
        printf("Status: [FAIL] Need %d more credits.\n", required_credits - total_credits);
        missing_count++; 
    }

    // --- FINAL OUTCOME / SONUÇ ---
    printf("\n============================================================\n");
    if (missing_count == 0 && total_credits >= required_credits) {
        printf("GRADUATION STATUS: >>> ELIGIBLE FOR GRADUATION <<<\n");
        printf("Congratulations! All requirements are met.\n");
    } else {
        printf("GRADUATION STATUS: >>> NOT ELIGIBLE <<<\n");
        printf("There are missing requirements. Student cannot graduate yet.\n");
    }
    printf("============================================================\n");
}
