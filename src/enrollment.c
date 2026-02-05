// enrollment.c - Kayýt Modülü (TAMAMLANMIÞ)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enrollment.h"
#include "utils.h"
#include "course.h"
#include "student.h"

/**
 * Adds a new enrollment record to the system after validating the data.
 * Verileri doðruladýktan sonra sisteme yeni bir kayýt (enrollment) ekler.
 * * @param head_ptr - Double pointer to the head of the enrollment list
 * @param head_ptr - Kayýt listesinin baþýna iþaret eden çift kademeli pointer
 * @param new_data - Pointer to the structure containing new enrollment information
 * @param new_data - Yeni kayýt bilgilerini içeren yapýya iþaret eden pointer
 * @return 1 if successful, 0 if validation fails or ID already exists
 * @return Baþarýlýysa 1, doðrulama baþarýsýzsa veya ID zaten varsa 0 döner
 */
int add_enrollment(Enrollment **head_ptr, const Enrollment *new_data) {
    if (new_data == NULL) {
        printf("Error: Invalid enrollment data!\n");
        return 0;
    }
    
    // Validasyon
    if (!validate_positive_int(new_data->id)) {
        printf("Error: Enrollment ID must be positive!\n");
        return 0;
    }
    
    // Ayný ID var mý
    if (find_enrollment_by_id(*head_ptr, new_data->id) != NULL) {
        printf("Error: Enrollment with ID %d already exists!\n", new_data->id);
        return 0;
    }
    
    // Yeni node
    Enrollment *new_node = (Enrollment *)malloc(sizeof(Enrollment));
    if (new_node == NULL) {
        printf("Error: Memory allocation failed!\n");
        return 0;
    }
    
    // Verileri kopyala
    new_node->id = new_data->id;
    new_node->student_id = new_data->student_id;
    new_node->course_id = new_data->course_id;
    new_node->professor_id = new_data->professor_id;
    strcpy(new_node->semester, new_data->semester);
    strcpy(new_node->date, new_data->date);
    strcpy(new_node->status, new_data->status);
    new_node->next = NULL;
    
    // Listeye ekle
    if (*head_ptr == NULL) {
        *head_ptr = new_node;
    } else {
        Enrollment *current = *head_ptr;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    
    printf("Success: Enrollment added successfully!\n");
    return 1;
}

/**
 * Searches for an enrollment record in the list by its unique ID.
 * Benzersiz ID numarasýna göre bir kayýt kaydýný listede arar.
 * * @param head - Pointer to the head of the enrollment list
 * @param head - Kayýt listesinin baþýna iþaret eden pointer
 * @param id - The unique identifier of the enrollment to find
 * @param id - Bulunacak kaydýn benzersiz tanýmlayýcýsý
 * @return Pointer to the enrollment node if found, NULL otherwise
 * @return Kayýt düðümü bulunursa adresi, aksi takdirde NULL döner
 */
Enrollment* find_enrollment_by_id(Enrollment *head, int id) {
    Enrollment *current = head;
    
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}

/**
 * Checks if a specific student is currently enrolled in a specific course.
 * Belirli bir öðrencinin belirli bir kursa kayýtlý olup olmadýðýný kontrol eder.
 * * @param head - Pointer to the head of the enrollment list
 * @param head - Kayýt listesinin baþýna iþaret eden pointer
 * @param student_id - ID of the student to check
 * @param student_id - Kontrol edilecek öðrencinin ID'si
 * @param course_id - ID of the course to check
 * @param course_id - Kontrol edilecek kursun ID'si
 * @return 1 if the student is enrolled or completed, 0 otherwise
 * @return Öðrenci kayýtlýysa veya tamamlamýþsa 1, aksi takdirde 0 döner
 */
int is_student_enrolled(Enrollment *head, int student_id, int course_id) {
    Enrollment *current = head;
    
    while (current != NULL) {
        if (current->student_id == student_id && 
            current->course_id == course_id &&
            (strcmp(current->status, "Enrolled") == 0 || 
             strcmp(current->status, "Completed") == 0)) {
            return 1;  // Zaten kayýtlý
        }
        current = current->next;
    }
    
    return 0;  // Kayýtlý deðil
}

/**
 * Counts the number of active enrollments for a specific course.
 * Belirli bir kurs için aktif kayýtlarýn sayýsýný hesaplar.
 * * @param head - Pointer to the head of the enrollment list
 * @param head - Kayýt listesinin baþýna iþaret eden pointer
 * @param course_id - ID of the course to count enrollments for
 * @param course_id - Kayýtlarý sayýlacak kursun ID'si
 * @return Total number of students with "Enrolled" status
 * @return "Enrolled" durumundaki toplam öðrenci sayýsý
 */
int get_enrollment_count(Enrollment *head, int course_id) {
    int count = 0;
    Enrollment *current = head;
    
    while (current != NULL) {
        if (current->course_id == course_id && 
            strcmp(current->status, "Enrolled") == 0) {
            count++;
        }
        current = current->next;
    }
    
    return count;
}

/**
 * Permanently deletes an enrollment record from the linked list by its ID.
 * Bir kayýt kaydýný ID'sine göre baðlý listeden kalýcý olarak siler.
 * * @param head_ptr - Double pointer to the head of the enrollment list
 * @param head_ptr - Kayýt listesinin baþýna iþaret eden çift kademeli pointer
 * @param id - The unique ID of the enrollment to delete
 * @param id - Silinecek kaydýn benzersiz ID'si
 * @return 1 if deletion is successful, 0 if record is not found
 * @return Silme baþarýlýysa 1, kayýt bulunamazsa 0 döner
 */
int delete_enrollment(Enrollment **head_ptr, int id) {
    Enrollment *current = *head_ptr;
    Enrollment *prev = NULL;
    
    if (current == NULL) {
        printf("Error: Enrollment list is empty!\n");
        return 0;
    }
    
    // Ýlk node
    if (current->id == id) {
        *head_ptr = current->next;
        printf("Success: Enrollment with ID %d deleted.\n", id);
        free(current);
        return 1;
    }
    
    // Ortada/sonda
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Error: Enrollment with ID %d not found!\n", id);
        return 0;
    }
    
    prev->next = current->next;
    printf("Success: Enrollment with ID %d deleted.\n", id);
    free(current);
    return 1;
}

