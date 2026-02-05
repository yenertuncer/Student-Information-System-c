#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "student.h"
#include "utils.h"
#include "grade.h"
#include "course.h"

/**
 * Adds a new student to the system. Checks for duplicate IDs.
 * Sisteme yeni bir öðrenci ekler. Mükerrer ID kontrolü yapar.
 * * @param head - Address of the pointer to the head of the student list
 * @param head - Öðrenci listesinin baþýný tutan pointer'ýn adresi
 * @param new_student - Pointer to the structure containing new student data
 * @param new_student - Yeni öðrenci verilerini içeren yapý pointer'ý
 * @return 1 if successful, 0 if ID exists or memory allocation fails
 * @return Baþarýlýysa 1, ID zaten varsa veya bellek hatasý oluþursa 0 döner
 */
int add_student(Student **head, Student *new_student) {
    if (find_student_by_id(*head, new_student->id) != NULL) {
        printf("Error: Student with ID %d already exists!\n", new_student->id);
        return 0;
    }

    Student *node = (Student *)malloc(sizeof(Student));
    if (node == NULL) {
        printf("Memory allocation failed!\n");
        return 0;
    }

    *node = *new_student;
    node->next = NULL;

    if (*head == NULL) {
        *head = node;
    } else {
        Student *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
    }
    return 1;
}

/**
 * Searches for a student in the list by their unique ID.
 * Öðrenciyi benzersiz ID numarasýna göre listede arar.
 * * @param head - Head of the student list
 * @param head - Öðrenci listesinin baþý
 * @param id - Unique ID of the student to find
 * @param id - Aranan öðrencinin benzersiz ID'si
 * @return Pointer to the found student or NULL if not found
 * @return Bulunursa öðrenci yapýsýnýn adresi, bulunamazsa NULL döner
 */
