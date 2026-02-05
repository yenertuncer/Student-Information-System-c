#ifndef COURSE_H
#define COURSE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Course {
    int id;
    char code[20];
    char name[100];
    int credits;
    int capacity;
    char department[50];
    char prerequisites[100];
    struct Course *next;
} Course;

int load_courses_from_csv(Course **head_ptr);
int save_courses_to_csv(Course *head, const char *filename);
int add_course(Course **head_ptr, const Course *new_course);
int update_course(Course *course_to_update, const Course *new_data);
int delete_course(Course **head_ptr, int id);
Course* find_course_by_id(Course *head, int id);
Course* find_course_by_code(Course *head, const char *code);
void display_all_courses(Course *head);
void display_course_details(Course *course);
int has_prerequisites(Course *course);
int check_prerequisites(int student_id, Course *course, void *grade_head, void *enrollment_head);
void free_all_courses(Course *head);
int count_courses(Course *head);

#endif
