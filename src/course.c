#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "course.h"
#include "utils.h"
#include "grade.h"
#include "enrollment.h"

/**
 * Adds a new course to the system after validating data and checking for duplicate IDs.
 * Verileri doðruladýktan ve mükerrer ID kontrolü yaptýktan sonra sisteme yeni bir ders ekler.
 * * @param head_ptr - Double pointer to the head of the course linked list [cite: 98]
 * @param head_ptr - Kurs baðlý listesinin baþýna iþaret eden çift kademeli pointer [cite: 98]
 * @param new_data - Pointer to the structure containing the new course details
 * @param new_data - Yeni ders detaylarýný içeren yapýya iþaret eden pointer
 * @return 1 if addition is successful, 0 if validation fails or ID already exists [cite: 533]
 * @return Ekleme baþarýlýysa 1, doðrulama baþarýsýzsa veya ID zaten varsa 0 döner [cite: 533]
 */
int add_course(Course **head_ptr, const Course *new_data) {
    if (new_data == NULL) {
        printf("Error: Invalid course data!\n");
        return 0;
    }
    
    if (!validate_positive_int(new_data->id)) {
        printf("Error: Course ID must be positive!\n");
        return 0;
    }
    
    if (!validate_positive_int(new_data->credits)) {
        printf("Error: Credits must be positive!\n");
        return 0;
    }
    
    if (!validate_positive_int(new_data->capacity)) {
        printf("Error: Capacity must be positive!\n");
        return 0;
    }
    
    if (find_course_by_id(*head_ptr, new_data->id) != NULL) {
        printf("Error: Course with ID %d already exists!\n", new_data->id);
        return 0;
    }
    
    Course *new_node = (Course *)malloc(sizeof(Course));
    if (new_node == NULL) {
        printf("Error: Memory allocation failed!\n");
        return 0;
    }
    
    *new_node = *new_data;
    new_node->next = NULL;
    
    if (*head_ptr == NULL) {
        *head_ptr = new_node;
    } else {
        Course *current = *head_ptr;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    
    printf("Success: Course '%s' added successfully!\n", new_data->name);
    return 1;
}

/**
 * Searches for a course in the linked list using its unique integer ID.
 * Benzersiz tam sayý ID'sini kullanarak baðlý listede bir kursu arar.
 * * @param head - Pointer to the head of the course list
 * @param head - Kurs listesinin baþýna iþaret eden pointer
 * @param id - The unique identifier of the course to find [cite: 40]
 * @param id - Bulunacak kursun benzersiz tanýmlayýcýsý [cite: 40]
 * @return Pointer to the course node if found, NULL otherwise
 * @return Kurs düðümü bulunursa adresi, aksi takdirde NULL döner
 */
Course* find_course_by_id(Course *head, int id) {
    Course *current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * Searches for a course in the linked list using its unique string code (e.g., "CS101").
 * Benzersiz ders kodunu (örn. "CS101") kullanarak baðlý listede bir kursu arar.
 * * @param head - Pointer to the head of the course list
 * @param head - Kurs listesinin baþýna iþaret eden pointer
 * @param code - The string code of the course to find
 * @param code - Bulunacak kursun dizgi formatýndaki kodu
 * @return Pointer to the course node if found, NULL otherwise
 * @return Kurs düðümü bulunursa adresi, aksi takdirde NULL döner
 */
Course* find_course_by_code(Course *head, const char *code) {
    Course *current = head;
    while (current != NULL) {
        if (strcmp(current->code, code) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * Updates the fields of an existing course node with new validated information.
 * Mevcut bir kurs düðümünün alanlarýný doðrulanmýþ yeni bilgilerle günceller.
 * * @param course_to_update - Pointer to the course node stored in the system [cite: 38]
 * @param course_to_update - Sistemde kayýtlý olan güncellenecek kurs düðümü pointer'ý [cite: 38]
 * @param new_data - Pointer to the structure containing updated details
 * @param new_data - Güncellenmiþ detaylarý içeren yapýya iþaret eden pointer
 * @return 1 if update is successful, 0 if validation fails
 * @return Güncelleme baþarýlýysa 1, doðrulama baþarýsýzsa 0 döner
 */
int update_course(Course *course_to_update, const Course *new_data) {
    if (course_to_update == NULL || new_data == NULL) {
        printf("Error: Invalid parameters!\n");
        return 0;
    }
    
    if (!validate_positive_int(new_data->credits)) {
        printf("Error: Credits must be positive!\n");
        return 0;
    }
    
    if (!validate_positive_int(new_data->capacity)) {
        printf("Error: Capacity must be positive!\n");
        return 0;
    }
    
    strcpy(course_to_update->code, new_data->code);
    strcpy(course_to_update->name, new_data->name);
    course_to_update->credits = new_data->credits;
    course_to_update->capacity = new_data->capacity;
    strcpy(course_to_update->department, new_data->department);
    strcpy(course_to_update->prerequisites, new_data->prerequisites);
    
    printf("Success: Course information updated!\n");
    return 1;
}

/**
 * Deletes a course from the linked list and frees the allocated memory.
 * Baðlý listeden bir kursu siler ve ayrýlan belleði serbest býrakýr.
 * * @param head_ptr - Double pointer to the head of the course list [cite: 39]
 * @param head_ptr - Kurs listesinin baþýna iþaret eden çift kademeli pointer [cite: 39]
 * @param id - The unique ID of the course to be removed
 * @param id - Silinecek kursun benzersiz ID'si
 * @return 1 if deletion is successful, 0 if course is not found
 * @return Silme baþarýlýysa 1, kurs bulunamazsa 0 döner
 */
int delete_course(Course **head_ptr, int id) {
    Course *current = *head_ptr;
    Course *prev = NULL;
    
    if (current == NULL) {
        printf("Error: Course list is empty!\n");
        return 0;
    }
    
    if (current->id == id) {
        *head_ptr = current->next;
        free(current);
        printf("Success: Course with ID %d deleted.\n", id);
        return 1;
    }
    
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Error: Course with ID %d not found!\n", id);
        return 0;
    }
    
    prev->next = current->next;
    free(current);
    printf("Success: Course with ID %d deleted.\n", id);
    return 1;
}

/**
 * Reads course records from a CSV file and populates the linked list[cite: 144].
 * CSV dosyasýndaki kurs kayýtlarýný okur ve baðlý listeyi doldurur[cite: 144].
 * * @param head_ptr - Double pointer to receive the head of the loaded list [cite: 93]
 * @param head_ptr - Yüklenen listenin baþýný alacak çift kademeli pointer [cite: 93]
 * @return 1 if loading is successful, 0 if file cannot be opened
 * @return Yükleme baþarýlýysa 1, dosya açýlamazsa 0 döner
 */
int load_courses_from_csv(Course **head_ptr) {
    const char *filename = "data/courses.csv";
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
    	filename = "courses.csv";
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("Warning: Could not open courses.csv. Starting empty.\n");
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
        if (token_count >= 6) {
            Course temp;
            temp.id = atoi(tokens[0]);
            strcpy(temp.code, tokens[1]);
            strcpy(temp.name, tokens[2]);
            temp.credits = atoi(tokens[3]);
            temp.capacity = atoi(tokens[4]);
            strcpy(temp.department, tokens[5]);
            if (token_count >= 7) strcpy(temp.prerequisites, tokens[6]);
            else strcpy(temp.prerequisites, "");
            
            Course *new_node = (Course *)malloc(sizeof(Course));
            if (new_node) {
                *new_node = temp;
                new_node->next = NULL;
                if (*head_ptr == NULL) *head_ptr = new_node;
                else {
                    Course *curr = *head_ptr;
                    while (curr->next != NULL) curr = curr->next;
                    curr->next = new_node;
                }
                count++;
            }
        }
    }
    fclose(file);
    printf("Success: Loaded %d courses from CSV.\n", count);
    return 1;
}

/**
 * Writes the entire course list into a formatted CSV file for persistence[cite: 92].
 * Tüm kurs listesini kalýcýlýk saðlamak için formatlý bir CSV dosyasýna yazar[cite: 92].
 * * @param head - Pointer to the head of the course list
 * @param head - Kurs listesinin baþýna iþaret eden pointer
 * @param filename - String representing the path to the save file
 * @param filename - Kayýt dosyasýnýn yolunu temsil eden dizgi
 * @return 1 if save is successful, 0 if file cannot be opened
 * @return Kayýt baþarýlýysa 1, dosya açýlamazsa 0 döner
 */
int save_courses_to_csv(Course *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file for writing!\n");
        return 0;
    }
    
    fprintf(file, "course_id,course_code,course_name,credits,capacity,department,prerequisites\n");
    Course *current = head;
    int count = 0;
    while (current != NULL) {
        fprintf(file, "%d,%s,%s,%d,%d,%s,%s\n",
                current->id, current->code, current->name, 
                current->credits, current->capacity, 
                current->department, current->prerequisites);
        current = current->next;
        count++;
    }
    fclose(file);
    printf("Success: Saved %d courses to CSV.\n", count);
    return 1;
}

/**
 * Prints all courses in the system in a readable table format[cite: 80].
 * Sistemdeki tüm kurslarý okunabilir bir tablo formatýnda yazdýrýr[cite: 80].
 * * @param head - Pointer to the head of the course list
 * @param head - Kurs listesinin baþýna iþaret eden pointer
 */
void display_all_courses(Course *head) {
    printf("\n====================================================================================================\n");
    printf("                                            COURSE LIST\n");
    printf("====================================================================================================\n");
    printf("%-6s %-8s %-35s %-4s %-5s %-20s %s\n", "ID", "Code", "Name", "Crd", "Cap", "Department", "Prereqs");
    printf("----------------------------------------------------------------------------------------------------\n");

    Course *current = head;
    int count = 0;
    while (current != NULL) {
        printf("%-6d %-8s %-35s %-4d %-5d %-20s %s\n", 
               current->id, current->code, current->name, 
               current->credits, current->capacity, current->department,
               (strlen(current->prerequisites) > 1) ? current->prerequisites : "None");
        current = current->next;
        count++;
    }
    printf("====================================================================================================\n");
    printf("Total Courses: %d\n", count);
}

/**
 * Displays full details of a specific course node[cite: 41].
 * Belirli bir kurs düðümünün tüm detaylarýný görüntüler[cite: 41].
 * * @param course - Pointer to the course structure to display
 * @param course - Görüntülenecek kurs yapýsýna iþaret eden pointer
 */
void display_course_details(Course *course) {
    if (course == NULL) {
        printf("Error: Course not found!\n");
        return;
    }
    printf("\n========================================\n");
    printf("         COURSE DETAILS                 \n");
    printf("========================================\n");
    printf("ID:            %d\n", course->id);
    printf("Code:          %s\n", course->code);
    printf("Name:          %s\n", course->name);
    printf("Credits:       %d\n", course->credits);
    printf("Capacity:      %d\n", course->capacity);
    printf("Department:    %s\n", course->department);
    printf("Prerequisites: %s\n", (strlen(course->prerequisites) > 0) ? course->prerequisites : "None");
    printf("========================================\n");
}

/**
 * Checks if a course has any defined prerequisite requirements[cite: 43].
 * Bir kursun tanýmlanmýþ herhangi bir ön koþul gereksinimi olup olmadýðýný kontrol eder[cite: 43].
 * * @param course - Pointer to the course structure
 * @param course - Kurs yapýsýna iþaret eden pointer
 * @return 1 if prerequisites exist, 0 otherwise
 * @return Ön koþullar varsa 1, aksi takdirde 0 döner
 */
int has_prerequisites(Course *course) {
    if (course == NULL) return 0;
    return (strlen(course->prerequisites) > 0);
}

/**
 * Verifies if a student has passed all prerequisites for a specific course[cite: 54].
 * Bir öðrencinin belirli bir kurs için tüm ön koþullarý geçip geçmediðini doðrular[cite: 54].
 * * @param student_id - ID of the student attempting to enroll
 * @param student_id - Kaydolmaya çalýþan öðrencinin ID'si
 * @param course - Pointer to the course with potential prerequisites
 * @param course - Olasý ön koþullarý olan kursa iþaret eden pointer
 * @param grade_head_void - Generic pointer to the head of the grade list
 * @param grade_head_void - Not listesinin baþýna iþaret eden genel pointer
 * @param enrollment_head_void - Generic pointer to the head of the enrollment list
 * @param enrollment_head_void - Kayýt listesinin baþýna iþaret eden genel pointer
 * @return 1 if all prerequisites are met, 0 otherwise
 * @return Tüm ön koþullar saðlanmýþsa 1, aksi takdirde 0 döner
 */
int check_prerequisites(int student_id, Course *course, void *grade_head_void, void *enrollment_head_void) {
    if (course == NULL) return 0;
    if (!has_prerequisites(course)) return 1;
    
    Grade *grade_head = (Grade *)grade_head_void;
    char prereq_copy[100];
    strcpy(prereq_copy, course->prerequisites);
    
    char *token = strtok(prereq_copy, ",");
    while (token != NULL) {
        trim_whitespace(token);
        int passed = 0;
        Grade *g = grade_head;
        while (g != NULL) {
            if (g->student_id == student_id) {
                if (g->numeric_grade >= 60.0) passed = 1;
            }
            g = g->next;
        }
        if (!passed) {
            printf("Error: Student has not completed prerequisite: %s\n", token);
            return 0;
        }
        token = strtok(NULL, ",");
    }
    return 1;
}

/**
 * Frees all dynamically allocated memory within the course linked list[cite: 162].
 * Kurs baðlý listesi içindeki dinamik olarak ayrýlmýþ tüm belleði serbest býrakýr[cite: 162].
 * * @param head - Pointer to the head of the course list
 * @param head - Kurs listesinin baþýna iþaret eden pointer
 */
void free_all_courses(Course *head) {
    Course *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp); 
    }
    printf("Memory for courses cleared.\n");
}

/**
 * Counts the total number of courses currently in the linked list.
 * Þu anda baðlý listede bulunan toplam kurs sayýsýný sayar.
 * * @param head - Pointer to the head of the course list
 * @param head - Kurs listesinin baþýna iþaret eden pointer
 * @return Total number of course nodes
 * @return Toplam kurs düðümü sayýsý
 */
int count_courses(Course *head) {
    int count = 0;
    Course *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}
