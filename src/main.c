#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "utils.h"
#include "student.h"
#include "course.h"
#include "professor.h"
#include "enrollment.h"
#include "grade.h"

/**
 * Application entry point. Initializes data, starts menu, and handles cleanup.
 * Uygulamanýn giriþ noktasýdýr. Verileri baþlatýr, menüyü baþlatýr ve temizlik iþlemlerini yapar.
 * @return 0 on successful termination / Baþarýlý sonlanmada 0 döner
 */
int main() {
    // 1. Initialize pointers to NULL / Pointerlarý NULL olarak baþlat
    Student *student_head = NULL;
    Course *course_head = NULL;
    Professor *professor_head = NULL;
    Enrollment *enrollment_head = NULL;
    Grade *grade_head = NULL;

    printf("Loading data...\n");

    // 2. Initial data load from CSV (Using address operator &)
    // CSV dosyalarýndan ilk veri yüklemesi (Adres operatörü & kullanarak)
    load_students_from_csv(&student_head);
    load_courses_from_csv(&course_head);
    load_professors_from_csv(&professor_head);
    load_enrollments_from_csv(&enrollment_head); 
    load_grades_from_csv(&grade_head);

    printf("Data loaded successfully.\n");

    // 3. Start the main menu system / Ana menü sistemini baþlat
    menu_main(&student_head, &course_head, &professor_head, &enrollment_head, &grade_head);

    // 4. Auto-save current data before exit (Important for persistence)
    // Çýkýþtan önce mevcut verileri otomatik kaydet (Kalýcýlýk için önemli)
    printf("Performing Auto-Save before exit...\n");
    save_students_to_csv(student_head, "data/students.csv");
    save_courses_to_csv(course_head, "data/courses.csv");
    save_professors_to_csv(professor_head, "data/professors.csv");
    save_enrollments_to_csv(enrollment_head, "data/enrollments.csv");
    save_grades_to_csv(grade_head, "data/grades.csv");
    printf("Auto-Save completed.\n");

    // 5. Secure exit and memory cleanup (Prevents leaks)
    // Güvenli çýkýþ ve bellek temizliði (Sýzýntýlarý önler)
    printf("Cleaning up memory...\n");
    free_all_students(student_head);
    free_all_courses(course_head);
    free_all_professors(professor_head);
    free_all_enrollments(enrollment_head);
    free_all_grades(grade_head);

    printf("System exited cleanly.\n");
    return 0;
}