/**
 * Changes a student's enrollment status to "Dropped" for a specific course.
 * Belirli bir kurs için öðrencinin kayýt durumunu "Dropped" olarak deðiþtirir.
 * * @param head_ptr - Double pointer to the head of the enrollment list
 * @param head_ptr - Kayýt listesinin baþýna iþaret eden çift kademeli pointer
 * @param student_id - ID of the student dropping the course
 * @param student_id - Kursu býrakan öðrencinin ID'si
 * @param course_id - ID of the course being dropped
 * @param course_id - Býrakýlan kursun ID'si
 * @return 1 if successfully dropped, 0 if no active enrollment is found
 * @return Baþarýyla býrakýldýysa 1, aktif kayýt bulunamazsa 0 döner
 */
int drop_enrollment(Enrollment **head_ptr, int student_id, int course_id) {
    Enrollment *current = *head_ptr;
    
    while (current != NULL) {
        if (current->student_id == student_id && 
            current->course_id == course_id &&
            strcmp(current->status, "Enrolled") == 0) {
            
            // Status'u "Dropped" yap
            strcpy(current->status, "Dropped");
            printf("Success: Student dropped from course.\n");
            return 1;
        }
        current = current->next;
    }
    
    printf("Error: Active enrollment not found!\n");
    return 0;
}

/**
 * Loads enrollment records from a CSV file into the linked list.
 * CSV dosyasýndaki kayýt verilerini okur ve baðlý listeye yükler.
 * * @param head_ptr - Double pointer to receive the head of the loaded list
 * @param head_ptr - Yüklenen listenin baþýný alacak çift kademeli pointer
 * @return 1 if loading is successful, 0 if file cannot be opened
 * @return Yükleme baþarýlýysa 1, dosya açýlamazsa 0 döner
 */
