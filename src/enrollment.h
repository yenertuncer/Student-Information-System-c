#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Enrollment {
    int id;
    int student_id;
    int course_id;
    int professor_id;
    char semester[20];
    char date[20];
    char status[20];
    struct Enrollment *next;
} Enrollment;

int load_enrollments_from_csv(Enrollment **head_ptr);
int save_enrollments_to_csv(Enrollment *head, const char *filename);
int add_enrollment(Enrollment **head_ptr, const Enrollment *new_enrollment);
int delete_enrollment(Enrollment **head_ptr, int id);
int drop_enrollment(Enrollment **head_ptr, int student_id, int course_id);
Enrollment* find_enrollment_by_id(Enrollment *head, int id);
int is_student_enrolled(Enrollment *head, int student_id, int course_id);
int get_enrollment_count(Enrollment *head, int course_id);
void display_student_enrollments(Enrollment *head, int student_id);
void display_course_roster(Enrollment *head, int course_id);
void display_all_enrollments(Enrollment *head);
void free_all_enrollments(Enrollment *head);
int count_enrollments(Enrollment *head);
int get_next_enrollment_id(Enrollment *head);

#endif
