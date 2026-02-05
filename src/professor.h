#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Professor {
    int id;
    char first_name[50];
    char last_name[50];
    char email[100];
    char phone[20];
    char department[50];
    char title[50];
    char office[20];
    struct Professor *next;
} Professor;

int load_professors_from_csv(Professor **head_ptr);
int save_professors_to_csv(Professor *head, const char *filename);
int add_professor(Professor **head_ptr, const Professor *new_prof);
int update_professor(Professor *prof_to_update, const Professor *new_data);
int delete_professor(Professor **head_ptr, int id);
Professor* find_professor_by_id(Professor *head, int id);
Professor* find_professor_by_name(Professor *head, const char *first_name, const char *last_name);
void display_all_professors(Professor *head);
void display_professor_details(Professor *professor);
void display_professor_courses(int professor_id, void *enrollment_head, void *course_head);
void free_all_professors(Professor *head);
int count_professors(Professor *head);

#endif