int load_enrollments_from_csv(Enrollment **head_ptr) {
    const char *filename = "data/enrollments.csv";
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
    	filename = "enrollments.csv";
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("Warning: Could not open enrollments.csv. Starting empty.\n");
            return 0;
        }
    }
    
    char line[512];
    char *tokens[10];
    int count = 0;
    
    fgets(line, sizeof(line), file);
    
    while (fgets(line, sizeof(line), file)) {
        remove_newline(line);
        
        int token_count = split_csv_line(line, tokens, 7);
        
        if (token_count >= 7) {
            Enrollment temp;
            
            temp.id = atoi(tokens[0]);
            temp.student_id = atoi(tokens[1]);
            temp.course_id = atoi(tokens[2]);
            temp.professor_id = atoi(tokens[3]);
            strcpy(temp.semester, tokens[4]);
            strcpy(temp.date, tokens[5]);
            strcpy(temp.status, tokens[6]);
            
            Enrollment *new_node = (Enrollment *)malloc(sizeof(Enrollment));
            if (new_node) {
                *new_node = temp;
                new_node->next = NULL;
                
                if (*head_ptr == NULL) {
                    *head_ptr = new_node;
                } else {
                    Enrollment *curr = *head_ptr;
                    while (curr->next != NULL) curr = curr->next;
                    curr->next = new_node;
                }
                count++;
            }
        }
    }
    
    fclose(file);
    printf("Success: Loaded %d enrollments from CSV.\n", count);
    return 1;
}

/**
 * Saves all enrollment records from the linked list into a CSV file.
 * Baðlý listedeki tüm kayýt verilerini bir CSV dosyasýna kaydeder.
 * * @param head - Pointer to the head of the enrollment list
 * @param head - Kayýt listesinin baþýna iþaret eden pointer
 * @param filename - Destination file path string
 * @param filename - Hedef dosya yolu dizgisi
 * @return 1 if save is successful, 0 if file cannot be opened
 * @return Kayýt baþarýlýysa 1, dosya açýlamazsa 0 döner
 */
int save_enrollments_to_csv(Enrollment *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file for writing!\n");
        return 0;
    }
    
    fprintf(file, "enrollment_id,student_id,course_id,professor_id,semester,enrollment_date,status\n");
    
    Enrollment *current = head;
    int count = 0;
    
    while (current != NULL) {
        fprintf(file, "%d,%d,%d,%d,%s,%s,%s\n",
                current->id,
                current->student_id,
                current->course_id,
                current->professor_id,
                current->semester,
                current->date,
                current->status);
        current = current->next;
        count++;
    }
    
    fclose(file);
    printf("Success: Saved %d enrollments to CSV.\n", count);
    return 1;
}

/**
 * Lists all course enrollments for a specific student in a table format.
 * Belirli bir öðrencinin tüm ders kayýtlarýný tablo formatýnda listeler.
 * * @param head - Pointer to the head of the enrollment list
 * @param head - Kayýt listesinin baþýna iþaret eden pointer
 * @param student_id - ID of the student whose enrollments will be displayed
 * @param student_id - Kayýtlarý görüntülenecek öðrencinin ID'si
 */
