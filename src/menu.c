#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "utils.h"
#include "curriculum.h"

// --- ANA MENÜ ---
void menu_main(Student **s_head, Course **c_head, Professor **p_head, Enrollment **e_head, Grade **g_head) {
    int choice;
    do {
        printf("\n==========================================\n");
        printf("      STUDENT INFORMATION SYSTEM\n");
        printf("==========================================\n");
        printf("1. Student Management\n");
        printf("2. Course Management\n");
        printf("3. Professor Management\n");
        printf("4. Enrollment Management\n");
        printf("5. Grade Management\n");
        printf("6. Reports\n");
        printf("7. System Options\n");
        printf("8. Graduation Check (Bonus)\n");
        printf("0. Exit\n");
        printf("------------------------------------------\n");
        choice = get_int_input("Enter your choice: ");

        switch (choice) {
            case 1: menu_student(s_head, c_head, g_head); break;
            case 2: menu_course(c_head); break;
            case 3: menu_professor(p_head, e_head, c_head); break;
            case 4: menu_enrollment(e_head, *s_head, *c_head, *g_head); break;
            case 5: menu_grade(g_head, *e_head, *s_head, *c_head); break;
            case 6: menu_reports(*s_head, *c_head, *p_head, *e_head, *g_head); break;
            case 7: menu_system_options(s_head, c_head, p_head, e_head, g_head); break;
            case 8: {
                int sid = get_int_input("Enter Student ID: ");
                check_graduation_status(sid, *s_head, *g_head, *c_head);
                break;
            }
            case 0: printf("Exiting system...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

// --- 1. ÖÐRENCÝ YÖNETÝMÝ ---
void menu_student(Student **head, Course **c_head, Grade **g_head) {
    int choice;
    do {
        printf("\n--- STUDENT MANAGEMENT ---\n");
        printf("1. Add New Student\n");
        printf("2. Edit Student Info\n");
        printf("3. Delete Student\n");
        printf("4. Search & View Details\n");
        printf("5. View Transcript\n");
        printf("6. Display All\n");
        printf("0. Back\n");
        choice = get_int_input("Choice: ");

        switch(choice) {
            case 1: {
                Student new_s;
                new_s.id = get_validated_id("Enter Student ID (e.g. 2024001): ");
                if (new_s.id == 0) break;
                if (find_student_by_id(*head, new_s.id)) {
                    printf("Error: ID already exists!\n");
                    break;
                }
                get_string_input("First Name: ", new_s.first_name, 50);
                get_string_input("Last Name: ", new_s.last_name, 50);
                do {
                    get_string_input("Email: ", new_s.email, 100);
                } while (!validate_email(new_s.email));
                get_string_input("Phone: ", new_s.phone, 20);
                new_s.enrollment_year = get_int_input("Enrollment Year: ");
                get_string_input("Major: ", new_s.major, 100);
                new_s.gpa = 0.0;
                new_s.next = NULL;
                add_student(head, &new_s);
                break;
            }
            case 2: {
                int id = get_int_input("Student ID to edit (0 to cancel): ");
                if (id == 0) break;
                Student *s = find_student_by_id(*head, id);
                if (s) {
                    Student temp = *s;
                    char buf[100];
                    printf("Editing %s %s. Enter new email (0 to skip): ", s->first_name, s->last_name);
                    get_string_input("", buf, 100);
                    if(strcmp(buf, "0") != 0 && validate_email(buf)) {
                        strcpy(temp.email, buf);
                    }
                    update_student(s, &temp);
                } else {
                    printf("Error: Student not found.\n");
                }
                break;
            }
            case 3:
                delete_student(head, get_int_input("ID to delete: "));
                break;
            case 4: {
                int sid = get_int_input("Enter Student ID: ");
                Student *s = find_student_by_id(*head, sid);
                if(s) display_student_details(s, *g_head, *c_head);
                else printf("Error: Not found.\n");
                break;
            }
            case 5: {
                int sid = get_int_input("Enter Student ID for Transcript: ");
                Student *s = find_student_by_id(*head, sid);
                if(s) display_student_transcript(s, *g_head, *c_head);
                else printf("Error: Student not found.\n");
                break;
            }
            case 6:
                display_all_students(*head);
                break;
        }
    } while(choice != 0);
}

// --- 2. DERS YÖNETÝMÝ ---
void menu_course(Course **head) {
    int choice;
    do {
        printf("\n--- COURSE MANAGEMENT ---\n");
        printf("1. Add New Course\n");
        printf("2. Edit Capacity\n");
        printf("3. Delete Course\n");
        printf("4. Search & View Details\n");
        printf("5. Display All\n");
        printf("0. Back\n");
        choice = get_int_input("Choice: ");

        switch(choice) {
            case 1: {
                Course c;
                c.id = get_validated_id("Course ID: ");
                if (c.id == 0) break;
                if(find_course_by_id(*head, c.id)) {
                    printf("Error: ID exists!\n");
                    break;
                }
                get_string_input("Code (e.g. CSE102): ", c.code, 20);
                get_string_input("Name: ", c.name, 100);
                c.credits = get_int_input("Credits: ");
                c.capacity = get_int_input("Capacity: ");
                get_string_input("Prerequisites (0 for none): ", c.prerequisites, 100);
                if(strcmp(c.prerequisites, "0") == 0) strcpy(c.prerequisites, "");
                c.next = NULL;
                add_course(head, &c);
                break;
            }
            case 2: {
                int id = get_int_input("Course ID: ");
                Course *c = find_course_by_id(*head, id);
                if(c) {
                    Course temp = *c;
                    temp.capacity = get_int_input("New Capacity: ");
                    update_course(c, &temp);
                } else printf("Not found.\n");
                break;
            }
            case 3:
                delete_course(head, get_int_input("ID to delete: "));
                break;
            case 4: {
                char code[20];
                get_string_input("Enter Course Code: ", code, 20);
                Course *c = find_course_by_code(*head, code);
                if(c) display_course_details(c);
                else printf("Not found.\n");
                break;
            }
            case 5:
                display_all_courses(*head);
                break;
        }
    } while(choice != 0);
}

// --- 3. PROFESÖR YÖNETÝMÝ ---
void menu_professor(Professor **head, Enrollment **e_head, Course **c_head) {
    int choice;
    do {
        printf("\n--- PROFESSOR MANAGEMENT ---\n");
        printf("1. Add Professor\n");
        printf("2. Edit Info\n");
        printf("3. Delete Professor\n");
        printf("4. Search & Details\n");
        printf("5. View Professor's Course Load\n");
        printf("6. Display All\n");
        printf("0. Back\n");
        choice = get_int_input("Choice: ");

        switch(choice) {
            case 1: {
                Professor p;
                p.id = get_validated_id("ID: ");
                if (p.id == 0) break;
                get_string_input("First Name: ", p.first_name, 50);
                get_string_input("Last Name: ", p.last_name, 50);
                get_string_input("Email: ", p.email, 100);
                get_string_input("Office: ", p.office, 20);
                p.next = NULL;
                add_professor(head, &p);
                break;
            }
            case 2: {
                int id = get_int_input("Professor ID to edit: ");
                Professor *p = find_professor_by_id(*head, id);
                if (p) {
                    Professor temp = *p;
                    get_string_input("New Office (0 to skip): ", temp.office, 20);
                    update_professor(p, &temp);
                } else printf("Not found.\n");
                break;
            }
            case 3:
                delete_professor(head, get_int_input("ID to delete: "));
                break;
            case 4: {
                int id = get_int_input("Professor ID: ");
                Professor *p = find_professor_by_id(*head, id);
                if(p) display_professor_details(p);
                else printf("Not found.\n");
                break;
            }
            case 5: {
                int id = get_int_input("Professor ID: ");
                Professor *p = find_professor_by_id(*head, id);
                if(p) display_professor_courses(id, *e_head, *c_head);
                else printf("Not found.\n");
                break;
            }
            case 6:
                display_all_professors(*head);
                break;
        }
    } while(choice != 0);
}

// --- 4. KAYIT YÖNETÝMÝ ---
void menu_enrollment(Enrollment **e_head, Student *s_head, Course *c_head, Grade *g_head) {
    int choice;
    do {
        printf("\n--- ENROLLMENT MANAGEMENT ---\n");
        printf("1. Enroll Student\n");
        printf("2. Drop Student\n");
        printf("3. View Student Enrollments\n");
        printf("4. View Course Roster\n");
        printf("0. Back\n");
        choice = get_int_input("Choice: ");

        switch(choice) {
            case 1: {
                int sid = get_int_input("Student ID: ");
                if (!find_student_by_id(s_head, sid)) {
                    printf("Error: Student not found.\n");
                    break;
                }
                int cid = get_int_input("Course ID: ");
                Course *c = find_course_by_id(c_head, cid);
                if (!c) {
                    printf("Error: Course not found.\n");
                    break;
                }
                // Kapasite ve Önkoþul Kontrolü
                if (get_enrollment_count(*e_head, cid) >= c->capacity) {
                    printf("Error: Course Full!\n");
                    break;
                }
                if (!check_prerequisites(sid, c, g_head, *e_head)) {
                    printf("Error: Prerequisite not met!\n");
                    break;
                }
                
                Enrollment e;
                e.student_id = sid;
                e.course_id = cid;
                e.professor_id = get_int_input("Assign Professor ID: ");
                get_string_input("Semester (e.g. 2024-FALL): ", e.semester, 20);
                get_current_date(e.date);
                strcpy(e.status, "Enrolled");
                e.id = get_next_enrollment_id(*e_head);
                e.next = NULL;
                add_enrollment(e_head, &e);
                break;
            }
            case 2: {
                int sid = get_int_input("Student ID: ");
                int cid = get_int_input("Course ID: ");
                drop_enrollment(e_head, sid, cid);
                break;
            }
            case 3:
                display_student_enrollments(*e_head, get_int_input("Student ID: "));
                break;
            case 4:
                display_course_roster(*e_head, get_int_input("Course ID: "));
                break;
        }
    } while(choice != 0);
}

// --- 5. NOT YÖNETÝMÝ ---
void menu_grade(Grade **g_head, Enrollment *e_head, Student *s_head, Course *c_head) {
    int choice;
    do {
        printf("\n--- GRADE MANAGEMENT ---\n");
        printf("1. Record/Update Grade\n");
        printf("2. View Course Statistics\n");
        printf("3. Grade Distribution\n");
        printf("0. Back\n");
        choice = get_int_input("Choice: ");

        switch(choice) {
            case 1: {
                int sid = get_int_input("Student ID: ");
                int cid = get_int_input("Course ID: ");
                if (!is_student_enrolled(e_head, sid, cid)) {
                    printf("Error: Student is not enrolled in this course!\n");
                    break;
                }
                float val = get_float_input("Grade (0-100): ");
                Grade *existing = find_student_course_grade(*g_head, sid, cid);
                if (existing) {
                    update_grade(existing, val, NULL);
                } else {
                    Grade g;
                    g.student_id = sid;
                    g.course_id = cid;
                    g.numeric_grade = val;
                    numeric_to_letter(g.numeric_grade, g.letter_grade);
                    get_string_input("Semester: ", g.semester, 20);
                    g.id = get_next_grade_id(*g_head);
                    g.next = NULL;
                    add_grade(g_head, &g);
                }
                calculate_all_gpas(s_head, *g_head, c_head);
                break;
            }
            case 2:
                display_grade_statistics(*g_head, get_int_input("Course ID: "));
                break;
            case 3:
                display_grade_distribution(*g_head, get_int_input("Course ID: "));
                break;
        }
    } while(choice != 0);
}

// --- 6. RAPORLAR ---
void menu_reports(Student *s_head, Course *c_head, Professor *p_head, Enrollment *e_head, Grade *g_head) {
    int choice;
    do {
        printf("\n--- REPORTS ---\n");
        printf("1. Transcript\n");
        printf("2. Course Roster\n");
        printf("3. Grade Statistics\n");
        printf("4. Professor Course Load\n");
        printf("0. Back\n");
        choice = get_int_input("Choice: ");

        switch(choice) {
            case 1: {
                int sid = get_int_input("Enter Student ID: ");
                Student *s = find_student_by_id(s_head, sid);
                if(s) display_student_transcript(s, g_head, c_head);
                else printf("Student not found.\n");
                break;
            }
            case 2:
                display_course_roster(e_head, get_int_input("Course ID: "));
                break;
            case 3:
                display_grade_statistics(g_head, get_int_input("Course ID: "));
                break;
            case 4: {
                int pid = get_int_input("Professor ID: ");
                display_professor_courses(pid, e_head, c_head);
                break;
            }
        }
    } while(choice != 0);
}

// --- 7. SÝSTEM SEÇENEKLERÝ ---
void menu_system_options(Student **s_head, Course **c_head, Professor **p_head, Enrollment **e_head, Grade **g_head) {
    int choice;
    printf("\n--- SYSTEM OPTIONS ---\n");
    printf("1. Save Data\n");
    printf("2. Load Sample Data\n");
    printf("3. Create Backup\n");
    printf("0. Back\n");
    choice = get_int_input("Choice: ");

    switch(choice) {
        case 1:
            save_students_to_csv(*s_head, "data/students.csv");
            save_courses_to_csv(*c_head, "data/courses.csv");
            save_professors_to_csv(*p_head, "data/professors.csv");
            save_enrollments_to_csv(*e_head, "data/enrollments.csv");
            save_grades_to_csv(*g_head, "data/grades.csv");
            printf("Success: All data saved.\n");
            break;
        case 2:
            free_all_students(*s_head); *s_head = NULL;
            free_all_courses(*c_head); *c_head = NULL;
            free_all_professors(*p_head); *p_head = NULL;
            free_all_enrollments(*e_head); *e_head = NULL;
            free_all_grades(*g_head); *g_head = NULL;
            load_students_from_csv(s_head);
            load_courses_from_csv(c_head);
            load_professors_from_csv(p_head);
            load_enrollments_from_csv(e_head);
            load_grades_from_csv(g_head);
            printf("Success: Sample data loaded from CSV files.\n");
            break;
        case 3:
            save_students_to_csv(*s_head, "data/students_backup.csv");
            save_courses_to_csv(*c_head, "data/courses_backup.csv");
            save_professors_to_csv(*p_head, "data/professors_backup.csv");
            save_enrollments_to_csv(*e_head, "data/enrollments_backup.csv");
            save_grades_to_csv(*g_head, "data/grades_backup.csv");
            printf("Success: Backup files created.\n");
            break;
    }
}
