#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>

// --- FORWARD DECLARATIONS ---
// Grade ve Course yapýlarýný derleyiciye önceden haber veriyoruz.
// Böylece circular dependency (döngüsel baðýmlýlýk) hatasý almýyoruz.
struct Grade;
struct Course;

typedef struct Student {
    int id;
    char first_name[50];
    char last_name[50];
    char email[100];
    char phone[20];
    int enrollment_year;
    char major[100];
    float gpa;
    struct Student *next;
} Student;

// --- FONKSÝYON PROTOTÝPLERÝ ---

// CRUD Ýþlemleri
int add_student(Student **head, Student *new_student);
Student* find_student_by_id(Student *head, int id);
Student* find_student_by_name(Student *head, const char *first, const char *last);
Student* find_student_by_email(Student *head, const char *email);
void update_student(Student *target, Student *new_data); // void veya int olabilir, c dosyasýna uydurduk
int delete_student(Student **head, int id);

// Listeleme ve Detay
void display_all_students(Student *head);

// !!! GÜNCELLENEN FONKSÝYONLAR (Hatayý çözen kýsýmm) !!!
// Artýk Grade ve Course listelerini de parametre olarak alýyorlar
void display_student_details(Student *s, struct Grade *g_head, struct Course *c_head);
void display_student_transcript(Student *s, struct Grade *g_head, struct Course *c_head);
float calculate_student_gpa(int student_id, struct Grade *g_head, struct Course *c_head);

// Toplu GPA Hesaplama
void calculate_all_gpas(Student *s_head, struct Grade *g_head, struct Course *c_head);

// Dosya Ýþlemleri
int save_students_to_csv(Student *head, const char *filename);
int load_students_from_csv(Student **head);
void free_all_students(Student *head);

#endif