void display_student_enrollments(Enrollment *head, int student_id) {
    printf("\n========================================================================\n");
    printf("  Enrollments for Student ID: %d\n", student_id);
    printf("========================================================================\n");
    printf("%-10s %-10s %-10s %-15s %-12s %-10s\n", 
           "Enr.ID", "CourseID", "ProfID", "Semester", "Date", "Status");
    printf("------------------------------------------------------------------------\n");
    
    Enrollment *current = head;
    int found = 0;
    
    while (current != NULL) {
        if (current->student_id == student_id) {
            printf("%-10d %-10d %-10d %-15s %-12s %-10s\n",
                   current->id,
                   current->course_id,
                   current->professor_id,
                   current->semester,
                   current->date,
                   current->status);
            found = 1;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("No enrollments found for this student.\n");
    }
    
    printf("========================================================================\n");
}

/**
 * Displays a list of all students enrolled in a specific course.
 * Belirli bir kursa kayýtlý olan tüm öðrencilerin listesini görüntüler.
 * * @param head - Pointer to the head of the enrollment list
 * @param head - Kayýt listesinin baþýna iþaret eden pointer
 * @param course_id - ID of the course whose roster will be displayed
 * @param course_id - Listesi görüntülenecek kursun ID'si
 */
void display_course_roster(Enrollment *head, int course_id) {
    printf("\n====================================================\n");
    printf("  Course Roster for Course ID: %d\n", course_id);
    printf("====================================================\n");
    printf("%-10s %-10s %-15s %-10s\n", 
           "Enr.ID", "StudentID", "Semester", "Status");
    printf("----------------------------------------------------\n");
    
    Enrollment *current = head;
    int found = 0;
    
    while (current != NULL) {
        if (current->course_id == course_id) {
            printf("%-10d %-10d %-15s %-10s\n",
                   current->id,
                   current->student_id,
                   current->semester,
                   current->status);
            found = 1;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("No students enrolled in this course.\n");
    }
    
    printf("====================================================\n");
}

/**
 * Prints all enrollment records in the system in a comprehensive table.
 * Sistemdeki tüm kayýt verilerini kapsamlý bir tablo formatýnda yazdýrýr.
 * * @param head - Pointer to the head of the enrollment list
 * @param head - Kayýt listesinin baþýna iþaret eden pointer
 */
void display_all_enrollments(Enrollment *head) {
    if (head == NULL) {
        printf("\nNo enrollments to display.\n");
        return;
    }
    
    printf("\n======================================================================================\n");
    printf("                                ENROLLMENT LIST                                       \n");
    printf("======================================================================================\n");
    printf("%-10s %-10s %-10s %-10s %-15s %-12s %-10s\n", 
           "Enr.ID", "StudentID", "CourseID", "ProfID", "Semester", "Date", "Status");
    printf("--------------------------------------------------------------------------------------\n");
    
    Enrollment *current = head;
    int count = 0;
    
    while (current != NULL) {
        printf("%-10d %-10d %-10d %-10d %-15s %-12s %-10s\n",
               current->id,
               current->student_id,
               current->course_id,
               current->professor_id,
               current->semester,
               current->date,
               current->status);
        current = current->next;
        count++;
    }
    
    printf("======================================================================================\n");
    printf("Total Enrollments: %d\n", count);
    printf("======================================================================================\n");
}

/**
 * Frees all memory allocated for the enrollment linked list.
 * Kayýt baðlý listesi için ayrýlan tüm belleði serbest býrakýr.
 * * @param head - Pointer to the head of the enrollment list
 * @param head - Kayýt listesinin baþýna iþaret eden pointer
 */
void free_all_enrollments(Enrollment *head) {
    Enrollment *temp;
    
    while (head != NULL) {
    	temp = head;
        head = head->next;
        free(temp);
    }
    
    printf("Memory for enrollments cleared.\n");
}

/**
 * Returns the total count of enrollment records in the system.
 * Sistemdeki toplam kayýt kaydý sayýsýný döndürür.
 * * @param head - Pointer to the head of the enrollment list
 * @param head - Kayýt listesinin baþýna iþaret eden pointer
 * @return Total number of enrollment nodes
 * @return Toplam kayýt düðümü sayýsý
 */
int count_enrollments(Enrollment *head) {
    int count = 0;
    Enrollment *current = head;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    return count;
}

/**
 * Finds the highest enrollment ID in the list and returns the next sequential ID.
 * Listedeki en yüksek kayýt ID'sini bulur ve bir sonraki sýralý ID'yi döndürür.
 * * @param head - Pointer to the head of the enrollment list
 * @param head - Kayýt listesinin baþýna iþaret eden pointer
 * @return The next available integer ID for a new enrollment
 * @return Yeni bir kayýt için kullanýlabilir bir sonraki tam sayý ID
 */
int get_next_enrollment_id(Enrollment *head) {
    int max_id = 0;
    Enrollment *current = head;
    
    while (current != NULL) {
        if (current->id > max_id) {
            max_id = current->id;
        }
        current = current->next;
    }
    
    return max_id + 1;
}
