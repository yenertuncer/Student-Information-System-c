#ifndef MENU_H
#define MENU_H

#include "student.h"
#include "course.h"
#include "professor.h"
#include "enrollment.h"
#include "grade.h"

// Ana Menü
void menu_main(Student **s_head, Course **c_head, Professor **p_head, Enrollment **e_head, Grade **g_head);

// Alt Menüler
void menu_student(Student **head, Course **c_head, Grade **g_head);
void menu_course(Course **head);
void menu_professor(Professor **head, Enrollment **e_head, Course **c_head);
void menu_enrollment(Enrollment **e_head, Student *s_head, Course *c_head, Grade *g_head);
void menu_grade(Grade **g_head, Enrollment *e_head, Student *s_head, Course *c_head);
void menu_reports(Student *s_head, Course *c_head, Professor *p_head, Enrollment *e_head, Grade *g_head);
void menu_system_options(Student **s_head, Course **c_head, Professor **p_head, Enrollment **e_head, Grade **g_head);

#endif