Student* find_student_by_id(Student *head, int id) {
    Student *current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * Searches for a student by first and last name (case-insensitive).
 * Ýsim ve soyisime göre öðrenci aramasý yapar (büyük/küçük harf duyarsýz).
 * * @param head - Head of the student list
 * @param head - Öðrenci listesinin baþý
 * @param first - First name to search
 * @param first - Aranan isim
 * @param last - Last name to search
 * @param last - Aranan soyisim
 * @return Pointer to the matched student or NULL
 * @return Eþleþen öðrenci yapýsý veya NULL döner
 */
Student* find_student_by_name(Student *head, const char *first, const char *last) {
    Student *current = head;
    while (current != NULL) {
        if (strcasecmp(current->first_name, first) == 0 && strcasecmp(current->last_name, last) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * Searches for a student by their email address.
 * E-posta adresine göre öðrenci aramasý yapar.
 * * @param head - Head of the student list
 * @param head - Öðrenci listesinin baþý
 * @param email - Email address to search
 * @param email - Aranan e-posta adresi
 * @return Pointer to the matched student or NULL
 * @return Eþleþen öðrenci yapýsý veya NULL döner
 */
Student* find_student_by_email(Student *head, const char *email) {
    Student *current = head;
    while (current != NULL) {
        if (strcmp(current->email, email) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * Updates an existing student's information with new data.
 * Mevcut bir öðrencinin bilgilerini yeni verilerle günceller.
 * * @param target - Pointer to the existing student structure to be updated
 * @param target - Güncellenecek olan mevcut öðrenci yapýsý
 * @param new_data - Structure containing updated information
 * @param new_data - Yeni bilgileri içeren yapý
 */
void update_student(Student *target, Student *new_data) {
    if (target == NULL) return;
    strcpy(target->first_name, new_data->first_name);
    strcpy(target->last_name, new_data->last_name);
    strcpy(target->email, new_data->email);
    strcpy(target->phone, new_data->phone);
    target->enrollment_year = new_data->enrollment_year;
    strcpy(target->major, new_data->major);
    printf("Success: Student information updated!\n");
}

/**
 * Deletes a student by ID and frees associated memory.
 * Belirtilen ID'ye sahip öðrenciyi siler ve belleði serbest býrakýr.
 * * @param head - Address of the pointer to the head of the student list
 * @param head - Öðrenci listesinin baþýný tutan pointer'ýn adresi
 * @param id - ID of the student to delete
 * @param id - Silinecek öðrencinýn ID'si
 * @return 1 if successful, 0 if student not found
 * @return Silme baþarýlýysa 1, öðrenci bulunamazsa 0 döner
 */
int delete_student(Student **head, int id) {
    if (*head == NULL) return 0;

    Student *temp = *head;
    Student *prev = NULL;

    if (temp != NULL && temp->id == id) {
        *head = temp->next;
        free(temp);
        printf("Success: Student with ID %d deleted.\n", id);
        return 1;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Error: Student with ID %d not found.\n", id);
        return 0;
    }

    prev->next = temp->next;
    free(temp);
    printf("Success: Student with ID %d deleted.\n", id);
    return 1;
}

/**
 * Displays all students in the system in a tabular format.
 * Sistemdeki tüm öðrencileri tablo formatýnda listeler.
 * * @param head - Head of the student list
 * @param head - Öðrenci listesinin baþý
 */
void display_all_students(Student *head) {
    printf("\n================================================================================\n");
    printf("                                STUDENT LIST\n");
    printf("================================================================================\n");
    printf("%-10s %-20s %-25s %-15s\n", "ID", "Name", "Email", "Major");
    printf("--------------------------------------------------------------------------------\n");
    
    Student *current = head;
    while (current != NULL) {
        char full_name[100];
        sprintf(full_name, "%s %s", current->first_name, current->last_name);
        printf("%-10d %-20s %-25s %-15s\n", 
               current->id, full_name, current->email, current->major);
        current = current->next;
    }
    printf("================================================================================\n");
}

/**
 * Displays detailed information and recalculated GPA for a student.
 * Bir öðrencinin detaylý bilgilerini ve yeniden hesaplanan GPA deðerini gösterir.
 * * @param s - Pointer to the student structure
 * @param s - Bilgileri gösterilecek öðrenci yapýsý
 * @param g_head - Head of the grade list (for GPA calculation)
 * @param g_head - Not listesinin baþý (GPA hesabý için)
 * @param c_head - Head of the course list (for credit info)
 * @param c_head - Kurs listesinin baþý (Kredi bilgisi için)
 */
void display_student_details(Student *s, struct Grade *g_head, struct Course *c_head) {
    if (s == NULL) return;
    
    s->gpa = calculate_student_gpa(s->id, g_head, c_head);

    printf("\n========================================\n");
    printf("         STUDENT DETAILS\n");
    printf("========================================\n");
    printf("ID:              %d\n", s->id);
    printf("Name:            %s %s\n", s->first_name, s->last_name);
    printf("Email:           %s\n", s->email);
    printf("Phone:           %s\n", s->phone);
    printf("Enrollment Year: %d\n", s->enrollment_year);
    printf("Major:           %s\n", s->major);
    printf("GPA:             %.2f\n", s->gpa);
    printf("========================================\n");
}

/**
 * Calculates a student's Cumulative GPA based on numeric grades and credits.
 * Öðrencinin sayýsal notlarýna ve kredilerine göre genel GPA'ini hesaplar.
 * * @param student_id - ID of the student
 * @param student_id - Hesaplama yapýlacak öðrencinin ID'si
 * @param g_head - Head of the grade list
 * @param g_head - Not listesinin baþý
 * @param c_head - Head of the course list
 * @param c_head - Kurs listesinin baþý
 * @return Calculated GPA value (0.0 - 4.0)
 * @return Hesaplanan GPA deðeri (0.0 - 4.0 arasý)
 */
float calculate_student_gpa(int student_id, struct Grade *g_head, struct Course *c_head) {
    float total_points = 0;
    int total_credits = 0;
    Grade *current_g = g_head;
    
    while (current_g != NULL) {
        if (current_g->student_id == student_id) {
            Course *c = find_course_by_id(c_head, current_g->course_id);
            if (c != NULL) {
                float grade_point = 0;
                if (current_g->numeric_grade >= 90) grade_point = 4.0;
                else if (current_g->numeric_grade >= 85) grade_point = 3.5;
                else if (current_g->numeric_grade >= 80) grade_point = 3.0;
                else if (current_g->numeric_grade >= 75) grade_point = 2.5;
                else if (current_g->numeric_grade >= 70) grade_point = 2.0;
                else if (current_g->numeric_grade >= 60) grade_point = 1.5;
                else if (current_g->numeric_grade >= 50) grade_point = 1.0;
                else grade_point = 0.0;
                
                total_points += (grade_point * c->credits);
                total_credits += c->credits;
            }
        }
        current_g = current_g->next;
    }
    
    if (total_credits == 0) return 0.0;
    return total_points / total_credits;
}

/**
 * Displays the student's transcript, including courses, grades, and total credits.
 * Öðrencinin transkriptini (dersler, notlar ve toplam kredi) listeler.
 * * @param s - Pointer to the student structure
 * @param s - Öðrenci yapýsý pointer'ý
 * @param g_head - Head of the grade list
 * @param g_head - Not listesinin baþý
 * @param c_head - Head of the course list
 * @param c_head - Kurs listesinin baþý
 */
void display_student_transcript(Student *s, struct Grade *g_head, struct Course *c_head) {
    if (s == NULL) return;
    
    s->gpa = calculate_student_gpa(s->id, g_head, c_head);

    printf("\n================================================================================\n");
    printf("                            TRANSCRIPT OF RECORDS\n");
    printf("================================================================================\n");
    printf("Student: %s %s (ID: %d)\n", s->first_name, s->last_name, s->id);
    printf("Major:   %s\n", s->major);
    printf("================================================================================\n");
    printf("%-8s %-35s %-15s %-7s %-8s %s\n", "Code", "Course Name", "Semester", "Credits", "Grade", "Letter");
    printf("--------------------------------------------------------------------------------\n");
    
    Grade *g = g_head;
    int total_credits = 0;
    
    while (g != NULL) {
        if (g->student_id == s->id) {
            Course *c = find_course_by_id(c_head, g->course_id);
            if (c != NULL) {
                printf("%-8s %-35s %-15s %-7d %-8.2f %s\n",
                       c->code, c->name, g->semester, c->credits, g->numeric_grade, g->letter_grade);
                total_credits += c->credits;
            }
        }
        g = g->next;
    }
    printf("================================================================================\n");
    printf("Total Credits: %d\n", total_credits);
    printf("Cumulative GPA: %.2f / 4.00\n", s->gpa);
    printf("================================================================================\n");
}

/**
 * Saves the current list of students to a CSV file.
 * Mevcut öðrenci listesini bir CSV dosyasýna kaydeder.
 * * @param head - Head of the student list
 * @param head - Öðrenci listesinin baþý
 * @param filename - Name and path of the file to save
 * @param filename - Kaydedilecek dosyanýn adý ve yolu
 * @return 1 if save successful, 0 if file cannot be opened
 * @return Kayýt baþarýlýysa 1, dosya açýlamazsa 0 döner
 */
int save_students_to_csv(Student *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return 0;
    }
    
    fprintf(file, "student_id,first_name,last_name,email,phone,enrollment_year,major,gpa\n");
    
    Student *current = head;
    int count = 0;
    while (current != NULL) {
        fprintf(file, "%d,%s,%s,%s,%s,%d,%s,%.2f\n",
                current->id,
                current->first_name,
                current->last_name,
                current->email,
                current->phone,
                current->enrollment_year,
                current->major,
                current->gpa);
        current = current->next;
        count++;
    }
    fclose(file);
    printf("Success: Saved %d students to CSV.\n", count);
    return 1;
}

/**
 * Loads student records from a CSV file into the linked list.
 * CSV dosyasýndaki öðrenci kayýtlarýný baðlý listeye yükler.
 * * @param head - Address of the pointer to the head of the student list
 * @param head - Öðrenci listesinin baþýný tutan pointer'ýn adresi
 * @return Number of students successfully loaded
 * @return Baþarýyla yüklenen öðrenci sayýsýný döner
 */
int load_students_from_csv(Student **head) {
    const char *filename = "data/students.csv";
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        filename = "students.csv";
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("Warning: Could not open students.csv anywhere. Starting empty.\n");
            return 0;
        }
    }
    
    char line[512];
    int count = 0;
    fgets(line, sizeof(line), file);
    
    while (fgets(line, sizeof(line), file)) {
        Student *new_s = (Student *)malloc(sizeof(Student));
        
        char *token = strtok(line, ",");
        if(token) new_s->id = atoi(token);
        
        token = strtok(NULL, ","); if(token) strcpy(new_s->first_name, token);
        token = strtok(NULL, ","); if(token) strcpy(new_s->last_name, token);
        token = strtok(NULL, ","); if(token) strcpy(new_s->email, token);
        token = strtok(NULL, ","); if(token) strcpy(new_s->phone, token);
        token = strtok(NULL, ","); if(token) new_s->enrollment_year = atoi(token);
        
        token = strtok(NULL, ","); if(token) strcpy(new_s->major, token);
        new_s->major[strcspn(new_s->major, "\r\n")] = 0;
        
        token = strtok(NULL, ","); if(token) new_s->gpa = atof(token);
        
        new_s->next = NULL;
        add_student(head, new_s);
        free(new_s); 
        count++;
    }
    
    fclose(file);
    printf("Success: Loaded %d students from CSV.\n", count);
    return count;
}

/**
 * Updates GPA values for all students based on the current grade and course data.
 * Tüm öðrencilerin GPA deðerlerini güncel not ve kurs verilerine göre günceller.
 * * @param s_head - Head of the student list
 * @param s_head - Öðrenci listesinin baþý
 * @param g_head - Head of the grade list
 * @param g_head - Not listesinin baþý
 * @param c_head - Head of the course list
 * @param c_head - Kurs listesinin baþý
 */
void calculate_all_gpas(Student *s_head, struct Grade *g_head, struct Course *c_head) {
    Student *current = s_head;
    while(current != NULL) {
        current->gpa = calculate_student_gpa(current->id, g_head, c_head);
        current = current->next;
    }
}

/**
 * Frees all memory allocated for the student linked list.
 * Öðrenci baðlý listesi için ayrýlan tüm belleði serbest býrakýr.
 * * @param head - Head of the student list
 * @param head - Öðrenci listesinin baþý
 */
void free_all_students(Student *head) {
    Student *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("Memory for students cleared.\n");
}
