#ifndef GRADE_H
#define GRADE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Grade {
    int id;
    int enrollment_id;
    int student_id;
    int course_id;
    char letter_grade[5];
    float numeric_grade;
    char semester[20];
    struct Grade *next;
} Grade;

int load_grades_from_csv(Grade **head_ptr);
int save_grades_to_csv(Grade *head, const char *filename);
int add_grade(Grade **head_ptr, const Grade *new_grade);
int update_grade(Grade *grade_to_update, float new_numeric, const char *new_letter);
int delete_grade(Grade **head_ptr, int id);
Grade* find_grade_by_id(Grade *head, int id);
Grade* find_grade_by_enrollment(Grade *head, int enrollment_id);
Grade* find_student_course_grade(Grade *head, int student_id, int course_id);
void numeric_to_letter(float numeric, char *letter_buffer);
int letter_to_points(const char *letter);
void display_student_grades(Grade *head, int student_id);
void display_course_grades(Grade *head, int course_id);
void display_all_grades(Grade *head);
float calculate_course_average(Grade *head, int course_id);
void display_grade_statistics(Grade *head, int course_id);
void free_all_grades(Grade *head);
int count_grades(Grade *head);
int get_next_grade_id(Grade *head);

#endif
